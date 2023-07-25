#include <Servo.h>
Servo servo; 
    
#define trigPin1 3
#define echoPin1 2
#define trigPin2 5
#define echoPin2 4
#define servoPin 13
#define Buzzer 7

long duration1, dist1, average1; 
long duration2, dist2, average2;   
long aver[3];  
long averr[3];

void setup() {       
  Serial.begin(9600);
  servo.attach(servoPin);  
  pinMode(trigPin1, OUTPUT);  
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT);  
  pinMode(echoPin2, INPUT); 
  pinMode(Buzzer, OUTPUT);
  servo.write(0);         
  delay(100);
  servo.detach(); 
} 

void measure1() {  
  digitalWrite(10,HIGH);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin1, LOW);
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  dist1 = (duration1/2) / 29.1;   
}
void measure2() {  
   digitalWrite(10,HIGH);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin2, LOW);
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  dist2 = (duration2/2) / 29.1;    
}
void loop() { 
  for (int i=0;i<=2;i++) {   
    measure1();               
   aver[i]=dist1;            
    delay(10);              
  }
 for (int i=0;i<=2;i++) {   
    measure2();               
   averr[i]=dist2;            
    delay(10);             
  }
  dist1=(aver[0]+aver[1]+aver[2])/3;    
 dist2=(averr[0]+averr[1]+averr[2])/3;    

if ( dist1<10) {

 servo.attach(servoPin);
 delay(2);
 servo.write(150);  
 Serial.println("Tempat Sampah Terbuka");
 delay(3000);       
 servo.write(40);    
 Serial.println("Tempat Sampah Tertutup");
 delay(500);
 servo.detach(); 

}
 else if (dist2 < 5){
  Serial.println("Tempat Sampah Penuh");
  digitalWrite(Buzzer, HIGH);
  delay(100);
  digitalWrite(Buzzer, LOW);
  delay(100);
  digitalWrite(Buzzer, HIGH);
  delay(100);
  digitalWrite(Buzzer, LOW);
  delay(200);

}
  Serial.print("Sensor Luar: ");
  Serial.print(dist1);
  Serial.print(", Sensor Dalam: ");
  Serial.println(dist2);
}
