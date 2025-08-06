/*==============================================================
          ALAMAT MEMORY EEPROM PENYIMPAN HASIL SETTING
                    By. SHATOMEDIA (Safix)
  ==============================================================*/

/* =====================================================
String mp3Play = "0";
float _mp3File = 0;
float _mp3Vol  = 0;
String tx ;
bool bufferAT = false;
bool relayAT  = false;

/* =====================================================
String intToString3(float data){
  String a;
  a += int (data / 100);
  a += int ((((data / 100) - int (data / 100))) * 10);
  a += int (((((data / 100) - int (data / 100)) * 10) - int(((((data / 100) - int (data / 100))) * 10))) * 10);
  return a;
}

String intToString2(float data){
  String a;
  a += int ((((data / 100) - int (data / 100))) * 10);
  a += int (((((data / 100) - int (data / 100)) * 10) - int(((((data / 100) - int (data / 100))) * 10))) * 10);
  return a;
}

/* =====================================================
void handleDPT(){
  tx  = "AT";                         // 2 digit indikator
  tx += String(IO.statusRelay()^1);  // 1 digit Relay on/off   //0 = Off, 1 = on
  tx += String(mp3Play);              // 1 digit play / stop // 0 = defaut, 1 = Stop, 2 = Play
  tx += intToString3(_mp3File);       // 3 digit File MP3
  _mp3Vol = memori.getVolume();       // 2 digit Volume
  tx += intToString2(_mp3Vol);
  server.send(200, "text/plane", tx);
  mp3Play  = "0";
  _mp3File = 0;
}

String kirimDPT(){
  tx  = "AT";                         // 2 digit indikator
  tx += String(IO.statusRelay()^1);   // 1 digit Relay on/off   //0 = Off, 1 = on
  tx += String(mp3Play);              // 1 digit play / stop // 0 = defaut, 1 = Stop, 2 = Play
  tx += intToString3(_mp3File);       // 3 digit File MP3
  _mp3Vol = memori.getVolume();       // 2 digit Volume
  tx += intToString2(_mp3Vol);
  return tx; }

/* =====================================================
void mp3Default(){
  mp3Play = "0";
}

void mp3Stop()   {
  mp3Play = "1";
}

void mp3File(int file){
  _mp3File = file;
  mp3Play = "2";
}

/* =====================================================

/*
void handleBufferOn(){
  bufferAT = true;
  server.send(200, "text/plane", "OK");
}

void handleBufferOff(){
  bufferAT = false;
  server.send(200, "text/plane", "OK");
}

void handleMp3On(){
  mp3Play  = "0";
  _mp3File = 0;
  server.send(200, "text/plane", "Mp3 play to default");
}

void handleMp3Off(){
  mp3Play  = "0";
  _mp3File = 0;
  server.send(200, "text/plane", "Mp3 Stop default");
}*/

/* =====================================================
void handleRx(){
  String status[4] = server.arg("status");

  Serial.println(server.arg(status[1]));


  if (status[0] == "O"){
    if (status[1] == "K") {             //repond AT > 0 = not OK, 1 = OK
      _mp3File = 0;
      mp3Play = "0";
    } else if (status[2] == "0") relayAT  = false;                 //Mp3 Off
      else if (status[2] == "1") relayAT  = true;                  //Mp3 On
      else if (status[3] == "0") bufferAT = false;                 //Mp3 Off
      else if (status[3] == "1") bufferAT = true;                  //Mp3 On
  }
}
*/

/*============ Setting Volume Suara ==========================*/
void setVolume()
{
  // Serial.println("Read Volume");
  mp3_set_volume(memori.getVolume());
  Serial.print(" Gain: ");
  Serial.println(memori.getVolume());
  mp3_set_EQ(0);
  Serial.print(" eq: ");
  Serial.println(0);
}

/*=====================================*/
void tandaSimpan()
{
  IO._tandaSimpan();
  mp3_play(ding); // 8 = file mp3 ding
}

/*=====================*/
void handleGetVolume()
{
  char str[3];
  sprintf(str, " %d ", memori.getVolume());
  server.send(200, "text/plane", str);
}

/*=====================*/
void handleSetVolume()
{
  String volume = server.arg("dataVolume");
  memori.setVolume(volume);
  Serial.println("Vol. Save");
  setVolume();
  Serial.println("Volume Set");
  // tandaSimpan();
  // mp3_play(1);
  Serial.println("Vol. Test");
  // mp3File(ding);
  delay(500);
}

/*==============================================================*/
void handleSetPlay()
{
  String p = server.arg("dataPlay");
  Serial.print("PLAY = ");
  Serial.println(p);
  if (p[3] == '.')
  {
    int s = ((p[0] - 48) * 100) + ((p[1] - 48) * 10) + (p[2] - 48);
    if (s == 0)
    {
      // mp3_stop();

      // mp3Stop();

      tandaSimpan();
      delay(200);
      Serial.println("Not Found");
    }
    else if (s != 0)
    {
      IO.amplifierOn();
      mp3_play(s);

      // mp3File(s);

      delay(500);
      Serial.println("Playing");
    }
  }
}

/*==============================================================*/
void handleSetRelay()
{
  String relayState = "OFF";
  String t_state = server.arg("relayState");
  Serial.print("Ampli = ");
  Serial.println(t_state);
  if (t_state == "1")
  {
    Serial.println("ON");
    IO.amplifierOn();
    relayState = "ON"; // Feedback parameter
  }
  else
  {
    mp3_stop();
    Serial.println("OFF");
    IO.amplifierOff();
    relayState = "OFF"; // Feedback parameter

    // mp3Stop();//==
  }
  server.send(200, "text/plane", relayState); // Send web page
}

/*=====================================*/
void handleGetMAC1()
{
  String wifi = memori.getMAC1();
  server.send(200, "text/html", wifi);
}

void handleSetMAC1()
{
  String namaMAC = server.arg("dataMAC1");
  memori.setMAC1(namaMAC);
  Serial.print("Save MAC : ");
  Serial.println(namaMAC);
  Serial.print("MAC :");
  Serial.println(memori.getMAC1());
  tandaSimpan();
}
/*=====================================*/

/*===================================*/
void handleResetter()
{
  memori.setReset();
  tandaSimpan();
}

/*===================================*/

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnPerangkat()
{
  server.on("/setPlay", handleSetPlay);
  server.on("/setVolume", handleSetVolume);
  server.on("/setRelay", handleSetRelay);

  server.on("/getVolume", handleGetVolume);

  server.on("/setMAC1", handleSetMAC1);
  server.on("/getMAC1", handleGetMAC1);

  server.on("/setResetter", handleResetter);

  // server.on("/tx",     handleTx);
  // server.on("/rx",     handleRx);

  // server.on("/sound",     handleDPT);
  // server.on("/soundOn",   handleBufferOn);
  // server.on("/soundOff",  handleBufferOff);
  // server.on("/mp3On",     handleMp3On);
  // server.on("/mp3Off",    handleMp3Off);
}

/* ===================================================== */
