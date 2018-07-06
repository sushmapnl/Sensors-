#include<SPI.h>
#include<WiFi.h>
//#define LEDPin 22
//#define buttonPin 0

// Network information
char ssid[] = "MichiganTechOpen";//Wifi Name
const char password[] = "";


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600); //Initialize serial port
    while(!Serial) {
      ;
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect");
      Serial.println(ssid);
      int status = WiFi.begin(ssid, password);

      delay(10000);
    }
    
 Serial.print("Connected");
  Serial.println(WL_CONNECTED);
}

void loop() {
  // put your main code here, to run repeatedly:
   

    delay(10000);
    Serial.print("You r connected");
    Serial.println(WiFi.status());// Show the user a connection is successful
  }
  



  



