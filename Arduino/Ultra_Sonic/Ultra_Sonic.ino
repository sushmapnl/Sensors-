
const int Trig = 2;
const int Echo = 4;
const int M1 = 3;

long duration;
float distance;



void setup() {
  // put your setup code here, to run once:
   pinMode(Trig, OUTPUT);
   pinMode(Echo, INPUT);
   pinMode(M1, OUTPUT);
   
   Serial.begin(9600);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);

 digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(Echo , HIGH);

  distance = (duration*340)/20000.0;
  int dutycycle = distance *10;
  dutycycle = constrain(dutycycle, 0, 100); 
  analogWrite(M1, (dutycycle*255)/100);
  

  Serial.print("Distance: " );
  Serial.println(duration);
  Serial.print("DutyCycle : ");
   Serial.println(dutycycle);
  
  
}
