void SHIFTER() {
  buttonForward = digitalRead(buttonForwardPin);
  buttonBackward = digitalRead(buttonBackwardPin);

  if (buttonForwardPin == LOW) {
    servoPosition += 20;
//    Serial.println("Naik");
    if (servoPosition > 180) {
      servoPosition = 180;
    }
    myservo.write(servoPosition);
    delay(100);  // Membuat jeda untuk menghindari bouncing tombol
  }

  if (buttonBackwardPin == LOW) {
    servoPosition -= 20;
//    Serial.println("Turun");
    if (servoPosition < 0) {
      servoPosition = 0;
    }
    myservo.write(servoPosition);
    delay(100);  // Membuat jeda untuk menghindari bouncing tombol
  }
}

  
  
  
