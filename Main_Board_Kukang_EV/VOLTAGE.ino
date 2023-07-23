
void VOLTAGE() {
  // Read the Analog Input
  adc_value = analogRead(voltagePin);

  // Determine voltage at ADC input
  adc_voltage = (adc_value * ref_voltage) / 4095.0;

  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2 / (R1 + R2)) ;
  voltage = ((in_voltage*1.27) ,2);

  // Print results to Serial Monitor to 2 decimal places
//  Serial.print("Input Voltage = ");
//  Serial.println((in_voltage*1.27), 2);
//  delay(500);
}
