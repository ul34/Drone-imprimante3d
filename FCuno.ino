
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 mpu(0x68);
MPU6050 mpu1(0x69);

#define MPU_ADDRESS 0x68 //MPU-1
#define MPU_ADDRESS1 0x69 //MPU-2
#define FREQ        250 
#define SSF_GYRO    65.5 // ± 250 °/s = 131, ± 500 °/s = 65.5, ± 1000 °/s = 32.8, ± 2000 °/s = 16.4

boolean initialized;
long Eroll, Epitch, Eyaw,  acc_total_vector, premicros, i, Eroll1, Epitch1, Eyaw1,  acc_total_vector1;
int Rollgyro, Pitchgyro, Yawgyro, Rollacc, Pitchacc, Yawacc, temperature,Rollgyro1, Pitchgyro1, Yawgyro1, Rollacc1, Pitchacc1, Yawacc1, temperature1;
float angleRO, anglePO,RollaccA , PitchaccA,angleRO1, anglePO1,RollaccA1 , PitchaccA1;

volatile unsigned long timer[4];
volatile unsigned long current_time;
volatile byte previous_state[4];
volatile unsigned int pulse_duration[4] = {1500, 1500, 1500, 1000};



float KYP = 6; // Coefficient YAW  
float KYI = 0.22;
float KYD = 0;

float KRP = 1.3; // Coefficient Roll
float KRI = 0.04;
float KRD = 18;

float KPP = 1.3; // Coefficient Pitch
float KPI =0.04; 
float KPD = 18;

float anglemaxP, anglemaxR, ConsG,  ConsP,  ConsR,  ConsY, EpropP,  EpropR,  EpropY,  EintP,  EintR,  EintY, EdevP, EdevR, EdevY, lastEP, lastER, lastEY, EPIDP, EPIDR, EPIDY,batterieV,angleP, angleR,ASP, ASR, ASY;
int mot1, mot2, mot3, mot4 ;
unsigned long prevmicros, prelmicros;
int decollage = 0;
int chanel1; //gaz
int chanel2; //pitch
int chanel3; //roll
int chanel4;  //Yaw
int gros;



void setup(){
 Serial.begin(57600);
  PCICR  |= (1 << PCIE0); // Declaration des interruptions Registre PCICR = "Pin change interrupt register" 00000001
  PCMSK0 |= (1 << PCINT0); // Registre PCMSK0 = "Pin change mask register" 00000001 = Pin digital 8 activée en interrupt en mode "Change"
  PCMSK0 |= (1 << PCINT1); //  Registre PCMSK0 = "Pin change mask register" 00000011 = Pin digital 8 et 9 activée en interrupt en mode "Change"
  PCMSK0 |= (1 << PCINT2); // Registre PCMSK0 = "Pin change mask register" 00000111 = Pin digital 8,9 et 10 activée en interrupt en mode "Change"
  PCMSK0 |= (1 << PCINT3); //  Registre PCMSK0 = "Pin change mask register" 00001111 = Pin digital 8,9,10 et 11 activée en interrupt en mode "Change"

 batterieV= (analogRead(0) + 65) * 1.2317; // Mesure de la tension de la batterie, 65 est additioner pour compenser la chute de tension crée par la diode (958+65)*1.2317 = 1260
 DDRD  |= B11110000; // declaration de la pin digital 4,5,6,7
 Wire.begin(); //lancer la  bibliothéque "Wire"
 TWBR = 24;       
 mpu.initialize(); // lancer la communication avec MPU-1
 mpu.setXAccelOffset(-3771); // rentrer les valeurs de calibration obtenue avec le programme MPU6050.cpp pour chaque gyroscope MPU-1 et MPU-2.
 mpu.setYAccelOffset(-1100);
 mpu.setZAccelOffset(1106);
 mpu.setXGyroOffset(-10);
 mpu.setYGyroOffset(70);
 mpu.setZGyroOffset(-8);

  mpu1.initialize(); // lancer la communication avec MPU-2
 mpu1.setXAccelOffset(497);
 mpu1.setYAccelOffset(1703);
 mpu1.setZAccelOffset(1148);
 mpu1.setXGyroOffset(-629);
 mpu1.setYGyroOffset(206);
 mpu1.setZGyroOffset(-8);

 communication(); // appel de la fonction " communication()"
 Emoyen(); // appel de la fonction " Emoyen()"


}

