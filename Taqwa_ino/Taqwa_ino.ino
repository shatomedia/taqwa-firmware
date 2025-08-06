/*
  TAQWA - Digital Prayer Time
  Versi: V.7.3 (12.0424)
  Dibuat oleh: SHATOMEDIA

  Deskripsi:
  Program ini merupakan firmware untuk perangkat jadwal waktu sholat digital berbasis ESP8266.
  Fitur utama:
    - Menampilkan jadwal sholat pada display 7-segment dan TV
    - Pengaturan melalui aplikasi Android (tidak lagi melalui web UI)
    - API JSON untuk integrasi dengan perangkat lain (misal Android TV)
    - Pengelolaan alarm, iqomah, dan relay perangkat masjid
    - Dukungan update jadwal otomatis berdasarkan perhitungan hisab

  Catatan:
    - Semua pengaturan dilakukan melalui aplikasi Android
    - Kode sudah dibersihkan dari fungsi ESP-NOW dan halaman web lama
    - Dokumentasi versi dan riwayat pengembangan ada di file 'version'
*/

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>

ESP8266WebServer server(80);
const char* version = "V.7.4";
const char* currentVersion = version; // untuk OTA module

// Include OTA module setelah deklarasi server dan version
#include "Handle/_ota.h"

#include <JWS_Segment.h>
JWS_Segment segment;
#include <JWS_DS3231.h>
JWS_DS3231 waktu;
#include <JWS_Ephemeris.h>
JWS_Ephemeris jws;
#include <JWS_Memori.h>
JWS_Memori memori;
#include <JWS_Interface.h>
JWS_Interface IO;
#include <DFPlayer_Mini_Mp3.h>
const int pinDip = D8;

long last1 = 0;
long last2 = 0;
bool _konter = false;
const uint8_t ding = 8;

#include "Tv/tv.h"
#include "Tv/tv1.h"
#include "Tv/tv2.h"
#include "Handle/_index.h"
#include "Handle/_perangkat.h"
#include "Handle/_waktu.h"
#include "Handle/_koordinat.h"
#include "Handle/_ikhtiyat.h"
#include "Handle/_iqomah.h"
#include "Handle/_display.h"
#include "Handle/_tilawah.h"
#include "Handle/_alaram.h"
#include "Handle/_tvi.h"
#include "Handle/_wifi.h"
#include "Handle/_cloud.h"
#include "Tv/_tv.h"
#include <DMDESP.h>
#include "Handle/_p10.h"

#define DISPLAYS_WIDE 3
#define DISPLAYS_HIGH 1


DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);
String teksBesar = "Selamat";
unsigned long waktuDisplay = 0;
int stateDisplay = 0;
int Data_Detik, Data_Menit, Data_Jam;


void updateTeksBesarFromWeb() {
  String teks = "";

  // --- Sumber 1 ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    if (http.begin(client, "http://" + memori.getDomain() + ".shatomedia.com/get-kas")) {
      http.addHeader("User-Agent", "Mozilla/5.0");
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        StaticJsonDocument<4096> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
          JsonArray arr = doc["result"].as<JsonArray>();
          for (JsonObject obj : arr) {
            if (obj.containsKey("keterangan") && obj.containsKey("jumlah")) {
              teks += obj["keterangan"].as<String>();
              teks += " : ";
              teks += obj["jumlah"].as<long>();
              teks += " | ";
            }
          }
        } else {
          teks += "Gagal parsing data kas! | ";
        }
      } else {
        teks += "Gagal ambil data kas! | ";
      }
      http.end();
    } else {
      teks += "Koneksi server gagal! | ";
    }
  } else {
    teks += "Sistem offline. | ";
  }

  // --- Sumber 2 (misal: info kegiatan) ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http2;
    WiFiClient client2;
    if (http2.begin(client2, "http://" + memori.getDomain() + ".shatomedia.com/get-kategori-informasi")) {
      http2.addHeader("User-Agent", "Mozilla/5.0");
      int httpCode2 = http2.GET();
      if (httpCode2 == HTTP_CODE_OK) {
        String payload2 = http2.getString();
        StaticJsonDocument<2048> doc2;
        DeserializationError error2 = deserializeJson(doc2, payload2);
        if (!error2) {
          JsonArray arr2 = doc2["result"].as<JsonArray>();
          for (JsonObject obj : arr2) {
            if (obj.containsKey("nama") && obj.containsKey("keterangan")) {
              teks += obj["nama"].as<String>();
              teks += " @ ";
              teks += obj["keterangan"].as<String>();
              teks += " | ";
            }
          }
        } else {
          teks += "Gagal parsing info kegiatan! | ";
        }
      } else {
        teks += "Gagal ambil info kegiatan! | ";
      }
      http2.end();
    } else {
      teks += "Koneksi server info gagal! | ";
    }
  }

  // Hasil akhir
  teksBesar = teks.length() > 0 ? teks : "Offline";
}



