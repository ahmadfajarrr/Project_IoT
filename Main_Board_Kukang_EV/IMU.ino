//
// void IMU() {
//   mpu.update();
// if ((millis() - timer) > 10) { // print data every 10ms
//      Angel_X = mpu.getAngleX();
////     Serial.print("X : ");
////     Serial.print(mpu.getAngleX());
//     
//     Angel_Y = mpu.getAngleY();
////     Serial.print("\tY : ");
////     Serial.print(mpu.getAngleY());
//
//     Angel_Z = mpu.getAngleZ();
////     Serial.print("\tZ : ");
////     Serial.println(mpu.getAngleZ());
//     timer = millis();
//   }
// }



void IMU() {
   int16_t accelerometerX = mpu.getAccelerationX();
  int16_t accelerometerY = mpu.getAccelerationY();
  int16_t accelerometerZ = mpu.getAccelerationZ();
  int16_t gyroX = mpu.getRotationX();
  int16_t gyroY = mpu.getRotationY();
  int16_t gyroZ = mpu.getRotationZ();

  // Convert raw sensor data to angles in degrees
  float angleX = atan(accelerometerY / sqrt(pow(accelerometerX, 2) + pow(accelerometerZ, 2))) * RAD_TO_DEG;
  float angleY = atan(-1 * accelerometerX / sqrt(pow(accelerometerY, 2) + pow(accelerometerZ, 2))) * RAD_TO_DEG;
  float angleZ = gyroZ / GYROSCOPE_SENSITIVITY;

  // Send data via LoRa
  LoRa.beginPacket();
  LoRa.print("X:");
  LoRa.print(angleX);
  LoRa.print(" Y:");
  LoRa.print(angleY);
  LoRa.print(" Z:");
  LoRa.print(angleZ);
  LoRa.endPacket();

  // Print data for debugging
  Serial.print("X: ");
  Serial.print(angleX);
  Serial.print("\tY: ");
  Serial.print(angleY);
  Serial.print("\tZ: ");
  Serial.println(angleZ);

  delay(10);  // Delay between transmissions
}
}