void loop(){
  activation();
   lectureMPU ();
  ANgyro();
  ANacc();
  calculangle ();
  consigne();
  PID();
  Signeauxcorrec();
  transmission();

}


void consigne(){  // la fonction consigne prend les signaux recu par les interruptions est les transformes en consigne pour le regulateur P.I.D

 ConsG = 0;   
 ConsP = 0;
 ConsR = 0;
 ConsY = 0;

 chanel1 =  pulse_duration[2]; //gaz
 chanel2 =  pulse_duration[1]; //Pitch
 chanel3 =  pulse_duration[3]; //Roll
 chanel4 =  pulse_duration[0]; //Yw

 if (chanel1 < 1000) chanel1 = 1000;
 if (chanel1 > 1800) chanel1 = 1800;
 if (chanel2 < 1000) chanel2 = 1000;
 if (chanel2 > 2000) chanel2 = 2000;
 if (chanel3 < 1000) chanel3 = 1000;
 if (chanel3 > 2000) chanel3 = 2000;
 if (chanel4 < 1000) chanel4 = 1000;
 if (chanel4 > 2000) chanel4 = 2000;
 //gaz
   if (chanel1 >1008){
   ConsG = chanel1;
    }


 //Pitch
   if (chanel2 >1508){
    ConsP = (chanel2-1508);
    }else if (chanel2 < 1492){
    ConsP = (chanel2-1492);
    }

     //Roll
   if (chanel3 >1508){
    ConsR = (chanel3-1508);
    }else if (chanel3 < 1492){
    ConsR = (chanel3-1492);
    }

      //Yaw
   if (chanel4 >1508){
    ConsY = (chanel4-1508);
    }else if (chanel4 < 1492){
    ConsY = (chanel4-1492);
    }

     anglemaxP = 15 * angleP; //32.8° angle maximum de rotation 15 = 492/32.8
     anglemaxR = 15 * angleR;

     ConsP -= anglemaxP ;
     ConsP /= 3;
     ConsR -=  anglemaxR;
     ConsR /= 3;
     ConsY /= 3; // limiter la vitesse de rotation maximale 492/3 = 164°/S


}



void PID(){ //La fonction PID prend la consigne envoyé est calcule l'erreur pour chaque axe

 //erreur proportionnelle
EpropP = ASP - ConsP;
EpropR = ASR - ConsR;
EpropY = ASY - ConsY;


//erreur intégré
EintP +=  EpropP;
EintR +=  EpropR;
EintY +=  EpropY;

if ( EintP > 400 ) EintP = 400; // limitation de l'erreur intégrale pour eviter l'effet "Windup"
if ( EintP < -400 )EintP = -400;
 if ( EintR > 400 ) EintR = 400;
if ( EintR < -400 )EintR = -400;
 if ( EintY > 400 ) EintY = 400;
if ( EintY < -400 )EintY = -400;

//erreur derivée
EdevP =  EpropP-lastEP;
EdevR =  EpropR-lastER;
EdevY =  EpropY-lastEY;

 lastEP =  EpropP;
lastER =  EpropR;
lastEY =  EpropY;


// erreur pid sortie pour chaque axe
EPIDR = KRP * EpropR + KRI * EintR + KRD * EdevR;
EPIDP = KPP * EpropP + KPI * EintP + KPD * EdevP;
EPIDY = KYP * EpropY + KYI * EintY + KYD * EdevY;



if ( EPIDP > 400 ) EPIDP = 400; // on limite aussi l'erreur totale pour chaque axe
if ( EPIDP < -400 )EPIDP = -400;
if (EPIDR > 400 ) EPIDR = 400;
if (EPIDR < -400 )EPIDR = -400;
if ( EPIDY > 400 ) EPIDY = 400;
if ( EPIDY < -400 )EPIDY = -400;

}


