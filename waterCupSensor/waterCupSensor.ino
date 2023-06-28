int rawSensor = 0; // raw sensor (jus a number)
bool flooded = false;

double convertToInches(double d){
  double zeroInc = 0;
  //double oneInc = 0;
  //double twoInc = 0;
  //double thrInc = 0;
  double forInc = 122;

  double slope = 1.0/(forInc-zeroInc);

  return slope*d;
  
}

void floodedProtocol(){
  //digitalWrite(6, HIGH);
  tone(3, 440, 500);


  digitalWrite(8, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);   //sensor
  pinMode(8, OUTPUT); //red led
  pinMode(13, OUTPUT); //green led
  pinMode(6, OUTPUT); //buzzer

  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void loop() {
  digitalWrite(7, HIGH);
  delay(10);
  rawSensor = analogRead(A5);
  digitalWrite(7, LOW);

  Serial.print("Sensor value: ");
  Serial.println(rawSensor);

  if(rawSensor < 50) {
    flooded = false;
    digitalWrite(13, HIGH);
  } else {
    flooded = true;
    digitalWrite(13, LOW);
  }



  if(flooded){floodedProtocol();}

  delay(500);
  noTone(3);
  digitalWrite(8, LOW);
  delay(500);


}
