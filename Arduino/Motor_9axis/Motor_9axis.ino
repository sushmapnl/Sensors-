#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include<WiFi.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

#define ML1  17
#define ML2  5
#define MR1  18
#define MR2  23
#define E1  16
#define E2  19

void speedir_control( int dir, int turn_per) { 

  //direction
  digitalWrite( ML1, HIGH); 
  digitalWrite ( ML2 ,  LOW );
  digitalWrite(MR1, LOW );
  digitalWrite(MR2,  HIGH );

  if (dir == 0) {

  ledcWrite( 0, ((turn_per)*1023)/100); 
  ledcWrite( 1, ((turn_per)*1023)/100);
} else if(dir == 1) { 
  ledcWrite( 0, ((100 -turn_per)*1023)/100); 
  ledcWrite( 1, ((turn_per)*1023)/100);
} else if ( dir == 2) {
  ledcWrite( 0, ((turn_per)*1023)/100); 
  ledcWrite( 1, ((100-turn_per)*1023)/100);
} 
}
void setup() {
  // put your setup code here, to run once:
  
  pinMode(ML1 , OUTPUT);
  pinMode(ML2 , OUTPUT);
  pinMode(MR1 , OUTPUT);
  pinMode(MR2 , OUTPUT);
  pinMode(E1 , OUTPUT);
  pinMode(E2 , OUTPUT);

  pinMode(27, OUTPUT);
  digitalWrite(27, LOW);
  
  pinMode(22, OUTPUT); //LED flash pin
  digitalWrite(22, LOW);

  ledcSetup(0, 500, 10);
  ledcAttachPin(E1, 0);
  ledcSetup(1, 500, 10);
  ledcAttachPin(E2, 1);

  
  Serial.begin(9600);
  Serial.println("Orientation Results of Motor"); Serial.println("");

  if(!bno.begin())
  {
    Serial.print("Oops, no BNO055 detected...Check wiring or I2C address");
    while(1);
  }
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

 if(Serial.available()) {

  int dir1 = Serial.parseInt();
    int turn_per1 = Serial.parseInt();
    Serial.read();
    speedir_control (dir1, turn_per1);

    Serial.println(dir1);
    Serial.println(turn_per1);

 sensors_event_t event;
 bno.getEvent(&event);

 Serial.print("X:");
 Serial.print(event.orientation.x, 4); 
 Serial.print("\tY: ");
 Serial.print(event.orientation.y, 4);
 Serial.print("\tZ: ");
 Serial.print(event.orientation.z, 4);
 
 displayCalStatus();
 Serial.println("");
 delay(BNO055_SAMPLERATE_DELAY_MS);
 }

 delay(10);
}

void displayCalStatus(void) { 
  uint8_t system, gyro, acc, mag;
  system = gyro = acc = mag = 0;
  bno.getCalibration(&system , &gyro, &acc, &mag);
  Serial.print("\t");
  if(!system)
  {
    Serial.print("!..");
  }
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print("G:");
  Serial.print(gyro, DEC);
  Serial.print("A:");
  Serial.print(acc, DEC);
  Serial.print("M:");
  Serial.print(mag, DEC);
}

