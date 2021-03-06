#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 mpu(0x68);
MPU6050 mpu1(0x69);

#define MPU_ADDRESS 0x68  // I2C address of the MPU-6050
#define MPU_ADDRESS1 0x69
#define FREQ        250   // Sampling frequency
#define SSF_GYRO    65.5  // Sensitivity Scale Factor of the gyro from datasheet

boolean initialized;
long Eroll, Epitch, Eyaw,  acc_total_vector, premicros,Eroll1, Epitch1, Eyaw1,  acc_total_vector1;
int Rollgyro, Pitchgyro, Yawgyro, Rollacc, Pitchacc, Yawacc, temperature,Rollgyro1, Pitchgyro1, Yawgyro1, Rollacc1, Pitchacc1, Yawacc1, temperature1;
float angleRO, anglePO,RollaccA , PitchaccA,angleRO1, anglePO1,RollaccA1 , PitchaccA1;

volatile unsigned long timer[6];
volatile unsigned long current_time;
volatile byte previous_state[6];
volatile unsigned int pulse_duration[6] = {1500, 1500, 1500, 1000,1000,1000};



float KYP = 0; // Coefficient YAW 4  0.02
float KYI = 0;
float KYD = 0;

float KRP = 1.3;
float KRI = 0.04;
float KRD = 18;//18;

float KPP = 1.3; //1.3;// Coefficient Pitch
float KPI =0.04; //0.04;
float KPD =18;//18;

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
 PCICR  |= (1 << PCIE0);
 PCMSK0 |= (1 << PCINT0);
 PCMSK0 |= (1 << PCINT1);
 PCMSK0 |= (1 << PCINT4);
 PCMSK0 |= (1 << PCINT3);
 PCMSK0 |= (1 << PCINT5);
 PCMSK0 |= (1 << PCINT7);
batterieV= (analogRead(0) + 65) * 1.2317;
DDRA  |= B11110000;
Wire.begin();
TWBR = 24;
mpu.initialize();
mpu.setXAccelOffset(-3771);
mpu.setYAccelOffset(-1100);
mpu.setZAccelOffset(1106);
mpu.setXGyroOffset(-10);
mpu.setYGyroOffset(70);
mpu.setZGyroOffset(-8);

 mpu1.initialize();
mpu1.setXAccelOffset(497);
mpu1.setYAccelOffset(1703);
mpu1.setZAccelOffset(1148);
mpu1.setXGyroOffset(-629);
mpu1.setYGyroOffset(206);
mpu1.setZGyroOffset(-8);

communication();
Emoyen();


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


void consigne(){

ConsG = 0;
ConsP = 0;
ConsR = 0;
ConsY = 0;

chanel1 =  pulse_duration[3]; //interrupt 11  Recepteur:CH3  "GAZ"
chanel2 =  pulse_duration[1]; //interrupt 9  Recepteur:CH2   "PITCH"
chanel3 =  pulse_duration[2]; //interrupt 10  Recepteur:CH4 "ROLL"
chanel4 =  pulse_duration[0]; //interrupt 8  Recepteur:CH1  "YAW"

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

    anglemaxP = 15 * angleP;
    anglemaxR = 15 * angleR;

    ConsP -= anglemaxP ;
    ConsP /= 3;
    ConsR -=  anglemaxR;
    ConsR /= 3;
    ConsY /= 3;


}



void PID(){
//erreur proportionnelle
EpropP = ASP - ConsP;
EpropR = ASR - ConsR;
EpropY = ASY - ConsY;


//erreur intégré
EintP +=  EpropP;
EintR +=  EpropR;
EintY +=  EpropY;

if ( EintP > 400 ) EintP = 400;
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



 
EPIDR = KRP * EpropR + KRI * EintR + KRD * EdevR;
EPIDP = KPP * EpropP + KPI * EintP + KPD * EdevP;
EPIDY = KYP * EpropY + KYI * EintY + KYD * EdevY;



if ( EPIDP > 400 ) EPIDP = 400;
if ( EPIDP < -400 )EPIDP = -400;
if (EPIDR > 400 ) EPIDR = 400;
if (EPIDR < -400 )EPIDR = -400;
if ( EPIDY > 400 ) EPIDY = 400;
if ( EPIDY < -400 )EPIDY = -400;

}


