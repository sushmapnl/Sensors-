
#include<Wire.h>

#define CHIP_ID   0x00
#define ACC_ID    0x01
#define MAG_ID    0x02
#define GYRO_ID   0x03
#define ACC_DATA_X 0X08
#define MAG_DATA_X 0x0E
#define GYRO_DATA_X 0x14
#define OPR_MODE  0x03D
#define ACC_CONFIG  0x08
#define MAG_CONFIG  0x09
#define GYRO_CONFIG_0 0x0A
#define GYRO_CONFIG_1 0x0B

int16_t acc[3];
int16_t gyro[3];
int16_t mag[3];
int16_t tempG, tempM;

float ax,ay, az, gx, gy, gz, mx, my, mz;

enum OPRMODE { CONFIGMODE = 0x00 };

// Using the BNO055_MS5637 breakout board/Teensy 3.1 Add-On Shield, ADO is set to 1 by default 
#define ADO 1
#if ADO
#define BNO055_ADDRESS 0x29   //  Device address of BNO055 when ADO = 1

#else
#define BNO055_ADDRESS 0x28   //  Device address of BNO055 when ADO = 0

#endif  

#define SerialDebug true      // set to true to get Serial output for debugging

void setup() {
  // put your setup code here, to run once:
 Wire.begin(32, 33, 400000);
 delay(5000);
 Serial.begin(9600);
 
 Serial.println("BNO055 9-axis motion sensor...");
 byte c = readByte(CHIP_ID);
 Serial.println("CHIP_ID"); Serial.print(c, HEX); //Serial.println(" 0xA0");
 
 delay(1000);
 
 byte d = readByte(ACC_ID);
  Serial.println("ACC_ID");Serial.print(d, HEX); //Serial.println(" 0xFB");
 
 delay(1000);
 
 byte e = readByte(MAG_ID);
  Serial.println("MAG_ID"); Serial.print(e, HEX); 
  
  delay(1000);
  
  byte f = readByte(GYRO_ID);
   Serial.println("GYRO_ID");  Serial.print(f, HEX); 
   
   delay(1000);
   
   initBNO055();  {// Initialize BNO055 
   Serial.println("BNO055 initialized....");
   }
   else 
   {
    Serial.print("Could not connect to BNO055: 0x");
    Serial.println(c, HEX);
    while(1) ; // Loop forever if communication doesn't happen
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  readAccData(acc); 
  ax = (float)acc[0];
  ay = (float)acc[1];
  az = (float)acc[2];
  
  readGyroData(gyro);
  gx = (float)gyro[0]/16.;
  gy = (float)gyro[1]/16.;
  gz = (float)gyro[2]/16.;
  
  readMagData(mag); 
  mx = (float)mag[0]/1.6;
  my = (float)mag[1]/1.6;
  mz = (float)mag[2]/1.6;
  
if(SerialDebug) {
  Serialprint("ax ="); Serial.print((int)ax);
  Serialprint("ay ="); Serial.print((int)ay);
  Serialprint("az ="); Serial.print((int)az); Serial.println("mg"):
  
  Serialprint("gx ="); Serial.print(gx, 2);
  Serialprint("gy ="); Serial.print(gy, 2);
  Serialprint("gz ="); Serial.print((gz, 2); Serial.println("deg/s"):
  
  Serialprint("mx ="); Serial.print((int)mx);
  Serialprint("my ="); Serial.print((int)my);
  Serialprint("mz ="); Serial.print((int)mz); Serial.println("mG"):
    
}
}

void readAccData(int16_t * dest)
{
  uint8_t rawData[6];
  readBytes(BNO055_ADDRESS, ACC_DATA_X, 6, &rawData[0]); //Read six raw data registers into data array
  dest[0] = ((int16_t)rawData[1] << 8) | rawData[0];
  dest[1] = ((int16_t)rawData[3] << 8) | rawData[2];
  dest[2] = ((int16_t)rawData[5] << 8) | rawData[4];
}
void readGyroData(int16_t * dest)
{
  uint8_t rawData[6];
  readBytes(BNO055_ADDRESS, GYRO_DATA_X, 6, &rawData[0]); //Read six raw data registers into data array
  dest[0] = ((int16_t)rawData[1] << 8) | rawData[0];
  dest[1] = ((int16_t)rawData[3] << 8) | rawData[2];
  dest[2] = ((int16_t)rawData[5] << 8) | rawData[4];
}
void readMagData(int16_t * dest)
{
  uint8_t rawData[6];
  readBytes(BNO055_ADDRESS, MAG_DATA_X, 6, &rawData[0]); //Read six raw data registers into data array
  dest[0] = ((int16_t)rawData[1] << 8) | rawData[0];
  dest[1] = ((int16_t)rawData[3] << 8) | rawData[2];
  dest[2] = ((int16_t)rawData[5] << 8) | rawData[4];
}

void initBNO055() { 
  //select BNO055 config mode
  writeByte(BNO055_ADDRESS, OPR_MODE, CONFIGMODE);
  delay(25);
 //configure ACC
  writeByte( BNO055_ADDRESS, ACC_CONFIG, 0X08);
  //Configure GYR
  writeByte( BNO055_ADDRESS, GYRO_CONFIG_0 , 0x0A);
  writeByte( BNO055_ADDRESS, GYRO_CONFIG_1 , 0x0B);
 //Configure MAG
 writeByte( BNO055_ADDRESS, MAG_CONFIG, 0X09);
 
}
void writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {
  Wire.beginTransmission(address);
  Wire.write(subAddress);
  Wire.write(data);
  Wire.endTransmission();
}
void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t *dest1) { 
    Wire.beginTransmission(address); //Initialize Tx buffer
    Wire.write(subAddress);  
    Wire.endTransmission(false);
    uint8_t i =0;
 Wire.requestFrom(address, count); 
   while(Wire.available()) { 
    dest1[i++] = Wire.read(); }
} 
  
