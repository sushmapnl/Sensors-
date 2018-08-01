/*
 * Reads an int and return the double
 */
 
#include<WiFi.h>

const char* ssid = "MichiganTechOpen" ; //NETGEAR83
const char* key = "";//luckyskates590

WiFiServer server(80);// server responds to clients on port 80 i.e. web browsers talk to web servers
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, key);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.begin();
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

void loop()
{  
  if (client.available()) {
    int value = client.parseInt();
    client.println(value * 2);
  }

  if (!client)
    try_connection();

  delay(10);
}
















