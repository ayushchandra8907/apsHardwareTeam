/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
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

//variables for each space represented on firebase
int space_1;
int space_2;
int space_3;
int space_4;
int space_5;
int space_6;
int space_7;
int space_8;

//variables for each pin on board
int space1pin = 13;
int space2pin = 12;
int space3pin = 14;
int space4pin = 27;
int space5pin = 26;
int space6pin = 35;
int space7pin = 33;
int space8pin = 32;


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
    Serial.println("ok");
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

//FETCHER METHOD FOR LOTS====================================================================================
void fetchLotStatus(){
  if (Firebase.ready() && signupOK) { //FETCHES ALL DATA
    
    //LOT 1====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space1")) { 
      if (fbdo.dataType() == "int") {
        space_1 = fbdo.intData();
        Serial.println(space_1);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 2====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space2")) { 
      if (fbdo.dataType() == "int") {
        space_2 = fbdo.intData();
        Serial.println(space_2);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 3====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space3")) { 
      if (fbdo.dataType() == "int") {
        space_3 = fbdo.intData();
        Serial.println(space_3);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 4====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space4")) { 
      if (fbdo.dataType() == "int") {
        space_4 = fbdo.intData();
        Serial.println(space_4);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 5====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space5")) { 
      if (fbdo.dataType() == "int") {
        space_5 = fbdo.intData();
        Serial.println(space_5);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 6====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space6")) { 
      if (fbdo.dataType() == "int") {
        space_6 = fbdo.intData();
        Serial.println(space_6);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 7====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space7")) { 
      if (fbdo.dataType() == "int") {
        space_7 = fbdo.intData();
        Serial.println(space_7);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    //LOT 8====================================================
    if (Firebase.RTDB.getInt(&fbdo, "/test/space8")) { 
      if (fbdo.dataType() == "int") {
        space_8 = fbdo.intData();
        Serial.println(space_8);
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

  }


  //end println for formatting
  Serial.println();
}

void updateLotStatus(){
  if(space_1 == 1){
    digitalWrite(space1pin, HIGH);
  } else {
    digitalWrite(space1pin, LOW);
  }
}


//SETUP======================================================================================================
void setup() {
  FIREBASE_INIT_PROCESS();

  pinMode(space1pin, OUTPUT);
  pinMode(space2pin, OUTPUT);
  pinMode(space3pin, OUTPUT);
  pinMode(space4pin, OUTPUT);
  pinMode(space5pin, OUTPUT);
  pinMode(space6pin, OUTPUT);
  pinMode(space7pin, OUTPUT);
  pinMode(space8pin, OUTPUT);

}

//MAIN LOOP==================================================================================================
void loop() {
  //fetches information from firebase to send to lots
  fetchLotStatus();

  //updates lots
  updateLotStatus();

  delay(3000); //delay for firebase update - change at will
}
