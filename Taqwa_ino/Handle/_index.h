/*==============================================================
                     Pick-Up Data DS3231
                    By. SHATOMEDIA (Safix)
  ==============================================================*/


/*=====================================*/
void handleRoots()
{
  String s;
  s += "<html><body><br><br><h3>Lakukan Update Aplikasi</h3><a>Halaman sudah tidak didukung lagi...</a><br><br><a href=";
  s += "https://play.google.com/store/apps/details?id=com.shatomedia.taqwa>";
  s += "Link Instalasi</a></body></html>";
  server.send(200, "text/html", s);
}

/*=====================================*/
void handleGetVersion()
{
  server.send(200, "text/plane", version);
}
/*=====================================*/
void handleGetSerial()
{
  String ssid = "TAQWA_";
  // ssid += memori.getWifi();
  ssid += WiFi.softAPmacAddress();
  server.send(200, "text/html", ssid);
}
/*=====================================*/
void handleGetConnect()
{
  String ssid = "Connect";
  server.send(200, "text/html", ssid);
}
/*=====================================
void handleGetPembuatan() {
  server.send(200, "text/plane", tahun);
}*/
/*=====================================
void handleGetDevelop() {
  server.send(200, "text/plane", develop);
}*/

/*=====================================*/
void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnIndex()
{
  server.on("/", handleRoots);

  server.on("/getConnect", handleGetConnect);
  server.on("/getVersion", handleGetVersion);
  server.on("/getSerial", handleGetSerial);
  // server.on("/getDevelop",  handleGetDevelop);
  // server.on("/getPembuatan",handleGetPembuatan);

  server.onNotFound(handle_NotFound);
}