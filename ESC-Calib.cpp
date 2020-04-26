byte mot =B11110000;
byte etein = B00000000;
 
int data;
int Minpuls = 1000;
int Maxpuls = 2000;
int PR = 0;
int PRO = 0;
int PROO = 0;
long prevmic;
float puls;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  puls = Minpuls;
 DDRD  |=  mot;
}

void loop() {
   
    if (Serial.available()) {
        data = Serial.read();
         }

    
         if (data == 48){
             Serial.println("Sending minimum throttle");
                       PORTD |= mot;
                       delayMicroseconds(Minpuls);
                       PORTD &=  B00000000;
                       PRO = 0;
                       PR = 1;
                        PROO = 0;
 
          }else if(PR == 1){
              
                        PORTD |= mot;
                       delayMicroseconds(Minpuls);
                       PORTD &=  B00000000;
              
         }


           if (data == 49){
             Serial.println("Sending  maximum throttle");
                       PORTD |= mot;
                       delayMicroseconds(Maxpuls);
                       PORTD &= B00000000;
                       PR = 0;
                       PRO = 1;
                       PROO = 0;
 
          }else if(PRO == 1){
                       PORTD |= mot;
                       delayMicroseconds(Maxpuls);
                       PORTD &= B00000000;
              
         }


           if (data == 50){
             Serial.println("test");
                       PORTD |= mot;
                       delayMicroseconds(puls);
                       PORTD &= B00000000;
                       PROO = 1;
                       PR = 0;
                       PRO = 0;
 
          }else if(PROO == 1){
            if (puls <= Maxpuls){
                       puls += 0.2;
                       PORTD |= mot;
                       delayMicroseconds(puls);
                       PORTD &= B00000000;
            }else{
              PR = 1;
              PROO = 0;
              puls = Minpuls; 
              }
              
         }

         while (micros()-prevmic < 8000);
         prevmic = micros();

}
