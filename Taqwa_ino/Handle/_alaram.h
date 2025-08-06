/*==============================================================
    This routine is executed when you open its IP in browser
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
static int alamatData;

/* ============================================================= */
void handleSetAlarm()
{
  String dataSet = server.arg("dataAlarm");
  memori.setAlarm(dataSet);
  Serial.print("Set Alarm :");
  Serial.println(dataSet);
  tandaSimpan();
}

/* ============================================================= */
void handleGetAlarm()
{
  String getHari = server.arg("hariAlarm");
  memori.getAlarm(getHari);
  Serial.print("Alarm Day :");
  Serial.println(getHari);
  tandaSimpan();
}

/* ============================================================= */

void handleAlarm01()
{
  char str[3];
  sprintf(str, "%d : %d  -  %d", memori.alarmJam01(), memori.alarmMenit01(), memori.alarmMp01());
  server.send(200, "text/plane", str);
}
void handleAlarm02()
{
  char str[3];
  sprintf(str, "%d : %d  -  %d", memori.alarmJam02(), memori.alarmMenit02(), memori.alarmMp02());
  server.send(200, "text/plane", str);
}
void handleAlarm03()
{
  char str[3];
  sprintf(str, "%d : %d  -  %d", memori.alarmJam03(), memori.alarmMenit03(), memori.alarmMp03());
  server.send(200, "text/plane", str);
}
void handleAlarm04()
{
  char str[3];
  sprintf(str, "%d : %d  -  %d", memori.alarmJam04(), memori.alarmMenit04(), memori.alarmMp04());
  server.send(200, "text/plane", str);
}
void handleAlarm05()
{
  char str[3];
  sprintf(str, "%d : %d  -  %d", memori.alarmJam05(), memori.alarmMenit05(), memori.alarmMp05());
  server.send(200, "text/plane", str);
}
/* ============================================================= */

/*==============================================================
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
void ScanJam()
{
  int DataAlarm;
  DataAlarm = memori.bacaMemori(alamatData);
  // Serial.print(memori.bacaMemori(alamatData));
  // Serial.print(" == ");
  // Serial.println(waktu.jam());

  if (DataAlarm == waktu.jam())
  {
    alamatData++;
    // Serial.print("JAM : ");
    // Serial.print(waktu.jam());
    // Serial.print(" = ");
    // Serial.println(DataAlarm);

    DataAlarm = memori.bacaMemori(alamatData);
    // Serial.print("MENIT : ");
    // Serial.print(waktu.menit());
    // Serial.print(" = ");
    // Serial.println(DataAlarm);

    if (DataAlarm == waktu.menit())
    {
      IO._tandaSimpan();
      // tanda_relay   = LOW;
      // digitalWrite(Relay, LOW);
      // delay (3000);

      Serial.println("ALARM ON");
      setVolume();
      // Data_Volume = EEPROM.read ( alamatSettingVolume );
      // mp3_set_volume (Data_Volume);
      // Serial.print("Volume : ");
      // Serial.println(Data_Volume);
      // delay (500);
      // setVolumeAudio();
      alamatData++;
      DataAlarm = memori.bacaMemori(alamatData);
      mp3_play(DataAlarm);
      // mp3File(DataAlarm);
      Serial.print("Musik : ");
      Serial.println(DataAlarm);
    }
  }
}
/*==============================================================
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
void ScanAlarm()
{
  if (waktu.detik() == 0)
  {
    if (waktu.jam() != 0)
    {
      int AlarmHari = memori.pilihAlarmHari();

      alamatData = AlarmHari;
      ScanJam();
      alamatData = 3 + AlarmHari;
      ScanJam();
      alamatData = 6 + AlarmHari;
      ScanJam();
      alamatData = 9 + AlarmHari;
      ScanJam();
      alamatData = 12 + AlarmHari;
      ScanJam();
    }
  }
}
/*==============================================================*/

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnAlarm()
{
  server.on("/setAlarm", handleSetAlarm);
  server.on("/getAlarm", handleGetAlarm);
  server.on("/Alarm01", handleAlarm01);
  server.on("/Alarm02", handleAlarm02);
  server.on("/Alarm03", handleAlarm03);
  server.on("/Alarm04", handleAlarm04);
  server.on("/Alarm05", handleAlarm05);
}
/*==============================================================*/