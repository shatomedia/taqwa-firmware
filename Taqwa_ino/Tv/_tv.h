/*==============================================================
                     Pick-Up Data DS3231
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
void handleTv(){

    switch (memori.getTheme()){
      case 0:
        server.send(200, "text/html", tv_page);
        break;
      case 1:
        server.send(200, "text/html", tv1_page);
        break;
      case 2:
        server.send(200, "text/html", tv2_page);
        break;
      default:
        server.send(200, "text/html", tv_page);
        break;
    }
}

/*==============================================================*/
//          PAGES HTML = waktu.h
/*==============================================================*/
void handleTvJam() {
  server.send(200, "text/plane", waktu.waktuString());
}

void handleTvKalender() {
  server.send(200, "text/plane", waktu.kalenderString());
}

void handleTvHijriyah() {
  server.send(200, "text/plane", waktu.hijriyahString());
}

void handleTvHari() {
  server.send(200, "text/plane", waktu.hariString());
}

void handleTvTanggal() {
  server.send(200, "text/plane", waktu.tanggalString());
}

void handleTvIqomah() {
  if (tandaIqomah == false){
    String data ;
    data += String(iqomahJam);
    data += ":";
    data += String(iqomahMenit);
    server.send(200, "text/plane", data);
  }else if (tandaIqomah == true){
    server.send(200, "text/plane", "");
  }
}


void handleTvBeep() {
  if (tandaBeep == false){
    server.send(200, "text/plane", "1");

  }else if (tandaBeep == true){
    server.send(200, "text/plane", "0");
  }
}



/*==============================================================*/
//          PAGES HTML = koordinat.h
/*==============================================================*/

void handleTvImsyak() {
  server.send(200, "text/plane", jws.imsyakString());
}
void handleTvShubuh() {
  server.send(200, "text/plane", jws.shubuhString());
}
void handleTvSyuruq() {
  server.send(200, "text/plane", jws.syuruqString());
}
void handleTvDhuha() {
  server.send(200, "text/plane", jws.dhuhaString());
}
void handleTvDzuhur() {
  server.send(200, "text/plane", jws.dzuhurString());
}
void handleTvAshar() {
  server.send(200, "text/plane", jws.asharString());
}
void handleTvMaghrib() {
  server.send(200, "text/plane", jws.maghribString());
}
void handleTvIsya() {
  server.send(200, "text/plane", jws.isyaString());
}
/* ===================================================== */



/* ===================================================== */
void serverOnTv(){
  server.on("/tv",         handleTv);
  
  server.on("/tvJam",      handleTvJam);
  server.on("/tvKalender", handleTvKalender);
  server.on("/tvHijriyah", handleTvHijriyah);

  server.on("/tvHari",     handleTvHari);
  server.on("/tvTanggal",  handleTvTanggal);


  server.on("/tvIqomah",   handleTvIqomah);
  server.on("/tvBeep",     handleTvBeep);

  server.on("/tvImsyak",   handleTvImsyak);
  server.on("/tvShubuh",   handleTvShubuh);
  server.on("/tvSyuruq",   handleTvSyuruq);
  server.on("/tvDhuha",    handleTvDhuha);
  server.on("/tvDzuhur",   handleTvDzuhur);
  server.on("/tvAshar",    handleTvAshar);
  server.on("/tvMaghrib",  handleTvMaghrib);
  server.on("/tvIsya",     handleTvIsya);

}
/* ===================================================== */



