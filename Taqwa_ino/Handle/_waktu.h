

/*==============================================================*/
//          PAGES HTML = waktu.h
/*==============================================================*/
void handleGetJam() {
  server.send(200, "text/plane", waktu.waktuString());
}

void handleGetTanggal() {
  server.send(200, "text/plane", waktu.kalenderString());
}

void handleGetHijriyah() {
  server.send(200, "text/plane", waktu.hijriyahString());
}

void handleSetWaktu() {
  String setRTC = server.arg("dataWaktu");
  waktu.setWaktu(setRTC);
  Serial.print("RTC :");
  Serial.println(setRTC);
  Serial.print("Test :");
  waktu.begin();
  //tandaSimpan();
}


/*==============================================================
                     Pick-Up Data DS3231
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
void serverOnWaktu(){
  server.on("/setWaktu",    handleSetWaktu);
  server.on("/getJam",      handleGetJam);
  server.on("/getTanggal",  handleGetTanggal);
  server.on("/getHijriyah", handleGetHijriyah);
}
/* ===================================================== */



/* ===================================================== */
