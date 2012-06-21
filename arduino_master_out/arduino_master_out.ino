/*
	
	Arduino Parallel Eprom Reader
	
	Code that runs on master Arduino
	
*/

#include <Wire.h>

byte outPins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};

int led=13;
long minadr = 0;
long maxadr = 10000;

void blinkLed(int delaytime){
  
  digitalWrite(led,HIGH);
  delay(delaytime);
  digitalWrite(led,LOW);
  delay(delaytime);
  
}

void addressOut(long address){
  int mask = 1;
  for(int i = 0; i<13; i++) {
    if((mask & address) != 0) digitalWrite(outPins[i], HIGH); else digitalWrite(outPins[i],LOW);
    mask = mask << 1;
    
  }
  if((mask & address) != 0) digitalWrite(A2, HIGH); else digitalWrite(A2,LOW);
    mask = mask << 1;
  if((mask & address) != 0) digitalWrite(A0, HIGH); else digitalWrite(A0,LOW);
    mask = mask << 1;
  if((mask & address) != 0) digitalWrite(A1, HIGH); else digitalWrite(A1,LOW);
    mask = mask << 1;  
  
}

void setup()
{
  Wire.begin();
  for(int i = 0; i<13; i++){  
    pinMode(outPins[i], OUTPUT);
  }
  pinMode(A2, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(led, OUTPUT);
  
}

void sendAdress(long adress){
  
  Wire.beginTransmission(2); 
  Wire.write(adress);            
  Wire.endTransmission();     
  blinkLed(25);
  
}

boolean done = false;

void loop()
{  
  int l;
  
  if(done==false){
  
	for(l=0;l<5;l++) blinkLed(1000);// blink led 5 times before start
    
    for(long i = minadr; i < maxadr; i++) {
	  // write address on input pins	
      addressOut(i);
	  // sends address to slave 
      sendAdress(i);
	}
	
    done=true;  
  }
  
  while(true)blinkLed(2000);//blink led after reading all addresses
 
}
