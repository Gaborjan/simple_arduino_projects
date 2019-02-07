/* 
* This program display a landscape. Establish a contact via serial port
* and read a light value (1..8) from the Arduino. If the light value is high,
* the landscape will be brighter, if the light is low, the landscape will darker.
* Actually we simulate a totel eclipse or sunset/sunrise;
* 
* Author: Gábor Jánvári 02.2019.
*
*/

import processing.serial.*;

PImage img;
Serial myPort;
int lightValue; //we get the value from Arduino 
boolean isNewValue=false; // get a new value from Arduino?
boolean firstContact=false; // did we made the contact yet?
int previousLightValue; 
final String fileName="landscape_s.jpg";

void setup() {
  // Images must be in the "data" directory to load correctly
  size(577,433); // this is the size of the sample image
  loadImage(); 
  String portName=Serial.list()[0];
  myPort=new Serial(this,portName,9600); //a new port object
}
 
void draw() {
  image(img, 0, 0);
  isNewValue=previousLightValue!=lightValue; // changed the light value?
  if (isNewValue) { // if changed, we update the picture
    switch (lightValue) {
      case 1: {//max. light  
        noTint();
        break;
      }
      case 2: {
        tint(230);
        break;
      }
      case 3: {
        tint(200);
        break;
      }
      case 4: {
        tint(150);
        break;
      }
      case 5: {
        tint(120);
        break;
      }
      case 6: {
        tint(90);
        break;
      }  
      case 7: {
        tint(60);
        break;
      }
      case 8: { // minimal light
        tint(20);
        break;
      }        
    } //switch
  } //isNewValue 
}  // draw

void serialEvent(Serial myPort) {
  int inByte=myPort.read(); //read a byte from serial port
  if (firstContact==false) { //if this the first byte we received  
    if (inByte=='A') { // check is this an 'A' clear the buffer
        myPort.clear(); 
        firstContact=true; // we have the contact now
        myPort.write('A'); // send back a character, ask for the next byte
    }
  }
  else { // read the next lightvalue from Arduino
    previousLightValue=lightValue; // save the previous value
    lightValue=inByte; // the actual value
    myPort.write('A'); // ask for the next byte (light value) from Arduino
  }
}
 
void loadImage() {
   img = loadImage(fileName);
 }