void resetvariable(){
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

void activation(){
if(decollage == 0 && chanel1 <= 1008 && chanel4 > 1980 && chanel3 > 1980){
  decollage = 1;
  resetvariable();
}

 if(decollage == 1 && chanel1 <= 1008 && chanel2 > 1980 && chanel4 < 1008){
  decollage = 0;
}



}



void Signeauxcorrec(){
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


}

void transmission(){



while (micros()-prevmicros < 4000);

prevmicros = micros();
PORTA |= B11110000;


while( PORTA >= 16){
prelmicros = micros();
if ( (mot1 + prevmicros) <= prelmicros) PORTA &= B11101111;
if ( (mot2 + prevmicros) <= prelmicros) PORTA &= B11011111;
if ( (mot3 + prevmicros) <= prelmicros) PORTA &= B10111111;
if ( (mot4 + prevmicros) <= prelmicros) PORTA &= B01111111;

}

}



void communication(){

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



void Emoyen(){
  int max_samples = 2000;
for (int i = 0; i < max_samples; i++) {
  lectureMPU();
   Eroll1 += Rollgyro1;
  Epitch1 += Pitchgyro1;
  Eyaw1 += Yawgyro1;

  Eroll += Rollgyro;
  Epitch += Pitchgyro;
  Eyaw += Yawgyro;
  PORTA |= B11110000;
  delayMicroseconds(1000);
  PORTA &= B00001111;

  delay(3);
}
Eroll /= max_samples;
Epitch /= max_samples;
Eyaw /= max_samples;

Eroll1 /= max_samples;
Epitch1 /= max_samples;
Eyaw1 /= max_samples;


}


void lectureMPU (){

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


void ANgyro() {

Rollgyro -= Eroll;
Pitchgyro -= Epitch;
Yawgyro -= Eyaw;

 Rollgyro1 -= Eroll1;
Pitchgyro1 -= Epitch1;
Yawgyro1 -= Eyaw1;



angleRO += (Rollgyro / (FREQ * SSF_GYRO));
anglePO += (-Pitchgyro / (FREQ * SSF_GYRO));
 angleRO1 += (Rollgyro1 / (FREQ * SSF_GYRO));
anglePO1 += (-Pitchgyro1 / (FREQ * SSF_GYRO));



anglePO += angleRO * sin(Yawgyro * (PI / (FREQ * SSF_GYRO * 180)));

angleRO -= anglePO * sin(Yawgyro * (PI / (FREQ * SSF_GYRO * 180)));

anglePO1 += angleRO1 * sin(Yawgyro1 * (PI / (FREQ * SSF_GYRO * 180)));

angleRO1 -= anglePO1 * sin(Yawgyro1 * (PI / (FREQ * SSF_GYRO * 180)));

}

void ANacc(){


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


void calculangle () {

if (initialized) {
  //  filtre plus le temps de bouclage est long (1-t)
  angleRO = angleRO * 0.996 + RollaccA * 0.004;//0.98  0.02
  angleRO1 = angleRO1 * 0.996 + RollaccA1* 0.004;
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

Serial.print("\n");
Serial.print(angleP);
}








ISR(PCINT0_vect)
{
  current_time = micros();

  // Channel 1 -------------------------------------------------
  if (PINB & B00000001) {
      if (previous_state[0] == LOW) {
          previous_state[0] = HIGH;
          timer[0]          = current_time;
      }
  } else if(previous_state[0] == HIGH) {
      previous_state[0] = LOW;
      pulse_duration[0] = current_time - timer[0];
  }

  // Channel 2 -------------------------------------------------
  if (PINB & B00000010) {
      if (previous_state[1] == LOW) {
          previous_state[1] = HIGH;
          timer[1]          = current_time;
      }
  } else if(previous_state[1] == HIGH) {
      previous_state[1] = LOW;
      pulse_duration[1] = current_time - timer[1];
  }

  // Channel 3 -------------------------------------------------
  if (PINB & B00010000) {
      if (previous_state[2] == LOW) {
          previous_state[2] = HIGH;
          timer[2]          = current_time;
      }
  } else if(previous_state[2] == HIGH) {
      previous_state[2] = LOW;
      pulse_duration[2] = current_time - timer[2];
  }

  // Channel 4 -------------------------------------------------
  if (PINB & B00001000) {
      if (previous_state[3] == LOW) {
          previous_state[3] = HIGH;
          timer[3]          = current_time;
      }
  } else if(previous_state[3] == HIGH) {
      previous_state[3] = LOW;
      pulse_duration[3] = current_time - timer[3];
  }

    if (PINB & B00100000) {
      if (previous_state[4] == LOW) {
          previous_state[4] = HIGH;
          timer[4]          = current_time;
      }
  } else if(previous_state[4] == HIGH) {
      previous_state[4] = LOW;
      pulse_duration[4] = current_time - timer[4];
  }

     if (PINB & B10000000) {
      if (previous_state[5] == LOW) {
          previous_state[5] = HIGH;
          timer[5]          = current_time;
      }
  } else if(previous_state[5] == HIGH) {
      previous_state[5] = LOW;
      pulse_duration[5] = current_time - timer[5];
  }
}
