#ifndef _OTA_H
#define _OTA_H

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

// Konfigurasi OTA
extern const char* currentVersion;
extern ESP8266WebServer server;

// Struktur info firmware
struct FirmwareInfo {
  String version;
  String downloadURL;
  bool hasUpdate;
  String releaseNotes;
};

// Konfigurasi GitHub
const char* githubRepo = "https://api.github.com/repos/shatomedia/taqwa-firmware/releases/latest";
const char* firmwareBaseURL = "https://github.com/shatomedia/taqwa-firmware/releases/download/";

// Fungsi utama OTA
FirmwareInfo checkForUpdate();
void performOTAUpdate(String downloadURL);
void autoUpdateCheck();
void setupOTAEndpoints();
void otaUpdateFromGitHub();

// Implementasi fungsi
FirmwareInfo checkForUpdate() {
  FirmwareInfo info;
  info.hasUpdate = false;
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi tidak terhubung untuk cek update");
    return info;
  }

  HTTPClient http;
  WiFiClient client;
  
  Serial.println("Checking for updates from GitHub...");
  
  if (http.begin(client, githubRepo)) {
    http.addHeader("User-Agent", "TAQWA-ESP8266");
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      StaticJsonDocument<2048> doc;
      DeserializationError error = deserializeJson(doc, payload);
      
      if (!error) {
        info.version = doc["tag_name"].as<String>();
        info.releaseNotes = doc["body"].as<String>();
        
        // Cek apakah ada update (bandingkan versi)
        if (info.version != currentVersion && info.version.length() > 0) {
          info.hasUpdate = true;
          info.downloadURL = String(firmwareBaseURL) + info.version + "/Taqwa_ino.ino.bin";
          Serial.println("Update tersedia: " + info.version);
          Serial.println("Current: " + String(currentVersion));
        } else {
          Serial.println("Firmware sudah terbaru: " + String(currentVersion));
        }
      } else {
        Serial.println("Gagal parsing response GitHub API");
      }
    } else {
      Serial.printf("HTTP Error saat cek update: %d\n", httpCode);
    }
    http.end();
  } else {
    Serial.println("Gagal koneksi ke GitHub API");
  }
  
  return info;
}

void performOTAUpdate(String downloadURL) {
  Serial.println("=== MEMULAI OTA UPDATE ===");
  Serial.println("URL: " + downloadURL);
  Serial.println("Free Heap sebelum update: " + String(ESP.getFreeHeap()));
  
  // Set progress callback (opsional)
  ESPhttpUpdate.onProgress([](int progress, int total) {
    Serial.printf("Progress: %d%% (%d/%d bytes)\n", (progress * 100) / total, progress, total);
  });
  
  // Set error callback (opsional)
  ESPhttpUpdate.onError([](int error) {
    Serial.printf("OTA Error: %d\n", error);
  });
  
  // Mulai update
  WiFiClient client;
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, downloadURL);
  
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.println("=== OTA UPDATE GAGAL ===");
      Serial.printf("Error (%d): %s\n", 
        ESPhttpUpdate.getLastError(), 
        ESPhttpUpdate.getLastErrorString().c_str());
      break;
      
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("=== TIDAK ADA UPDATE ===");
      break;
      
    case HTTP_UPDATE_OK:
      Serial.println("=== OTA UPDATE BERHASIL ===");
      Serial.println("Restarting dalam 3 detik...");
      delay(3000);
      ESP.restart();
      break;
  }
}

void autoUpdateCheck() {
  static unsigned long lastCheck = 0;
  const unsigned long checkInterval = 3600000; // Cek setiap 1 jam
  
  if (millis() - lastCheck > checkInterval) {
    lastCheck = millis();
    Serial.println("Auto-checking for updates...");
    
    FirmwareInfo updateInfo = checkForUpdate();
    if (updateInfo.hasUpdate) {
      Serial.println("Auto-updating firmware to: " + updateInfo.version);
      performOTAUpdate(updateInfo.downloadURL);
    }
  }
}

void setupOTAEndpoints() {
  // Endpoint untuk cek update
  server.on("/api/check-update", HTTP_GET, []() {
    Serial.println("API: Checking for updates...");
    FirmwareInfo info = checkForUpdate();
    
    StaticJsonDocument<500> doc;
    doc["currentVersion"] = currentVersion;
    doc["latestVersion"] = info.version;
    doc["hasUpdate"] = info.hasUpdate;
    doc["downloadURL"] = info.downloadURL;
    doc["releaseNotes"] = info.releaseNotes;
    doc["freeHeap"] = ESP.getFreeHeap();
    doc["chipId"] = ESP.getChipId();
    
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
  });
  
  // Endpoint untuk trigger update
  server.on("/api/update", HTTP_POST, []() {
    Serial.println("API: Manual update triggered");
    FirmwareInfo info = checkForUpdate();
    
    if (info.hasUpdate) {
      StaticJsonDocument<200> doc;
      doc["status"] = "updating";
      doc["message"] = "Update dimulai ke versi " + info.version;
      doc["version"] = info.version;
      
      String response;
      serializeJson(doc, response);
      server.send(200, "application/json", response);
      
      // Delay agar response terkirim
      delay(2000);
      performOTAUpdate(info.downloadURL);
    } else {
      StaticJsonDocument<200> doc;
      doc["status"] = "no-update";
      doc["message"] = "Firmware sudah terbaru";
      doc["currentVersion"] = currentVersion;
      
      String response;
      serializeJson(doc, response);
      server.send(200, "application/json", response);
    }
  });
  
  // Endpoint info firmware
  server.on("/api/firmware-info", HTTP_GET, []() {
    StaticJsonDocument<400> doc;
    doc["version"] = currentVersion;
    doc["buildDate"] = __DATE__;
    doc["buildTime"] = __TIME__;
    doc["freeHeap"] = ESP.getFreeHeap();
    doc["chipId"] = ESP.getChipId();
    doc["flashChipSize"] = ESP.getFlashChipSize();
    doc["sdkVersion"] = ESP.getSdkVersion();
    doc["coreVersion"] = ESP.getCoreVersion();
    doc["uptime"] = millis();
    
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
  });
  
  // Endpoint restart
  server.on("/api/restart", HTTP_POST, []() {
    server.send(200, "application/json", "{\"status\":\"restarting\",\"message\":\"Perangkat akan restart dalam 3 detik\"}");
    delay(3000);
    ESP.restart();
  });
}

// Fungsi simple OTA (untuk kompatibilitas)
void otaUpdateFromGitHub() {
  FirmwareInfo info = checkForUpdate();
  if (info.hasUpdate) {
    performOTAUpdate(info.downloadURL);
  } else {
    Serial.println("Tidak ada update tersedia");
  }
}

#endif