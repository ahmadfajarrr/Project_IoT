#include <OneWire.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>;
#include <HardwareSerial.h>;
#include <ESP32Servo.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 mpu;

const float ACCELEROMETER_SENSITIVITY = 16384.0;
const float GYROSCOPE_SENSITIVITY = 131.0;
const float RAD_TO_DEG = 57.29578;



#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_REALACCEL
#define OUTPUT_TEAPOT
//#define INTERRUPT_PIN 0  // use pin 2 on Arduino Uno & most boards
//#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
unsigned long timer = 0;
const int ONE_WIRE_BUS_PIN_1         = 25;
const int ONE_WIRE_BUS_PIN_2         = 26;
const int fanPin1           = 5;
const int fanPin2           = 18;
const int buttonForwardPin  = 14;
const int buttonBackwardPin = 27;
const int servoPin          = 26;
const int currentPin        = 2;
const int voltagePin        = 4;
int servoPosition = 0;

float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
float ref_voltage = 4.5;
int adc_value = 0;
float Angel_X, Angel_Y, Angel_Z;
float temperature_1 ;
float temperature_2 ;
float voltage;
float current;
String lattitude, longitude;

bool buttonForward = false;
bool buttonBackward = false;

OneWire oneWire_1(ONE_WIRE_BUS_PIN_1);
OneWire oneWire_2(ONE_WIRE_BUS_PIN_2);
TinyGPSPlus gps;
Servo myservo;
HardwareSerial SerialGPS(1);
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}
void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  pinMode (fanPin1, OUTPUT);
  pinMode (fanPin2, OUTPUT);
  myservo.setPeriodHertz(60);  // Set frekuensi PWM motor servo
  myservo.attach(servoPin, 500, 2500);
  pinMode(buttonForwardPin, INPUT_PULLUP);
  pinMode(buttonBackwardPin, INPUT_PULLUP);
  IMU();
  Serial.println("Done!\n");
}


void loop() {
   
  TEMPERATURE();
  
//  CURRENT();
//  VOLTAGE();
//  GPS();
//  SHIFTER();
  Loop_IMU();

//  
//  StaticJsonDocument<200> doc;
//  doc["Temperatur 1"] = temperature_1 ;
//  doc["Temperatur 2"] = temperature_2;
//  doc["Voltage"] = voltage;
//  doc["Current"] = current;
//  doc["ServoPosition"] = servoPosition;
//  doc["Angel_X"] = Angel_X;
//  doc["Angel_Y"] = Angel_Y;
//  doc["Angel_Z"] = Angel_Z;
//  doc["Latitude"] = lattitude;
//  doc["Longitude"] = longitude;
//  String jsonString;
//  serializeJson(doc, jsonString);
//
//  // Kirim data JSON melalui Serial
//  Serial.println(jsonString);

//  delay(2000);  // Tunggu selama 5 detik sebelum mengirim data berikutnya
}
