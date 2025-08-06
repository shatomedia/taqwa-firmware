/*==============================================================
                     Pick-Up Data SKALA
                    By. SHATOMEDIA (Safix)
  ==============================================================*/


/*==============================================================*/
//          PAGES HTML = koordinat.h
/*==============================================================*/

void handleGetImsyak() {
  //char str[5];
  //sprintf(str, "%d:%d", jws.imsyakJam(), jws.imsyakMenit());
  server.send(200, "text/plane", jws.imsyakString());
}
void handleGetShubuh() {
  //char str[5];
  //sprintf(str, "%d:%d",  jws.shubuhJam(), jws.shubuhMenit());
  server.send(200, "text/plane", jws.shubuhString());
}
void handleGetSyuruq() {
  //char str[5];
  //sprintf(str, "%d:%d",  jws.syuruqJam(), jws.syuruqMenit());
  server.send(200, "text/plane", jws.syuruqString());
}
void handleGetDhuha() {
  //char str[5];
  //sprintf(str, "%d:%d",  jws.dhuhaJam(), jws.dhuhaMenit());
  server.send(200, "text/plane", jws.dhuhaString());
}
void handleGetDzuhur() {
  //char str[5];
  //sprintf(str, "%d:%d", jws.dzuhurJam(), jws.dzuhurMenit());
  server.send(200, "text/plane", jws.dzuhurString());
}
void handleGetAshar() {
  //char str[5];
  //sprintf(str, "%d:%d", jws.asharJam(), jws.asharMenit());
  server.send(200, "text/plane", jws.asharString());
}
void handleGetMaghrib() {
  //char str[5];
  //sprintf(str, "%d:%d", jws.maghribJam(), jws.maghribMenit());
  server.send(200, "text/plane", jws.maghribString());
}
void handleGetIsya() {
  //char str[5];
  //sprintf(str, "%d:%d", jws.isyaJam(), jws.isyaMenit());
  server.send(200, "text/plane", jws.isyaString());
}
/* ===================================================== */


void handleSetShubuh() {
  String skala = server.arg("skalaShubuh");
  memori.setShubuh(skala);
  Serial.print("Shubuh :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaShubuh());
  Serial.print("Sudut :");
  Serial.println(memori.getSudutShubuh());
  tandaSimpan();
}
void handleSetSyuruq() {
  String skala = server.arg("skalaSyuruq");
  memori.setSyuruq(skala);
  Serial.print("Syuruq :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaSyuruq());
  tandaSimpan();
}
void handleSetDhuha() {
  String skala = server.arg("skalaDhuha");
  memori.setDhuha(skala);
  Serial.print("Dhuha :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaDhuha());
  tandaSimpan();
}
void handleSetDzuhur() {
  String skala = server.arg("skalaDzuhur");
  memori.setDzuhur(skala);
  Serial.print("Dzuhur :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaDzuhur());
  tandaSimpan();
}
void handleSetAshar() {
  String skala = server.arg("skalaAshar");
  memori.setAshar(skala);
  Serial.print("Ashar :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaAshar());
  Serial.print("Sudut :");
  Serial.println(memori.getSudutAshar());
  tandaSimpan();
}
void handleSetMaghrib() {
  String skala = server.arg("skalaMaghrib");
  memori.setMaghrib(skala);
  Serial.print("Maghrib :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaMaghrib());
  tandaSimpan();
}
void handleSetIsya() {
  String skala = server.arg("skalaIsya");
  memori.setIsya(skala);
  Serial.print("Isya :");
  Serial.println(skala);
  Serial.print("Skala :");
  Serial.println(memori.getSkalaIsya());
  tandaSimpan();
}



/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnIkhtiyat(){
  server.on("/getImsyak",   handleGetImsyak);
  server.on("/getShubuh",   handleGetShubuh);
  server.on("/getSyuruq",   handleGetSyuruq);
  server.on("/getDhuha",    handleGetDhuha);
  server.on("/getDzuhur",   handleGetDzuhur);
  server.on("/getAshar",    handleGetAshar);
  server.on("/getMaghrib",  handleGetMaghrib);
  server.on("/getIsya",     handleGetIsya);

  server.on("/setShubuh",   handleSetShubuh);
  server.on("/setSyuruq",   handleSetSyuruq);
  server.on("/setDhuha",    handleSetDhuha);
  server.on("/setDzuhur",   handleSetDzuhur);
  server.on("/setAshar",    handleSetAshar);
  server.on("/setMaghrib",  handleSetMaghrib);
  server.on("/setIsya",     handleSetIsya);

}
/* ===================================================== */

/* ===================================================== */

