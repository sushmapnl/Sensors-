const int M1 = 3;
//const int M2 = 5;

void setup() {
  // put your setup code here, to run once:
   pinMode(M1, OUTPUT);
 //  pinMode(M2, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
     int x;
     for(x=0; x <= 100; x+=1)
     {
      digitalWrite(M1 , HIGH);
      delay(30); 
     }
     delay(1000);
     for(x =0; x<=100;x+=1)
     {
      digitalWrite(M1, LOW);
      delay(30);
     }
     delay(1000);
}
