#include<WiFi.h>

#define ML1  17
#define ML2  5
#define MR1  18
#define MR2  23
#define E1  16
#define E2  19

const char* ssid = "MichiganTechOpen";
const char* key = "";

WiFiServer server(80); 
WiFiClient client;

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

  pinMode(22, OUTPUT); //LED flash pin
  digitalWrite(22, LOW);

  ledcSetup(0, 500, 10);
  ledcAttachPin(E1, 0);
  ledcSetup(1, 500, 10);
  ledcAttachPin(E2, 1);


  Serial.begin(9600);
  WiFi.begin(ssid, key);

  while(WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.println("Waiting for Client connection");

  try_connection();
  Serial.println("Client Connected");
}
void try_connection() {
  // loop forever until client a client is connected
  while (!client) {
    client = server.available();
    Serial.println(WiFi.localIP());
    delay(1000);
  }
}
void loop() {
  // put your main code here, to run repeatedly:

  if(client.connected()) {
    client.println("Connected");
  } else if (!client) { 
//    Serial.println("Disconnected");
     try_connection();
  }

  if (client.available()) { 
   
//    int dir1 = Serial.parseInt();
//    int turn_per1 = Serial.parseInt();
       int dir1 = client.parseInt();
       int turn_per1 = client.parseInt();
//    Serial.read();
      client.read();
    speedir_control (dir1, turn_per1);

//    Serial.println(dir1);
//    Serial.println(turn_per1);
      client.println(dir1);
      client.println(turn_per1);
  }

  else if (!client) {
    try_connection();
  }

  delay(10);  
}
