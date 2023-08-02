//LIBRARIES===================================================================================
#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>                                        


//FIREBASE====================================================================================
#define FIREBASE_HOST "apsparkingboardtest-default-rtdb.firebaseio.com"              // the project name address from firebase id
#define FIREBASE_AUTH "xg6KvcccYzCzYCS2TPhRbisbzKzh14iOcumbSGin"       // the secret key generated from firebase
#define WIFI_SSID "APS1057"                                          
#define WIFI_PASSWORD "!APS1057!"                                  
 
String fireStatus = "";  // led status received from firebase

//connects board to firebase (do not touch!)
void connectBoard(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

//arrays===============================================================
//array for pins of LEDs
int pinsArr[2][4] = {
  {4, 5, 6, 7}, 
  {10, 11, 12, 13}
};

//array for status of LEDs
bool configArr[2][4] = {
  {true, true, true, true},
  {true, true, true, true}
};

//array for status of LEDs on flutter
String firebaseArr[2][4] = {
  {Firebase.getString("SPACE_1"), Firebase.getString("SPACE_2"), Firebase.getString("SPACE_3"), Firebase.getString("SPACE_4")},
  {Firebase.getString("SPACE_5"), Firebase.getString("SPACE_6"), Firebase.getString("SPACE_7"), Firebase.getString("SPACE_8")}
};


//BOARD INIT===================================================================================
//basic helper method for setting LED to on or off
void togPin(int pinNum, bool on){
  if(on){
    digitalWrite(pinNum, HIGH);
  } else {
    digitalWrite(pinNum, LOW);
  }
}

//sets all pins to either off or on irl----------------------------------
void setAllPins(bool on){
  int i = 1;
  
  for(int r = 0; r<2; r++){
    for(int c = 0; c<4; c++){
      //sets physical pin to off
      togPin(pinsArr[r][c], on);

      //sets led off in firebase
      String f = "SPACE_" + i;
      if(on){
        Firebase.setString(f, "ON")        
      } else {
        Firebase.setString(f, "OFF")                
      }
      i++:
    }
  }
}

//updates irl lot based off config--------------------------------------
//takes the infomration form config array and assings to LEDs
void updateLot(){
  for(int r = 0; r<2; r++){
    for(int c = 0; c<4; c++){
      togPin(pinsArr[r][c], configArr[r][c]);
    }
  }
}

//takes the information from firebase and assigns it to config array
void updateConfigFromFirebase(){
  int i = 1;
  for(int r = 0; r<2; r++){
    for(int c = 0; c<4; c++){
      String f = "SPACE_" + i;

      if(Firebase.getString(f) == "ON"){
        configArr[r][c] = true;
      } else {
        configArr[r][c] = false;
      }
      
      i++;
    }
  }
}



void setup() 
{
  Serial.begin(9600);
  delay(1000);    

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  Firebase.setString("LED_STATUS", "OFF");                       //send initial string of led status
}
 
void loop() 
{

//CODE COPIED FOR REFERENCES! delte at on risk
//  fireStatus = Firebase.getString("SPACE_1");                                      // get ld status input from firebase
//  if (fireStatus == "ON") 
//  {                                                          // compare the input of led status received from firebase
//    Serial.println("Led Turned ON");                                                        
//    digitalWrite(led, HIGH);                                                         // make external led ON
//  } 
//  else if (fireStatus == "OFF") 
//  {                                                  // compare the input of led status received from firebase
//    Serial.println("Led Turned OFF");
//    digitalWrite(led, LOW);                                                         // make external led OFF
//  }
//  else 
//  {
//    Serial.println("Command Error! Please send ON/OFF");
//  }


  //MAIN CODE===========================================================
  //gets values from firebase and sets to config array
  updateConfigFromFirebase();

  //takes the values from the config array and sends it to the pin LEDs.
  updateLot();
  
  delay(500);
}
