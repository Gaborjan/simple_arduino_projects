
const int ledPins[] = {2,3,4,5,6,7,8,9}; //LED channels we use
const int photoPin = A0; // photo diode analag channel
const int maxALevel=500; //max. light level that we process from photo resistor
//the real max. is 1023, though should optimalization, depends on circumstances
//the lighter place should use smaller value
const int minLED=1; //min. pieces of LED
const int maxLED=8; //max. pieces of LED
int lightLevel=0;
int diodeLevel=0;



void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++){         
    pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output    
  }
}


void loop(){
  // default to LED's off
  //ledOnOff({0,0,0,0,0,0,0,0});
  diodeLevel=analogRead(photoPin);
  lightLevel=constrain(map(diodeLevel,0,maxALevel,minLED,maxLED),minLED,maxLED);
  Serial.print("Diode level: ");
  Serial.print(diodeLevel);
  Serial.print("     Light level: ");
  Serial.print(lightLevel);
  Serial.println();
  switch (lightLevel) {
    case 1:
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
    case 8:
      ledOnOff({1,0,0,0,0,0,0,0});
      break; 
  }
}  

void ledOnOff(const int (&leds)[8]) {
  for (int i=0;i<=7;i++) {
    if (leds[i]>0) digitalWrite(ledPins[i],HIGH);
    else digitalWrite(ledPins[i],LOW);
  }
}
  
