/**
* A controll program for Arduino. With a knob we can adjust "KITT's" (from Knight Rider) sensor 
* speed.
* First upload the program to Arduino next start the Processing app. 
* Author: Gábor Jánvári 02.2019.
* ControlP5 by Andreas Schlegel, 2012
* www.sojamo.de/libraries/controlp5
*
*/

import controlP5.*;
import processing.serial.*;

ControlP5 cp5; // controll container
Serial myPort; // serial port object
PImage img; // image object 
final String fileName="dashboard.jpg";
Knob myKnob; // knob object 
int value;

void setup() {
  size(1280,720); // this is the size of the image
  loadImage();
  image(img, 0, 0);
  // open Serial port
  String portName=Serial.list()[0];
  myPort = new Serial(this,portName,9600);
  cp5 = new ControlP5(this);
  // add a knob and set it 
  myKnob = cp5.addKnob("angry") 
    .setCaptionLabel("Excited Level")
    .setColorCaptionLabel(color(245,168,12))
    .setColorValueLabel(color(245,168,12))
    .setMin(1)
    .setMax(250)
    .setRange(0,250)
    .setValue(133)
    .setPosition(405,490)
    .setRadius(44)
    .setNumberOfTickMarks(15)
    .setViewStyle(3)
    .setTickMarkLength(4)
    .snapToTickMarks(true)
    .setColorForeground(color(245,98,12))
    .setColorBackground(color(98, 3, 3))
    .setColorActive(color(245,98,12))
    .setDragDirection(Knob.HORIZONTAL)
    ;
}

void draw() { //the draw loop is empty
}

// this method actually an action listener fot the knob
void angry(int theValue) { 
  value=theValue;
  myPort.write(value);
}

void loadImage() {
  img = loadImage(fileName);
}
