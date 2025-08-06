/*==============================================================
                     Pick-Up Data DS3231
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
bool modeWifi = false;
//==========================
IPAddress ipAP(192, 168, 1, 111);  // IP Akses Point yang dibuat
IPAddress ipSTA(192, 168, 1, 111); // IP permintaan ke Router
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

/* ================================================
    Program akan memilih koneksifitas
    Apabila router jaringan tidak terhubung
    maka akan dialihkan ke mode AP
/* ================================================ */
void wifi_begin() {
  Serial.println();
  Serial.println("STATION");

  WiFi.mode(WIFI_AP_STA); // AP+STA mode

  WiFi.softAPdisconnect(true);
  WiFi.config(ipSTA, gateway, subnet, IPAddress(8,8,8,8));
  WiFi.begin(memori.getSSID(), memori.getPassword());

  for (int x = 0; x <= 19; x++) {
    if (WiFi.status() == WL_CONNECTED) {
      x = 20;
      modeWifi = true;
      WiFi.persistent(true);
      Serial.println();
      Serial.print("Client : "); Serial.println(memori.getSSID());
      Serial.print("IP  : "); Serial.println(WiFi.localIP());
    } else {
      Serial.print(".");
      delay(500);
    }
  }

  // AP tetap aktif meski STA connect
  String ssid = "TAQWA_" + WiFi.softAPmacAddress();
  String password = ""; // Ganti sesuai kebutuhan
  WiFi.softAPConfig(ipAP, gateway, subnet);
  WiFi.softAP(ssid.c_str(), password.c_str());

  Serial.println("AP  : " + ssid);
  Serial.println("pass: " + password);
  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());
}

/* ================================================ */
void handleScanWiFi()
{
  int n = WiFi.scanNetworks();
  if (n == 0)
    server.send(200, "text/plane", "Tidak ada Jaringan");
  else
  {
    String wifi;
    wifi = String(n);
    wifi += " Terdeteksi: <br><br>";

    for (int i = 0; i < n; ++i)
    {
      wifi += WiFi.SSID(i);
      wifi += "  >>  ";
      wifi += String(WiFi.RSSI(i));
      wifi += " dBm";
      wifi += "<br>";
      delay(10);
    }
    server.send(200, "text/plane", wifi);
  }
}

/*=====================================*/
void handleScanClient()
{
  String n = String(WiFi.softAPgetStationNum());
  server.send(200, "text/plane", n);
}

void handleModeWiFi()
{
  if (modeWifi == true)
  {
    server.send(200, "text/plane", "Online");
  }
  else
  {
    server.send(200, "text/plane", "Offline");
  }
}

/*=====================================*/
void handleSetSSID()
{
  String ssid = server.arg("ssid");
  memori.setSSID(ssid);
  Serial.print("Save SSID Router : ");
  Serial.println(ssid);
  Serial.print("SSID :");
  Serial.println(memori.getSSID());
  tandaSimpan();
}

void handleSetPassword()
{
  String password = server.arg("password");
  memori.setPassword(password);
  Serial.print("Save Password Router : ");
  Serial.println(password);
  Serial.print("Password :");
  Serial.println(memori.getPassword());
  tandaSimpan();
}

/*
void handleSetWifi() {
  String namaWifi = server.arg("namaWifi");
  memori.setWifi(namaWifi);
  Serial.print("Save WiFi: ");
  Serial.println(namaWifi);
  Serial.print("WiFi :");
  Serial.println(memori.getWifi());
  tandaSimpan();
}

/*=====================================*/
void handleGetSSID()
{
  server.send(200, "text/html", memori.getSSID());
}
void handleGetPassword()
{
  server.send(200, "text/html", memori.getPassword());
}
void handleGetWifi()
{
  String wifi = "TAQWA_";
  // wifi += memori.getWifi();
  wifi += WiFi.softAPmacAddress();
  server.send(200, "text/html", wifi);
}

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnWifi()
{
  server.on("/scanWiFi", handleScanWiFi);
  server.on("/scanClient", handleScanClient);
  server.on("/modeWiFi", handleModeWiFi);

  server.on("/setSSID", handleSetSSID);
  server.on("/getSSID", handleGetSSID);
  server.on("/setPassword", handleSetPassword);
  server.on("/getPassword", handleGetPassword);

  // server.on("/setWifi",     handleSetWifi);
  server.on("/getWifi", handleGetWifi);
}
