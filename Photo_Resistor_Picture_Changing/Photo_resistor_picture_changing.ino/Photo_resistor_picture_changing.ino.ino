/*
 * The circuit contains a photo diode and 8 LEDs. Continusly measure the light,
 * and switch on/off LEDs the value of measured light.
 * More light means more LEDs are switched on.
 * Establish a contact on the serial port, and send this value (1..8) to the 
 * computer, where we read it. In a Processing sketch a landscape will change,
 * more lights means lighter picture, actually simulatin a total eclipse or sunset/sunrise.
 * Author: Gábor Jánvári 02.2019.
 * 
 */
const int ledPins[] = {2,3,4,5,6,7,8,9}; //LED channels we use
const int photoPin = A0; // photo diode analag channel
const int maxALevel=500; //max. light level that we process from photo resistor
//the real max. is 1023, though should optimalization, depends on circumstances
//the lighter place should use smaller value
const int minLED=1; //min. pieces of LED
const int maxLED=8; //max. pieces of LED
int lightLevel=0; // derived from diode Level 1..8
int diodeLevel=0; // incoming analog ligth level from photoresistor
int inByte; //incoming serial byte


void setup() {
  Serial.begin(9600);
  while (!Serial) {;} //wait for serial port to connect. Needed for native USB port only
  for(int i = 0; i < 8; i++){         
    pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output  
  establishContact();  // send a bíte to establisg contact until receiver responds
  }
}

 
void loop(){
  if (Serial.available()>0) { // if get a valid byte
  inByte=Serial.read();  //get the incoming byte, though we don't use it
  delay(10); //wait a bit before we send the next analog read - some time need the resistor
  diodeLevel=analogRead(photoPin); //read the analog input from photodiode
  //derive a 1..8 from the analog value, just for sure we use constrain too
  lightLevel=constrain(map(diodeLevel,0,maxALevel,minLED,maxLED),minLED,maxLED);
  switch (lightLevel) { //depends on level light switch on LEDs
    case 1: //The highest level of the light
      ledOnOff({1,1,1,1,1,1,1,1});
      break;  
    case 2:
      ledOnOff({1,1,1,1,1,1,1,0});
      break; 
    case 3:
      ledOnOff({1,1,1,1,1,1,0,0});
      break;  
    case 4:
      ledOnOff({1,1,1,1,1,0,0,0});
      break; 
    case 5:
      ledOnOff({1,1,1,1,0,0,0,0});
      break;  
    case 6:
      ledOnOff({1,1,1,0,0,0,0,0});
      break; 
    case 7:
      ledOnOff({1,1,0,0,0,0,0,0});
      break;  
    case 8: //The lowest level of the light
      ledOnOff({1,0,0,0,0,0,0,0});
      break; 
  }
  Serial.write(lightLevel); // send the light level to receiver
  }
}  

//switch on/off the LEDs, the method gets the command in an array constant
//0=switch off, 1=switch on the proper LED
void ledOnOff(const int (&leds)[8]) {
  for (int i=0;i<=7;i++) {
    if (leds[i]>0) digitalWrite(ledPins[i],HIGH);
    else digitalWrite(ledPins[i],LOW);
  }
}

//trying to make a contact
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300); 
  }
}
  
