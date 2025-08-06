/*==============================================================
                     CLOUD COMPUTING
                    By. SHATOMEDIA (Safix)
  ==============================================================*/

/*
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//#define WIFI_SSID "SHATOMEDIA"
//#define WIFI_PASSWORD "inovation"

#define API_KEY "AIzaSyCR5ZQOaMpOwBp0vTvVH5be-v9Kf6VAdg0"
#define DATABASE_URL "https://esp-firebase-a156b-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
  */

/* ================================================
    Program akan memilih koneksifitas
    Apabila router jaringan tidak terhubung
    maka akan dialihkan ke mode AP
/* ================================================ */
void cloud_begin()
{
  /*
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  //config.api_key = "AIzaSyCR5ZQOaMpOwBp0vTvVH5be-v9Kf6VAdg0";
  //config.database_url = "https://esp-firebase-a156b-default-rtdb.asia-southeast1.firebasedatabase.app/";

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  */
}

/*=====================================*/
void firebase()
{
  /*
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
      sendDataPrevMillis = millis();
      if (Firebase.RTDB.setInt(&fbdo, "test/coba", count)) {
        Serial.println(F("PASSED"));
      } else {
        Serial.println(F("FAILED"));
      }
      count++;
      if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0, 100))) {
        Serial.println("PASSED");
      } else {
        Serial.println("FAILED");
      }
        Serial.println(count);
    }

        */
}
/*=====================================*/

/*=====================================*/
void handleSetDomain()
{
  String domain = server.arg("domain");
  memori.setDomain(domain);
  Serial.print("Save Domain : ");
  Serial.println(domain);
  Serial.print("Test:");
  Serial.println(memori.getDomain());
  tandaSimpan();
}

void handleGetDomain()
{
  server.send(200, "text/html", memori.getDomain());
}

void handleSetAPI()
{
  tandaSimpan();
}

void handleGetAPI()
{
  //
}
/*=====================================
    Layanan Interface Web server
           Halaman Beranda
  =====================================*/
void serverOnCloud()
{
  server.on("/setAPI", handleSetAPI);
  server.on("/getAPI", handleGetAPI);

  server.on("/setDomain", handleSetDomain);
  server.on("/getDomain", handleGetDomain);
}

/*=====================================*/
