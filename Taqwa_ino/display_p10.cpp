#include "Handle/_p10.h"

void TampilkanJamP10() {
  char bufJam[3], bufMenit[3];
  snprintf(bufJam, sizeof(bufJam), "%02d", Data_Jam);
  snprintf(bufMenit, sizeof(bufMenit), "%02d", Data_Menit);

  Disp.setFont(EMSansSP8x16);
  Disp.drawText(0, 0, bufJam);
  Disp.drawText(20, 0, (Data_Detik % 2 == 0) ? ":" : " ");
  Disp.drawText(26, 0, bufMenit);
}

void TampilkanLayoutUtama() {
  static int lastDetik = -1;
  static unsigned long lastUpdateJadwal = 0;
  static int jadwalIndex = 0;
  unsigned long sekarang = millis();

  // Ganti jadwal setiap 10 detik
  if (sekarang - lastUpdateJadwal >= 10000) {
    lastUpdateJadwal = sekarang;
    jadwalIndex = (jadwalIndex + 1) % 6; // 6 jadwal: SHUBUH, SYURUQ, DZUHUR, ASHAR, MAGHRIB, ISYA
  }

  if (Data_Detik != lastDetik) {
    Disp.clear();
    TampilkanJamP10();
    Disp.setFont(System6x7);

    char buf[6];
    switch (jadwalIndex) {
      case 0:
        Disp.drawText(50, 0, "SHUBUH");
        snprintf(buf, sizeof(buf), "%02d:%02d", jws.shubuhJam(), jws.shubuhMenit());
        Disp.drawText(54, 8, buf);
        break;
      case 1:
        Disp.drawText(50, 0, "SYURUQ");
        snprintf(buf, sizeof(buf), "%02d:%02d", jws.syuruqJam(), jws.syuruqMenit());
        Disp.drawText(54, 8, buf);
        break;
      case 2:
        Disp.drawText(50, 0, "DZUHUR");
        snprintf(buf, sizeof(buf), "%02d:%02d", jws.dzuhurJam(), jws.dzuhurMenit());
        Disp.drawText(55, 8, buf);
        break;
      case 3:
        Disp.drawText(54, 0, "ASHAR");
        snprintf(buf, sizeof(buf), "%02d:%02d", jws.asharJam(), jws.asharMenit());
        Disp.drawText(56, 8, buf);
        break;
      case 4:
        Disp.drawText(49, 0, "MAGHRIB");
        snprintf(buf, sizeof(buf), "%02d:%02d", jws.maghribJam(), jws.maghribMenit());
        Disp.drawText(59, 8, buf);
        break;
      case 5:
        Disp.drawText(57, 0, "ISYA");
        snprintf(buf, sizeof(buf), "%02d:%02d", jws.isyaJam(), jws.isyaMenit());
        Disp.drawText(54, 8, buf);
        break;
    }
    lastDetik = Data_Detik;
  }
}

void TampilkanTeksBesar() {
  static int scrollX = 0;
  static String lastTeks = "";
  static unsigned long lastScroll = 0;
  const unsigned long intervalScroll = 30; // 25-50ms biasanya cukup smooth
  unsigned long sekarang = millis();

  Disp.setFont(Mono5x7); // Set font sebelum hitung lebar!
  int textWidth = Disp.textWidth(teksBesar.c_str());

  // Reset scrollX hanya jika teksBesar berubah
  if (teksBesar != lastTeks) {
    scrollX = Disp.width();
    lastTeks = teksBesar;
  }

  if (sekarang - lastScroll >= intervalScroll) {
    lastScroll = sekarang;
    scrollX--;
    if (scrollX < -textWidth) {
      scrollX = Disp.width();
    }
  }

  Disp.clear();
  Disp.drawText(scrollX, 4, teksBesar.c_str());
}