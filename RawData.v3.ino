void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print(analogRead(0));
  Serial.print("\t");
  Serial.print(analogRead(1));
  Serial.print("\t");
  Serial.print(analogRead(2));
  
  Serial.print("\t");
  Serial.print(analogRead(3));
  Serial.print("\t");
  Serial.print(analogRead(4));
  Serial.print("\t");
  Serial.print(analogRead(5));
  
  Serial.println("");
  delay(10);
}
