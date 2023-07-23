float getTemperature(OneWire* oneWire) {
  byte data[9];
  float temperature = 0;

  if (!oneWire->reset()) {
//    Serial.println("No sensor found!");
    return temperature;
  }

  oneWire->write(0xCC);  // Skip ROM command
  oneWire->write(0x44);  // Start temperature conversion

  delay(750);  // Wait for temperature conversion to complete

  if (!oneWire->reset()) {
//    Serial.println("No sensor found!");
    return temperature;
  }

  oneWire->write(0xCC);  // Skip ROM command
  oneWire->write(0xBE);  // Read scratchpad

  for (byte i = 0; i < 9; i++) {
    data[i] = oneWire->read();
  }

  int16_t rawTemperature = (data[1] << 8) | data[0];
  temperature = static_cast<float>(rawTemperature) * 0.0625;

  return temperature;
}

void TEMPERATURE() {
  temperature_1 = getTemperature(&oneWire_1);
  temperature_2 = getTemperature(&oneWire_2);

//  Serial.print("Temperature 1: ");
//  Serial.print(temperature_1);
//  Serial.println(" °C");
  if(temperature_1 >= 40){
    digitalWrite(fanPin1,HIGH);
  }
  else {
    digitalWrite(fanPin1,LOW);
  }

//  Serial.print("Temperature 2: ");
//  Serial.print(temperature_2);
//  Serial.println(" °C");
  if(temperature_2 >= 40){
  digitalWrite(fanPin2,HIGH);
  }
  else {
  digitalWrite(fanPin2,LOW);
  }
//
//  delay(2000);
}