void resetvariable(){ // mise a zéro de toute les valeurs au démarage du drone
 lastEP = 0;
 lastER = 0;
 lastEY = 0;
  EintP = 0;
  EintR = 0;
  EintY = 0;
  EpropP = 0;
  EpropR = 0;
  EpropY = 0;
}

void activation(){ //  Démarer et eteindre le Drone
 if(decollage == 0 && chanel1 <= 1008 && chanel4 > 1980 && chanel3 > 1980){
   decollage = 1;
   resetvariable();
 }

  if(decollage == 1 && chanel1 <= 1008 && chanel2 > 1980 && chanel4 < 1008){
   decollage = 0;
 }



}



void Signeauxcorrec(){ // cette fonction recoit les valeur du PID est calcule la puissance a envoyer a chaque moteur elle calcule aussi le voltage pour compenser la perte de puissance
if ( decollage == 1){

 mot1 = ConsG-EPIDR-EPIDP-EPIDY;
 mot2 = ConsG+EPIDR-EPIDP+EPIDY;
 mot3 = ConsG-EPIDR+EPIDP+EPIDY;
 mot4 = ConsG+EPIDR+EPIDP-EPIDY;


batterieV = batterieV * 0.92 + (analogRead(0) + 65) * 0.09853;

 if ( batterieV < 1240 &&  batterieV > 800){
  mot1 += mot1 * ((1240 - batterieV)/(float)3500);
  mot2 += mot2 * ((1240 - batterieV)/(float)3500);
  mot3 += mot3 * ((1240 - batterieV)/(float)3500);
   mot4 += mot4 * ((1240 - batterieV)/(float)3500);
   }


 if (mot1 < 1100) mot1 = 1050;
 if (mot1 > 2000) mot1 = 2000;
 if (mot2 < 1100) mot2 = 1050;
 if (mot2 > 2000) mot2 = 2000;
 if (mot3 < 1100) mot3 = 1050;
 if (mot3 > 2000) mot3 = 2000;
 if (mot4 < 1100) mot4 = 1050;
 if (mot4 > 2000) mot4 = 2000;

} else{
mot1 = 1000;
mot2 = 1000;
mot3 = 1000;
mot4 = 1000;


}

Serial.print("\n");
 Serial.print(mot1);
 Serial.print("\t");
 Serial.print(mot2);
 Serial.print("\n");
 Serial.print(mot3);
Serial.print("\t");
 Serial.print(mot4);
 Serial.print("\n");


}

