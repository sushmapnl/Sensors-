#include<WiFi.h>


const char* ssid = "NETGEAR83" ; //MichiganTechOpen
const char* key = "luckyskates590";

WiFiServer server(80);// server responds to clients on port 80 i.e. web browsers talk to web servers
WiFiClient client;

const int ML1 = 17;
const int ML2 = 5;
const int MR1 = 18;
const int MR2 = 23;
const int E1 = 16;
const int E2 = 19;

void setup() {
  // put your setup code here, to run once:

  pinMode(ML1 , OUTPUT);
  pinMode(ML2 , OUTPUT);
  pinMode(MR1 , OUTPUT);
  pinMode(MR2 , OUTPUT);
  pinMode(E1 , OUTPUT);
  pinMode(E2 , OUTPUT);

  
  pinMode(22, OUTPUT); //LED flash pin
  digitalWrite(22, LOW);

  Serial.begin(9600);
  WiFi.begin(ssid, key);

  while(WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }

  server.begin(); 

  Serial.println("Waiting for Client connection");
//  To print IP address of client connected
  while(!client) { 
    client = server.available();
    Serial.println(WiFi.localIP());
    delay(1000);
  }

  Serial.println("Client Connected");
}

void loop() {
//   put your main code here, to run repeatedly:

  if(client.connected()) {
    client.println("Connected");
//    digitalWrite(22, HIGH);
//    delay(1000);
  } else { 
//    digitalWrite(22, !digitalRead(22));
//    delay(1000);
    Serial.println("Disconnected");
  }

//To read the string from client and print the same
  while(client.available()) { 
    String string = client.readStringUntil('r');
    Serial.println(string);  
//To blink led on & off
//    if(string == "low") {
//    digitalWrite(22, LOW);
//    delay(1000);
//  } else if(string == "high") {
//    digitalWrite(22, HIGH);
//    delay(1000);

/To Control in different directions
        digitalWrite(16, HIGH);
        digitalWrite(19, HIGH);

     if (string == "f") {      //forward

       
        digitalWrite(ML1, HIGH);
        digitalWrite(ML2, LOW);
        digitalWrite(MR1, LOW);
        digitalWrite(MR2, HIGH);
     } else if ( string == "b") { // Backward

         
        digitalWrite(ML1, LOW);
        digitalWrite(ML2, HIGH);
        digitalWrite(MR1, HIGH);
        digitalWrite(MR2, LOW);
     } else if (string == "l" ) { //Left

          
          digitalWrite(ML1,LOW );
        digitalWrite(ML2, LOW);
        digitalWrite(MR1, HIGH);
        digitalWrite(MR2, LOW);
     } else if (string == "p" ) { //Right

         
         digitalWrite(ML1, HIGH);
        digitalWrite(ML2, LOW);
        digitalWrite(MR1, LOW);
        digitalWrite(MR2, LOW);
         
     }


  }
}
















