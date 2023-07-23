//int RPM;
//void INTERUPT() {
//  RPM++;
//}
//
//// Kalman Filter parameters
//float X, P, K, R, Q;
//
//void setup() {
//  Serial.begin(115200);
//
//  // IR Infrared sensor
//  attachInterrupt(0, INTERUPT, RISING);
//
//  // Initialize Kalman Filter parameters
//  X = 0;  // Initial state estimate
//  P = 1;  // Initial error covariance
//  R = 0.1;  // Measurement noise covariance
//  Q = 0.01;  // Process noise covariance
//}
//
//void loop() {
//  noInterrupts();
//  int wings = 3;  // Number of wings of rotating object, for disc object use 1 with white tape on one side
//  int RPMnew = RPM / wings;  // Here we used a fan which has 3 wings
//
//  // Kalman Filter prediction step
//  float X_pred = X;
//  float P_pred = P + Q;
//
//  // Kalman Filter update step
//  K = P_pred / (P_pred + R);
//  X = X_pred + K * (RPMnew - X_pred);
//  P = (1 - K) * P_pred;
//
//  Serial.print(X);
//  Serial.print(" Rot/sec :");  // Revolutions per second
//  Serial.print((X * 60));
//  Serial.println(" Rot/min. ");  // Revolutions per minute
//
//  RPM = 0;
//  interrupts();
//  delay(1000);  // 1 second.
//}
