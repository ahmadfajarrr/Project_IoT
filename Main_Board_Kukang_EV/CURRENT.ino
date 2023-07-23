void CURRENT() {
  // put your main code here, to run repeatedly:
  int adc = analogRead(currentPin);
  float volt = adc * 4.5 / 4095.5;
  current = ((volt - 2.5) / 0.066)-6.8;
//  if (current < 0.16) {
//    current = 0;
//  }
//  Serial.print("Current : ");
//  Serial.println(current);
//  delay(300);
}
