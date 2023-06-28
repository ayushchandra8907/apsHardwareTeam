//VARIBABLES==========================================
int fireHZ = 880;
int gasHZ = 440;
int speakerHZ;

int flmVal;
int gasVal;

bool emergency = false;


//HELPER FUNCTIONS====================================
void emergencyProtocol(){
  if(emergency){
    digitalWrite(13, HIGH);
    tone(3, speakerHZ, 500);
  } else {
    turnOff();
  }
}

void turnOff(){
  digitalWrite(13, LOW);
  noTone(3);
}

void gatherData(){
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  gasVal = analogRead(A2);
  flmVal = analogRead(A0);

  delay(10);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

//SETUP===============================================

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT); // red led

  pinMode(6, OUTPUT); // gas sensor
  pinMode(7, OUTPUT); // flame sensor

}

void loop() {
  //turning on/off
  gatherData();

  Serial.print("Gas Sensor:");
  Serial.print(gasVal);
  Serial.print(" Flame Sensor: ");
  Serial.println(flmVal);

  if(digitalRead(1) == HIGH){
    emergency = true;
  } else{
    emergency = false;
  }

  //code for gas sensor
  if(gasVal > 10){
    emergency = true;
    speakerHZ = gasHZ;
  }
  


  //code for flame sensor
  if(flmVal > 500){
    emergency = true;
    speakerHZ = fireHZ;
  }



  if(flmVal <=500 && gasVal <= 10){
    emergency = false;
  }


  emergencyProtocol();
  delay(250);
  turnOff();
  delay(250);
}
