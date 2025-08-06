
/*==============================================================
                    By. SHATOMEDIA (Safix)
  ==============================================================*/

//=================================
static int temp_alarm;
static int temp_waktu;
static int temp_hari;

/*==============================================================
                Tilawah Sebelum Waktu Sholat
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
void handleSetTilawah()
{
  String dataSet = server.arg("dataTilawah");
  memori.setTilawah(dataSet);
  Serial.print("Setting Tilawah :");
  Serial.println(dataSet);
  tandaSimpan();
}

//=================================
void handleGetTilawah()
{
  String getHari = server.arg("getHariTilawah");
  memori.getTilawah(getHari);
  Serial.print("daftar Tilawah :");
  Serial.println(getHari);
  tandaSimpan();
}

/* ============================================================= */

void handleTilawahImsyak()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahImsyakJam(), memori.tilawahImsyakMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahShubuh()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahShubuhJam(), memori.tilawahShubuhMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahSyuruq()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahSyuruqJam(), memori.tilawahSyuruqMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahDhuha()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahDhuhaJam(), memori.tilawahDhuhaMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahDzuhur()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahDzuhurJam(), memori.tilawahDzuhurMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahAshar()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahAsharJam(), memori.tilawahAsharMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahMaghrib()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahMaghribJam(), memori.tilawahMaghribMp3());
  server.send(200, "text/plane", str);
}
void handleTilawahIsya()
{
  char str[2];
  sprintf(str, "%d - %d", memori.tilawahIsyaJam(), memori.tilawahIsyaMp3());
  server.send(200, "text/plane", str);
}
/* ============================================================= */

/*==============================================================
                    ROUTIN DFPLAYER SYSTEM
                    By. SHATOMEDIA (Safix)
  ==============================================================*/

void hidupkan()
{
  // mp3_play(EEPROM.read(temp_alarm + 1));
  IO.relayOn();
  delay(500);
  mp3_play(memori.bacaMemori(temp_alarm + 1));
  // mp3File(memori.bacaMemori(temp_alarm + 1));
  // Serial.println("Relay dihidupkan");
  // digitalWrite(Relay, LOW);
  delay(2000);
}
/*======================================*/

void hitung_Alarm_Nyata()
{
  // int a = EEPROM.read(temp_alarm);
  int a = memori.bacaMemori(temp_alarm);
  if (a != 0)
  {
    byte j = waktu.jam();
    byte m = waktu.menit();

    for (int b = a; b >= 1; b--)
    {
      m++;
      if (m >= 60)
      {
        m = 0;
        j++;
      }
    }
    /*
        Serial.print(j);
        Serial.print(":");
        Serial.println(m);
    */
    switch (temp_waktu)
    {
      Serial.print("Alarm Sebelum ");
    case 1:
      if (j == jws.imsyakJam())
      {
        if (m == jws.imsyakMenit())
        {
          Serial.println("Imsyak");
          hidupkan();
        }
      }
      break;
    case 2:
      if (j == jws.shubuhJam())
      {
        if (m == jws.shubuhMenit())
        {
          Serial.println("Shubuh");
          hidupkan();
        }
      }
      break;
    case 3:
      if (j == jws.syuruqJam())
      {
        if (m == jws.syuruqMenit())
        {
          Serial.println("Syuruq");
          hidupkan();
        }
      }
      break;
    case 4:
      if (j == jws.dhuhaJam())
      {
        if (m == jws.dhuhaMenit())
        {
          Serial.println("Dhuha");
          hidupkan();
        }
      }
      break;
    case 5:
      if (j == jws.dzuhurJam())
      {
        if (m == jws.dzuhurMenit())
        {
          Serial.println("Dzuhur");
          hidupkan();
        }
      }
      break;
    case 6:
      if (j == jws.asharJam())
      {
        if (m == jws.asharMenit())
        {
          Serial.println("Ashar");
          hidupkan();
        }
      }
      break;
    case 7:
      if (j == jws.maghribJam())
      {
        if (m == jws.maghribMenit())
        {
          Serial.println("Maghrib");
          hidupkan();
        }
      }
      break;
    case 8:
      if (j == jws.isyaJam())
      {
        if (m == jws.isyaMenit())
        {
          Serial.println("Isya");
          hidupkan();
        }
      }
      break;
    }
  }
}

void scanTilawah()
{
  if (waktu.detik() == 5)
  {
    temp_hari = memori.pilihTilawahSholat();
    /*
    switch (hari) {
      case 1: temp_hari = (alamatTilawahAhad); break;
      case 2: temp_hari = (alamatTilawahSenin); break;
      case 3: temp_hari = (alamatTilawahSelasa); break;
      case 4: temp_hari = (alamatTilawahRabu); break;
      case 5: temp_hari = (alamatTilawahKamis); break;
      case 6: temp_hari = (alamatTilawahJumat); break;
      case 7: temp_hari = (alamatTilawahSabtu); break;
    }*/
    temp_alarm = temp_hari;
    temp_waktu = 1;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 2;
    temp_waktu = 2;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 4;
    temp_waktu = 3;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 6;
    temp_waktu = 4;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 8;
    temp_waktu = 5;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 10;
    temp_waktu = 6;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 12;
    temp_waktu = 7;
    hitung_Alarm_Nyata();
    temp_alarm = temp_hari + 14;
    temp_waktu = 8;
    hitung_Alarm_Nyata();
    temp_waktu = 0;
  }
}

/* ===================================================== */

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/

void serverOnTilawah()
{
  server.on("/setTilawah", handleSetTilawah);
  server.on("/getTilawah", handleGetTilawah);
  server.on("/tilawahImsyak", handleTilawahImsyak);
  server.on("/tilawahShubuh", handleTilawahShubuh);
  server.on("/tilawahSyuruq", handleTilawahSyuruq);
  server.on("/tilawahDhuha", handleTilawahDhuha);
  server.on("/tilawahDzuhur", handleTilawahDzuhur);
  server.on("/tilawahAshar", handleTilawahAshar);
  server.on("/tilawahMaghrib", handleTilawahMaghrib);
  server.on("/tilawahIsya", handleTilawahIsya);
}

/* ===================================================== */