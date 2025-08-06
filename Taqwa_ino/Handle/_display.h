/*==============================================================
          ALAMAT MEMORY EEPROM PENYIMPAN HASIL SETTING
                    By. SHATOMEDIA (Safix)
  ==============================================================*/

/*=============================================================*/
void handleGetDisplay()
{
  char str[6];
  sprintf(str, "%d", memori.getDisplay());
  server.send(200, "text/plane", str);
}

void handleSetDisplay()
{
  String dataDisplay = server.arg("dataDisplay");
  memori.setDisplay(dataDisplay);
  Serial.print("Display Mode :");
  Serial.println(dataDisplay);
  Serial.print(F("Mode "));
  Serial.println(memori.getDisplay());
  Serial.print(F("Logic "));
  Serial.println(memori.getLogika());
  tandaSimpan();
}

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnDisplay()
{
  server.on("/setDisplay", handleSetDisplay);
  server.on("/getDisplay", handleGetDisplay);
}
/* ========================================== */