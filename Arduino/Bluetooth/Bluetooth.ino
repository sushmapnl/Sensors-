
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//baud rate is important for serial transmission via bluetooth
  pinMode(13, OUTPUT); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
   if(Serial.available() > 0)  
   { 
    int state = Serial.read();
    Serial.print("State :");
    Serial.println(state);

    if (state =='0')
       digitalWrite(13, LOW);
    else if(state == '1')
       digitalWrite(13, HIGH); 
       
   }
}
