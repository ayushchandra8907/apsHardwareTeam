//Arduiono libraries
#include <Arduino.h>

#include <LiquidCrystal.h>

#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

//NETWORK AND API INFO=====================================================================
#define WIFI_SSID "dream"
#define WIFI_PASSWORD "600312600"

// Insert Firebase project API Key
#define API_KEY "AIzaSyD-mrYNBScSexbSjY7U5lLQ6I3IElHlPX4"
#define DATABASE_URL "espdemo-519c5-default-rtdb.firebaseio.com" 

//VARIABLES AND OBJECTS===================================================================
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;

//program vars
String firebase_plate;

//LCD Config
int Contrast = 75;
LiquidCrystal lcd(33, 25, 26, 27, 14, 12);



//FIREBASE INIT PROCESS===================================================================
void FIREBASE_INIT_PROCESS(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Signup Completed");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

//GETS LICENSE PLATE FROM FIREBASE==============================================================================
void fetchLicensePlate(){
  if (Firebase.ready() && signupOK) { //FETCHES ALL DATA
    
    if (Firebase.RTDB.getString(&fbdo, "/test/licensePlate")) { 
      if (fbdo.dataType() == "string") {
        firebase_plate = fbdo.stringData();
        Serial.println(firebase_plate);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
}

//SETUP======================================================================================================
void setup() {
  FIREBASE_INIT_PROCESS();

  analogWrite(32,Contrast); // allows u to write onto lcd
  lcd.begin(16,2);

  
  lcd.setCursor(0, 0);
  lcd.print("Reserved For:");
}

//MAIN LOOP==================================================================================================
void loop() {

  fetchLicensePlate();

  //writes license plate onto lcd screen
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Reserved For:");
  
  lcd.setCursor(0, 1);
  lcd.print(firebase_plate);

  //delay for wifi module  
  delay(1500);
  
}
