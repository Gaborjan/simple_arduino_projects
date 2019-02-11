/**
* This program receive a value from PC (Processing app), and depends on the received
* value, speed up/down a LED animation. (KITT's (Knight Rider) sensor animation.)
* First upload the program to Arduino next start the Processing app. 
* Author: Gábor Jánvári 02.2019.
*/


const int ledPins[] = {2,3,4,5,6,7,8,9}; //LED channels we use
const int minLED=1; //min. pieces of LED
const int maxLED=8; //max. pieces of LED
 
int inByte; //incoming serial byte
//the inicialization values are essential
int act=2; //actual lighting LED
int pre=3; //the previous lighting LED
boolean forward=false; //the animation direction
int intByte=100; 

void setup() {
  Serial.begin(9600);
  while (!Serial) {;} //wait for serial port to connect. Needed for native USB port only
  for(int i = 0; i < 8; i++){         
    pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output  
 }
}

void loop(){
  if ((Serial.available()>0) or (inByte>0)) // if get a valid byte or we do not get a new one, use the last one
  { 
    if (Serial.available()) // 
      inByte=Serial.read();  //get the incoming byte
    delay(255-inByte); // adjust the animation speed
    //LED anomation starts here
    pre=act; // previous LED=actual LED
    // actualizing the actual LED position
    if (forward) 
    {
      if (act<maxLED-2) //before get the end of line
        act++;
      else //at the end of line change direction
      {
        forward=false;
      }  
    }
    else 
    {
      if (act>1) // before get the start of line
        act--; 
      else // at the start of line
      {
        forward=true; // change direction
      }
    } 
    // light on/off the LEDs
    if (forward) 
    {
      digitalWrite(ledPins[pre],LOW);
      digitalWrite(ledPins[act],HIGH);
      digitalWrite(ledPins[pre-1],LOW);
      digitalWrite(ledPins[act+1],HIGH);
    }
    else
    {
      digitalWrite(ledPins[pre],LOW);
      digitalWrite(ledPins[act],HIGH);
      digitalWrite(ledPins[pre+1],LOW);
      digitalWrite(ledPins[act-1],HIGH);
    }
  }
}
  


  
