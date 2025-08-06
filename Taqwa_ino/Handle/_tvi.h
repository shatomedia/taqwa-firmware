/*==============================================================
                     Pick-Up Data DS3231
                    By. SHATOMEDIA (Safix)
  ==============================================================*/

/*==============================================================*/
//          PAGES HTML = waktu.h
/*==============================================================*/

void handleSetMasjid()
{
  String masjid = server.arg("masjid");
  memori.setMasjid(masjid);
  Serial.print("Save Nama Masjid : ");
  Serial.println(masjid);
  Serial.print("Test :");
  Serial.println(memori.getMasjid());
  tandaSimpan();
}

void handleSetAlamat()
{
  String alamat = server.arg("alamat");
  memori.setAlamat(alamat);
  Serial.print("Save Alamat Masjid 1 :");
  Serial.println(alamat);
  Serial.print("Test :");
  Serial.println(memori.getAlamat());
  tandaSimpan();
}

void _handleSetAlamat()
{
  String alamat = server.arg("_alamat");
  memori._setAlamat(alamat);
  Serial.print("Save Alamat Masjid 2 :");
  Serial.println(alamat);
  Serial.print("Test :");
  Serial.println(memori._getAlamat());
  tandaSimpan();
}

void handleSetTheme()
{
  String theme = server.arg("dataTheme");
  memori.setTheme(theme);
  Serial.print("Save Theme :");
  Serial.println(theme);
  Serial.print("Test :");
  Serial.println(memori.getTheme());
  tandaSimpan();
}

void handleGetMasjid()
{
  server.send(200, "text/html", memori.getMasjid());
}
void handleGetAlamat()
{
  server.send(200, "text/html", memori.getAlamat());
}
void _handleGetAlamat()
{
  server.send(200, "text/html", memori._getAlamat());
}

// void handleGetTheme() {
//   server.send(200, "text/html", memori.getTheme());
// }

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnTvi()
{
  server.on("/setMasjid", handleSetMasjid);
  server.on("/setAlamat", handleSetAlamat);
  server.on("/_setAlamat", _handleSetAlamat);
  server.on("/setTheme", handleSetTheme);

  server.on("/getMasjid", handleGetMasjid);
  server.on("/getAlamat", handleGetAlamat);
  server.on("/_getAlamat", _handleGetAlamat);
  // server.on("/getTheme",       handleGetTheme);
}
/* ===================================================== */