void receiveData() {
  StaticJsonDocument<300> JSONData;
  String jsonString = server.arg("plain");
  DeserializationError error = deserializeJson(JSONData, jsonString);
  if (error) {
    server.send(500, "application/json", "Error in parsing");
    return;
  }
  if (JSONData.containsKey("number")) {
    server.send(200, "application/json", String(JSONData["number"].as<int>()) + " Received");
  } else {
    server.send(400, "application/json", "Bad JSON");
  }
}

void JsonMasjid() {
  StaticJsonDocument<420> JSONData;
  JSONData["mas"]  = memori.getMasjid();
  JSONData["alm"]  = memori.getAlamat();
  JSONData["alt"]  = memori._getAlamat();
  JSONData["dom"]  = memori.getDomain();
  JSONData["yyy"]  = waktu.kalenderString();
  JSONData["yyh"]  = waktu.hijriyahString();
  JSONData["dd" ]  = waktu.hari();
  JSONData["hh" ]  = waktu.jam();
  JSONData["mm" ]  = waktu.menit();
  JSONData["ss" ]  = waktu.detik();
  JSONData["the"]  = memori.getTheme();
  JSONData["iSu"]  = memori.iqomahShubuh();
  JSONData["iDu"]  = memori.iqomahDzuhur();
  JSONData["iAs"]  = memori.iqomahAshar();
  JSONData["iMa"]  = memori.iqomahMaghrib();
  JSONData["iIs"]  = memori.iqomahIsya();
  JSONData["hIms"] = jws.imsyakJam();
  JSONData["mIms"] = jws.imsyakMenit();
  JSONData["hShu"] = jws.shubuhJam();
  JSONData["mShu"] = jws.shubuhMenit();
  JSONData["hSyu"] = jws.syuruqJam();
  JSONData["mSyu"] = jws.syuruqMenit();
  JSONData["hDhu"] = jws.dhuhaJam();
  JSONData["mDhu"] = jws.dhuhaMenit();
  JSONData["hDzu"] = jws.dzuhurJam();
  JSONData["mDzu"] = jws.dzuhurMenit();
  JSONData["hAsh"] = jws.asharJam();
  JSONData["mAsh"] = jws.asharMenit();
  JSONData["hMag"] = jws.maghribJam();
  JSONData["mMag"] = jws.maghribMenit();
  JSONData["hIsy"] = jws.isyaJam();
  JSONData["mIsy"] = jws.isyaMenit();
  char data[420];
  serializeJson(JSONData, data);
  server.send(200, "application/json", data);
}

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("TAQWA");
  Serial.print("Version: ");
  Serial.println(version);

  segment.begin();
  segment.Hapus_Jam();
  segment.Hapus_Jadwal();
  segment.Hapus_Kalender();
  segment.Scanning_Segment();
  segment.displayStart();
  segment.Scanning_Segment();
  Serial.println("DISPLAY");

  jws.begin();
  Serial.println("HISAB");

  IO.begin();
  pinMode(pinDip, OUTPUT);
  digitalWrite(pinDip, HIGH);
  Serial.println("I/O");

  Disp.start();
  Disp.setBrightness(15);
  Serial.println("LED P10 Running");
  Disp.clear();

  // ===== Web Server Access Point  =====
  Serial.println();
  Serial.println("== Web Server Configuration ==");

  wifi_begin();
  server.begin();
  serverOnIndex();
  serverOnWaktu();
  serverOnKoordinat();
  serverOnIkhtiyat();
  serverOnIqomah();
  serverOnDisplay();
  serverOnPerangkat();
  serverOnTilawah();
  serverOnAlarm();
  serverOnTv();
  serverOnTvi();
  serverOnWifi();
  serverOnCloud();

  server.on("/api/masjid", HTTP_GET, JsonMasjid);
  server.on("/api", HTTP_POST, receiveData);

  Serial.println("Server On");

  // ====== Cloud ======
  Serial.println();
  Serial.println("Cloud");
  cloud_begin();
  updateTeksBesarFromWeb();

  // ====== Data Masjid ======
  Serial.println();
  Serial.println("Data Masjid:");
  Serial.println(memori.getMasjid());
  Serial.println(memori.getAlamat());
  Serial.println(memori._getAlamat());
  Serial.println();
  Serial.println("domain: ");
  Serial.print("https://");
  Serial.print(memori.getDomain());
  Serial.print(".shatomedia.com");
  Serial.println();

  // ===== Routin DFPlayer Audio =====
  Serial.println();
  Serial.println("Audio");
  mp3_set_serial(Serial);
  setVolume();
  mp3_play(1);
  Serial.println("check");

  // ============ Manual ===========
  Serial.println();
  Serial.println("= Starting =");

  // Setup OTA endpoints
  setupOTAEndpoints();

  // Opsional: Cek update saat startup
  delay(5000); // Tunggu WiFi stabil
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Checking for updates at startup...");
    FirmwareInfo info = checkForUpdate();
    if (info.hasUpdate) {
      Serial.println("Update tersedia saat startup: " + info.version);
      // Uncomment jika ingin auto-update saat startup
      // performOTAUpdate(info.downloadURL);
    }
  }
}


