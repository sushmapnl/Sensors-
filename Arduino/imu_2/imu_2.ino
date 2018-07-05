#include "Wire.h"
const int MPU_ADDR = 0x68;
int acc_x, acc_y, acc_z;
int gyr_x, gyr_y, gyr_z;
int temp;

char temp_str[7];

char* convert_int_to_str(int i)  {
     sprintf(temp_str, "%6d",i);
     return temp_str;
       
}

//Serial Communication
void setup() { 
  Serial.begin(9600);
  
  pinMode(8, OUTPUT);
  
  digitalWrite(8, LOW);
  
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
}
void loop() {
  
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU_ADDR, 7*2, true); 

  acc_x = Wire.read()<<8 | Wire.read();
  acc_y = Wire.read()<<8 | Wire.read();
  acc_z = Wire.read()<<8 | Wire.read();

  temp = Wire.read()<<8 | Wire.read();

  gyr_x = Wire.read()<<8 | Wire.read();
  gyr_y = Wire.read()<<8 | Wire.read(); 
  gyr_z = Wire.read()<<8 | Wire.read(); 

  //print out data
  Serial.print("Acc_X = "); Serial.print(convert_int_to_str(acc_x));
  Serial.print("Acc_Y = "); Serial.print(convert_int_to_str(acc_y));
  Serial.print("Acc_Z = "); Serial.print(convert_int_to_str(acc_z));

  Serial.print(" |Temp = "); Serial.print(temp/340+36.53);

  Serial.print("Gyr_X = "); Serial.print(convert_int_to_str(gyr_x));
  Serial.print("Gyr_Y = "); Serial.print(convert_int_to_str(gyr_y));
  Serial.print("Gyr_Z = "); Serial.print(convert_int_to_str(gyr_z));

  Serial.println();

  if (acc_x > 5000 ) { 

    digitalWrite(8, HIGH); 

  }  else {

    digitalWrite(8, LOW);
  }
  delay(10);

}

