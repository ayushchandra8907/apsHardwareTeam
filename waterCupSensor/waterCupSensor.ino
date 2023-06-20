int rawSensor = 0; // raw sensor (jus a number)


void convertToInches(double d){
  double zeroInc = 0;
  //double oneInc = 0;
  //double twoInc = 0;
  //double thrInc = 0;
  double forInc = 0;

  double slope = (forInc-zeroInc)/4.0;

  return slope*d;
  
}

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);   //sensor
  digitalWrite(7, LOW);
}

void loop() {
  digitalWrite(7, HIGH);
  delay(10);
  rawSensor = analogRead(SIGNAL_PIN);
  digitalWrite(7, LOW);

  Serial.print("Sensor value: ");
  Serial.print(rawSensor);

  Serial.print(" Inch value: ");
  Serial.println(convertToInches(rawSensor));

  delay(1000);
}