void transmission(){ // transmission s'occupe d'envoyer les signaux aux ESC de chaque moteur toute les 4ms=250HZ



 while (micros()-prevmicros < 4000);

 prevmicros = micros();
 PORTD |= B11110000;


while( PORTD >= 16){
 prelmicros = micros();
 if ( (mot1 + prevmicros) <= prelmicros) PORTD &= B11101111;
 if ( (mot2 + prevmicros) <= prelmicros) PORTD &= B11011111;
 if ( (mot3 + prevmicros) <= prelmicros) PORTD &= B10111111;
 if ( (mot4 + prevmicros) <= prelmicros) PORTD &= B01111111;

 }

}



 void communication(){ // Configuration de MPU-1 et MPU-2

 Wire.beginTransmission(MPU_ADDRESS);
 Wire.write(0x6B);
 Wire.write(0x00);
 Wire.endTransmission();


 Wire.beginTransmission(MPU_ADDRESS);
 Wire.write(0x1B);
 Wire.write(0x08);
 Wire.endTransmission();


 Wire.beginTransmission(MPU_ADDRESS);
 Wire.write(0x1C);
 Wire.write(0x10);
 Wire.endTransmission();

 Wire.beginTransmission(MPU_ADDRESS);
 Wire.write(0x1A);
 Wire.write(0x03);
 Wire.endTransmission();


  Wire.beginTransmission(MPU_ADDRESS1);
 Wire.write(0x6B);
 Wire.write(0x00);
 Wire.endTransmission();


 Wire.beginTransmission(MPU_ADDRESS1);
 Wire.write(0x1B);
 Wire.write(0x08);
 Wire.endTransmission();


 Wire.beginTransmission(MPU_ADDRESS1);
 Wire.write(0x1C);
 Wire.write(0x10);
 Wire.endTransmission();

 Wire.beginTransmission(MPU_ADDRESS1);
 Wire.write(0x1A);
 Wire.write(0x03);
 Wire.endTransmission();

 }



 void Emoyen(){// Calcul une moyenne des variations naturelle des gyroscopes "Drift"
   int max_samples = 2000;
for (int i = 0; i < max_samples; i++) {
   lectureMPU();
    Eroll1 += Rollgyro1;
   Epitch1 += Pitchgyro1;
   Eyaw1 += Yawgyro1;

   Eroll += Rollgyro;
   Epitch += Pitchgyro;
   Eyaw += Yawgyro;
   PORTD |= B11110000;
   delayMicroseconds(1000);
   PORTD &= B00001111;

   delay(3);
 }
 Eroll /= max_samples;
 Epitch /= max_samples;
 Eyaw /= max_samples;

 Eroll1 /= max_samples;
 Epitch1 /= max_samples;
 Eyaw1 /= max_samples;


 }


 void lectureMPU (){ // Lecture des valeurs de l'accelérométre et du gyroscope MPU-1 et MPU-2

   Wire.beginTransmission(MPU_ADDRESS);  
 Wire.write(0x3B);
 Wire.endTransmission();
 Wire.requestFrom(MPU_ADDRESS, 14);


 while (Wire.available() < 14);

 Rollacc  = Wire.read() << 8 | Wire.read();
 Pitchacc  = Wire.read() << 8 | Wire.read();
 Yawacc  = Wire.read() << 8 | Wire.read();
 temperature = Wire.read() << 8 | Wire.read();
 Rollgyro = Wire.read() << 8 | Wire.read();
 Pitchgyro = Wire.read() << 8 | Wire.read();
 Yawgyro = Wire.read() << 8 | Wire.read();

  Wire.beginTransmission(MPU_ADDRESS1);
 Wire.write(0x3B);
 Wire.endTransmission();
 Wire.requestFrom(MPU_ADDRESS1, 14);


 while (Wire.available() < 14);

 Rollacc1  = Wire.read() << 8 | Wire.read();
 Pitchacc1  = Wire.read() << 8 | Wire.read();
 Yawacc1  = Wire.read() << 8 | Wire.read();
 temperature1 = Wire.read() << 8 | Wire.read();
 Rollgyro1 = Wire.read() << 8 | Wire.read();
 Pitchgyro1 = Wire.read() << 8 | Wire.read();
 Yawgyro1 = Wire.read() << 8 | Wire.read();

 }


 void ANgyro() { // Cette fonction recoit le "Drift" et les valeurs brutes des Gyroscopes et fait un clacul de l'angle du Roll et Pitch

 Rollgyro -= Eroll;
 Pitchgyro -= Epitch;
 Yawgyro -= Eyaw;

  Rollgyro1 -= Eroll1;
 Pitchgyro1 -= Epitch1;
 Yawgyro1 -= Eyaw1;


 // calcul de l'angle par integration
 angleRO += (Rollgyro / (FREQ * SSF_GYRO));
 anglePO += (-Pitchgyro / (FREQ * SSF_GYRO));  
  angleRO1 += (Rollgyro1 / (FREQ * SSF_GYRO));
 anglePO1 += (-Pitchgyro1 / (FREQ * SSF_GYRO));


 // Transfert de l'angle entre le "Pitch" et le "Roll"  en fonction du YAW est converti le résultat en degrés
 anglePO += angleRO * sin(Yawgyro * (PI / (FREQ * SSF_GYRO * 180)));

 angleRO -= anglePO * sin(Yawgyro * (PI / (FREQ * SSF_GYRO * 180)));

 anglePO1 += angleRO1 * sin(Yawgyro1 * (PI / (FREQ * SSF_GYRO * 180)));

 angleRO1 -= anglePO1 * sin(Yawgyro1 * (PI / (FREQ * SSF_GYRO * 180)));

 }

 void ANacc(){ // cette fonction calcul l'angle de l'accélérométre est convertie le resultat en degrés


     acc_total_vector = sqrt(pow(Rollacc, 2) + pow(Pitchacc, 2) + pow(Yawacc, 2));
     acc_total_vector1 = sqrt(pow(Rollacc1, 2) + pow(Pitchacc1, 2) + pow(Yawacc1, 2));


 if (abs(Rollacc) < acc_total_vector) {
   RollaccA = asin((float)Pitchacc / acc_total_vector) * (180 / PI);
 }

 if (abs(Pitchacc) < acc_total_vector) {
   PitchaccA = asin((float)Rollacc / acc_total_vector) * (180 / PI);
 }

  if (abs(Rollacc) < acc_total_vector) {
   RollaccA1 = asin((float)Pitchacc1 / acc_total_vector1) * (180 / PI);
 }


}


 void calculangle () { // calcul de l'angle est de l'angle/S

 if (initialized) {
   //  filtre plus le temps de bouclage est long (1-t)
   angleRO = angleRO * 0.98 + RollaccA * 0.02;//0.98  0.02
   angleRO1 = angleRO1 * 0.98 + RollaccA1* 0.02;
 } else {
   // premiere mesure angle de l' acceleromettre
   angleRO = RollaccA;
   angleRO1 =  RollaccA1;
   initialized = true;
 }


 angleR  = angleR * 0.9 + angleRO * 0.1;
 angleP = angleP * 0.9 + angleRO1 * 0.1;
 ASR = (ASR * 0.7) + ((Rollgyro / 65.5) * 0.3);
 ASP = (ASP * 0.7) + ((Rollgyro1 / 65.5) * 0.3);
 ASY = (ASY * 0.7) + ((Yawgyro/ 65.5) * 0.3);


}








