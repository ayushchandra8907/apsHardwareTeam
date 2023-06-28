void setup() {
  Serial.begin(9600);
}

void loop() {
  tone(3, 440, 500);

  delay(500);

  noTone(3);
}