/* ============================================ 
      Program Utama Jadwal Waktu Sholat
   ========================================= */
void handleWebServer() {
  server.handleClient();
}
void updateP10Time() {
  Data_Jam   = waktu.jam();
  Data_Menit = waktu.menit();
  Data_Detik = waktu.detik();
}
void updateDisplayAndSchedule() {
  segment.restoreJadwal();
  segment.restoreWaktu();
}
void processAlarms() {
  scanningSholat();
  //scanTilawah();
  //ScanAlarm();
}
void handleRelay() {
  if (IO.tandaRelay() == LOW) {
    if (waktu.detik() == 30) {
      if (IO.tandaBusy() == HIGH)
        IO.relayOff();
    }
  }
}
void updateSecondIndicator() {
  static unsigned long konter = 5000;
  static unsigned long last2 = 0;
  static int _konter = 0;
  if (_konter != segment.detikan()) {
    _konter = segment.detikan();
    konter = 1000;
  }
  if (WiFi.softAPgetStationNum() == 1)
    konter = 500;
  else if (WiFi.softAPgetStationNum() == 2)
    konter = 250;
  else if (WiFi.softAPgetStationNum() == 3)
    konter = 100;
  if ((millis() - last2) >= konter) {
    digitalWrite(pinDip, digitalRead(pinDip) ^ 1);
    last2 = millis();
  }
}

unsigned long lastTeksUpdate = 0;
void LEDP10(){
  unsigned long sekarang = millis();
  updateP10Time();
  if (stateDisplay == 0) {
    TampilkanLayoutUtama();
    if (sekarang - waktuDisplay >= 180000) {
      stateDisplay = 1;
      waktuDisplay = sekarang;
    }
  } else {
    TampilkanTeksBesar();
    if (sekarang - waktuDisplay >= 70000) {
      stateDisplay = 0;
      waktuDisplay = sekarang;
    }
  }
  if (millis() - lastTeksUpdate > 300000) {
    updateTeksBesarFromWeb();
    lastTeksUpdate = millis();
  }
  Disp.loop();
}

void loop() {
  handleWebServer();
  
  // Auto check update (setiap 1 jam)
  autoUpdateCheck();
  
  static unsigned long lastAlarm = 0;
  if ((millis() - lastAlarm) >= 300) {
    lastAlarm = millis();
    //updateDisplayAndSchedule();
    processAlarms();
    //handleRelay();
  }
  LEDP10();
}