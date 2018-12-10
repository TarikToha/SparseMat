void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("ul = \t");
  Serial.print(analogRead(0));
  Serial.print("\t, ur = \t");
  Serial.print(analogRead(1));
  
  Serial.print("\t, ml = \t");
  Serial.print(analogRead(2));
  Serial.print("\t, mr = \t");
  Serial.print(analogRead(3));
  
  Serial.print("\t, ll = \t");
  Serial.print(analogRead(4));
  Serial.print("\t, lr = \t");
  Serial.print(analogRead(5));
  
  Serial.println("\t");
  delay(10);
}
