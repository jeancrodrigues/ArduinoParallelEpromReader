/*
	
	Arduino Parallel Eprom Reader
	
	Code that runs on slave Arduino

*/

#include <Wire.h>

//digital input ports
byte inPins[] = {2,3,4,5,6,7,8,9}; 

// Control state pins: OutputEnable, ChipEnable
int outputEnable = 11;
int chipEnable = 10;

//reads input pins
byte readInput(){
  byte input = 0;
  byte mask = 1;
  for(int i = 0; i<8; i++){ 
    if(digitalRead(inPins[i]) == HIGH) input |= mask;
    mask = mask << 1;
  }
  return(input);
} 

//function registered as Wire event, runs when Wire receives data
void receiveData(int maxdata)
{
  while(1 <= Wire.available())
  {
    //receive address
    int c = Wire.read();
    //print output to serial
   
    Serial.println(readInput(), HEX); 
  }
}

void setup()
{

  //begin I2C communication 	
  Wire.begin(2);            

  // register event to receive signal from master
  Wire.onReceive(receiveData);
  
  //set pins for receive data from the eprom
  for(int i = 0; i<8; i++){  
      pinMode(inPins[i], INPUT);
  }
  
  //set control pins and read mode on eprom
  pinMode(outputEnable, OUTPUT);
  pinMode(chipEnable, OUTPUT);
  digitalWrite(outputEnable, LOW);
  digitalWrite(chipEnable, LOW);
  
  //begin serial communication for sending data to computer
  Serial.begin(9600);
    
}

void loop()
{
  // nothing to do here yet!!!
}
