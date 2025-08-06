/*==============================================================
                     Pick-Up Data DS3231
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
#include <DMDESP.h>
#include <fonts/EMSansSP8x16.h>


void handleSetKoordinat()
{
  String koordinat = server.arg("dataKoordinat");
  memori.setKoordinatString(koordinat);
  tandaSimpan();
}

void handleGetKoordinat()
{
  char str[10];
  sprintf(str, " %f LS, %f BT, %d W ", memori.dataLintang(), memori.dataBujur(), memori.dataLokal());
  server.send(200, "text/plane", str);
}

/*==============================================================
          PROGRAMs SCANNING ALARM for Digital Prayer Time
                    By. SHATOMEDIA (Safix)
  ==============================================================*/
bool tandaBeep = true;
bool tandaIqomah = true;
int iqomahJam = 0;
int iqomahMenit = 0;
int sholat;

extern DMDESP Disp;

void scanningSholat()
{
  // Ambil_Waktu();
  // Hitung_Waktu_Sholat ();
  sholat = 0;
  if (waktu.detik() == 0)
  {
    if (waktu.jam() == jws.shubuhJam())
    {
      if (waktu.menit() == jws.shubuhMenit())
      {
        sholat = 1;
      }
    }
    else if (waktu.jam() == jws.dzuhurJam())
    {
      if (waktu.menit() == jws.dzuhurMenit())
      {
        sholat = 2;
      }
    }
    else if (waktu.jam() == jws.asharJam())
    {
      if (waktu.menit() == jws.asharMenit())
      {
        sholat = 3;
      }
    }
    else if (waktu.jam() == jws.maghribJam())
    {
      if (waktu.menit() == jws.maghribMenit())
      {
        sholat = 4;
      }
    }
    else if (waktu.jam() == jws.isyaJam())
    {
      if (waktu.menit() == jws.isyaMenit())
      {
        sholat = 5;
      }
    }
  }

  if (sholat != 0)
  {
    mp3_stop();
    // mp3Stop();
    delay(500);
    Serial.println("Masuk Waktu Sholat");
    
    byte s = memori.getSirine();
    if (s == HIGH)
    {
      // digitalWrite  (Relay, LOW);
      IO.relayOn();
      delay(1000);
      for (int i = 0; i <= 7; i++)
      {
        tandaBeep = false;

        mp3_play(2);
        // mp3File(2);

        unsigned long time_now = 0;

        time_now = millis();
        while(millis() < time_now + 500){
            server.handleClient(); // TV

            segment.Hapus_Jam();
            segment.Hapus_Jadwal();
            segment.Hapus_Kalender();
            segment.Scanning_Segment();
        }
      
        time_now = millis();
        while(millis() < time_now + 250){
            server.handleClient(); // TV

            segment.DisplayAlarm(sholat);
            segment.Scanning_Segment();
        }

        time_now = millis();
        while(millis() < time_now + 250){
            server.handleClient(); // TV

            segment.Hapus_Jadwal();
            segment.Scanning_Segment();
        }

        tandaBeep = true;
      
        time_now = millis();
        while(millis() < time_now + 500){
            server.handleClient(); // TV

            segment.DisplayAlarm(sholat);
            segment.Scanning_Segment();
        }
      }
    }

    segment.Hapus_Jam();
    segment.Hapus_Jadwal();
    segment.Hapus_Kalender();
    byte c = memori.getAdzan();
    if (c == HIGH)
    {
      // digitalWrite  (Relay, LOW);
      IO.relayOn();
      delay(1000);
      mp3_play(7);
      // mp3File(7);
      delay(100);
      if (sholat == 1)
      {
        mp3_play(6);
      }
    }
  }

  if (sholat != 0)
  {
    int i_qomah;
    switch (sholat)
    {
    case 1:
      i_qomah = memori.iqomahShubuh();
      break;
    case 2:
      i_qomah = memori.iqomahDzuhur();
      break;
    case 3:
      i_qomah = memori.iqomahAshar();
      break;
    case 4:
      i_qomah = memori.iqomahMaghrib();
      break;
    case 5:
      i_qomah = memori.iqomahIsya();
      break;
    }

    if (i_qomah != 0)
    {
      Serial.println("");
      Serial.println("I Q O M A H");

      tandaIqomah = false;
      i_qomah--;

      for (int a = i_qomah; a >= 0; a--)
      {
        Serial.println(a);
        segment.iqomahJam(a);

        for (int b = 59; b >= 0; b--)
        {

          // Tampilkan hitung mundur iqomah di display P10
          char buffer[16];
          sprintf(buffer, "IQOMAH %02d:%02d", a, b);
          Disp.clear();
          Disp.setFont(EMSansSP8x16); // Atau font yang Anda pakai
          Disp.drawText(0, 0, buffer);
          Disp.loop();

          unsigned long time_now = 0;

          time_now = millis();
          while(millis() < time_now + 300){
              server.handleClient(); // TV

              segment.iqomahMenit(b);
              segment.DisplayIqomah();
              segment.Scanning_Segment();
          }

          time_now = millis();
          while(millis() < time_now + 200){
              server.handleClient(); // TV

              segment.Hapus_Kalender();
              segment.Scanning_Segment();
          }

          time_now = millis();
          while(millis() < time_now + 300){
              server.handleClient(); // TV

              segment.DisplayIqomah();
              segment.Scanning_Segment();
          }

          time_now = millis();
          while(millis() < time_now + 200){
              server.handleClient(); // TV

              segment.Hapus_Kalender();
              segment.Scanning_Segment();
          }

          iqomahJam = a;
          iqomahMenit = b;
          Serial.print(a);
          Serial.print(" : ");
          Serial.println(b);
        }
      }

      tandaIqomah = true;

      byte s = memori.getSirine();
      if (s == HIGH)
      {
        for (int i = 0; i <= 2; i++)
        {
          mp3_play(2);
          // mp3File(2);


          unsigned long time_now = 0;
        
          time_now = millis();
          while(millis() < time_now + 500){
              server.handleClient(); // TV

            segment.DisplayAlarm(sholat);
            segment.Scanning_Segment();
          }

          time_now = millis();
          while(millis() < time_now + 250){
              server.handleClient(); // TV

            segment.Hapus_Jadwal();
            segment.Scanning_Segment();
          }
          
          time_now = millis();
          while(millis() < time_now + 250){
              server.handleClient(); // TV

            segment.DisplayAlarm(sholat);
            segment.Scanning_Segment();
          }
          time_now = millis();
          while(millis() < time_now + 500){
              server.handleClient(); // TV

            segment.Hapus_Jam();
            segment.Hapus_Jadwal();
            segment.Hapus_Kalender();
            segment.Scanning_Segment();
          }


        }
      }

      Serial.println("");
      Serial.println("Stand by");
      for (int i = 0; i <= 120; i++)
      {
        segment.DisplayAlarm(sholat);
        segment.Hapus_Jadwal();
        segment.Scanning_Segment();
        delay(500);
        segment.Hapus_Kalender();
        segment.Scanning_Segment();
        delay(500); // standby
        Serial.print(i);
      }
    }

    
    Serial.println("");
    Serial.println("Mode Normal");
  }
  

}

/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnKoordinat()
{
  server.on("/setKoordinat", handleSetKoordinat);
  server.on("/getKoordinat", handleGetKoordinat);
}

/*==============================================================*/