#include<SPI.h>
#include<WiFi.h>
#define LEDPin 22
//#define buttonPin 0

// Network information
char ssid[] = "MichiganTechOpen";//Wifi Name
const char password[] = "";


void setup() {
  // put your setup code here, to run once:
    pinMode(LEDPin , OUTPUT);
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
    //Serial.print("You r connected");
    Serial.println(WiFi.status());// Show the user a connection is successful

    //Scan wifi networks available
    Serial.print("Scanning wifi networks");
    int numSsid = WiFi.scanNetworks();

    if (numSsid == -1) {
       Serial.println("Couldn't get a wifi connection");
       
    while (true);
  
  }
 Serial.println("number of available networks:");
 Serial.println(numSsid); 

 // print the network names found:

 for(int x = 0; x < numSsid; x++) {
    Serial.println(WiFi.SSID(x));
    Serial.print("\tSignal: ");
  
 }
ledControl();//To Control Ledpin of WiFi module
delay(10000);
 
  }

  void ledControl() {

     if(Serial.available() > 0)  
   { 
    int state = Serial.read();
    Serial.print("State :");
    Serial.println(state);

    if (state =='0')
       digitalWrite(LEDPin, LOW);
    else if(state == '1')
       digitalWrite(LEDPin, HIGH); 
  }
  }


  



