/*==============================================================
          ALAMAT MEMORY EEPROM PENYIMPAN HASIL SETTING
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
/*==============================================================*/
void handleGetIqomah()
{
  int detik = waktu.detik();
  char istr[1];
  if (detik <= 10)
  {
    sprintf(istr, " Shubuh : %d ", memori.iqomahShubuh());
    server.send(200, "text/plane", istr);
  }
  if (detik <= 20)
  {
    sprintf(istr, " Dzuhur : %d ", memori.iqomahDzuhur());
    server.send(200, "text/plane", istr);
  }
  if (detik <= 30)
  {
    sprintf(istr, " Ashar : %d ", memori.iqomahAshar());
    server.send(200, "text/plane", istr);
  }
  if (detik <= 40)
  {
    sprintf(istr, " Maghrib : %d ", memori.iqomahMaghrib());
    server.send(200, "text/plane", istr);
  }
  if (detik <= 50)
  {
    sprintf(istr, " Isya : %d ", memori.iqomahIsya());
    server.send(200, "text/plane", istr);
  }
}

/* ==================================== */
void handleSetIqomah()
{
  int T_Alamat;
  String data_iqomah = server.arg("dataIqomah");
  memori.setIqomah(data_iqomah);
  Serial.print("Iqomah :");
  memori.testIqomah();
  tandaSimpan();
}

/*==============================================================*/
void handleGetAdzan()
{
  const int a = memori.getAdzan();
  if (a == LOW)
  {
    server.send(200, "text/plane", " OFF ");
  }
  else if (a == HIGH)
  {
    server.send(200, "text/plane", " ON ");
  }
}

void handleSetAdzan()
{
  String adzan = server.arg("dataAdzan");
  memori.setAdzan(adzan);
  Serial.print("Adzan :");
  Serial.println(adzan);
  Serial.print("Test :");
  Serial.println(memori.getAdzan());
  tandaSimpan();
}

/*==============================================================*/
void handleGetSirine()
{
  const int a = memori.getSirine();
  if (a == LOW)
  {
    server.send(200, "text/plane", " OFF ");
  }
  else if (a == HIGH)
  {
    server.send(200, "text/plane", " ON ");
  }
}

void handleSetSirine()
{
  String sirine = server.arg("dataSirine");
  memori.setSirine(sirine);
  Serial.print("Sirine :");
  Serial.println(sirine);
  Serial.print("Test :");
  Serial.println(memori.getSirine());
  tandaSimpan();
}

/* =====================================================
    Layanan Iqomah

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnIqomah()
{
  server.on("/setIqomah", handleSetIqomah);
  server.on("/setAdzan", handleSetAdzan);
  server.on("/setSirine", handleSetSirine);

  server.on("/getIqomah", handleGetIqomah);
  server.on("/getAdzan", handleGetAdzan);
  server.on("/getSirine", handleGetSirine);
}

/* ===================================================== */