ISR(PCINT0_vect)  // Routines d'interruptions calcul des l'argeur d'impulsions recut
{
   current_time = micros();


   if (PINB & B00000001) {              
       if (previous_state[0] == LOW) {
           previous_state[0] = HIGH;
           timer[0]          = current_time;
       }
   } else if(previous_state[0] == HIGH) {
       previous_state[0] = LOW;
       pulse_duration[0] = current_time - timer[0];
   }


   if (PINB & B00000010) {
       if (previous_state[1] == LOW) {
           previous_state[1] = HIGH;
           timer[1]          = current_time;
       }
   } else if(previous_state[1] == HIGH) {
       previous_state[1] = LOW;
       pulse_duration[1] = current_time - timer[1];
   }


   if (PINB & B00000100) {
       if (previous_state[2] == LOW) {
           previous_state[2] = HIGH;
           timer[2]          = current_time;
       }
   } else if(previous_state[2] == HIGH) {
       previous_state[2] = LOW;
       pulse_duration[2] = current_time - timer[2];
   }


   if (PINB & B00001000) {
       if (previous_state[3] == LOW) {
           previous_state[3] = HIGH;
           timer[3]          = current_time;
       }
   } else if(previous_state[3] == HIGH) {
       previous_state[3] = LOW;
       pulse_duration[3] = current_time - timer[3];
   }


}
