/*     ---------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code             |
 *     |  CIRC-02 .: 8 LED Fun :. (Multiple LEDs)   |
 *     ---------------------------------------------------------
 *  
 *  A few Simple LED animations
 *
 * For more information on this circuit http://tinyurl.com/d2hrud
 *
 *Modified and extended by: Gábor Jánvári, January 2019.
 * 
 */

int ledPins[] = {2,3,4,5,6,7,8,9}; 
//An array to hold the pin each LED is connected to i.e. LED #0 is connected to pin 2, LED #1, 3 and so on
//to address an array use ledPins[0] this would equal 2 and ledPins[7] would equal 9
//2,4,6,8 are green ones, 3,5,7,9 are red ones
short SPEED=1000; //Default delay time in milisec   
int* program = new int[8]; // to store a program    
int programType=0; // There are 13 animation program, the actual one
int counter=0; // Counter for the runned program
 
/* setup() - this function runs once when you turn your Arduino on We the three control pins to outputs */
void setup()
{
  Serial.begin(9600);
  randomSeed(millis);
  //Set each pin connected to an LED to output mode (pulling high (on) or low (off) 
  for(int i = 0; i < 8; i++){         
    pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output  
  }                                  
}
 
 
// loop() - this function will start after setup finishes and then repeat 
 void loop() // run over and over again
{
  //Some example how to program the LEDs manually, 0=ON, 1=OFF 
  //programmedOn({1,1,1,1,1,1,1,1});
  //programmedOn({0,1,0,1,0,1,0,1});
  //programmedOn({1,0,1,0,1,0,1,0});
  //programmedOn({1,1,1,1,1,1,1,1});  
  //program=randomProgram(); // to store a random program
  /*for (int i=0;i<=7;i++) {
    Serial.print(program[i]);
  }*/
  SPEED=random(50,200); // generate a random speed for the next animation, all methods use a delayTime
  //variable, that get the SPEED as a default;
  programType=random(0,13); // generate a random animation
  // Print to console the actual animation's datas
  Serial.print("No.: ");
  Serial.print(counter);
  Serial.print("  Program: ");
  Serial.print(programType);
  Serial.print("  Speed: ");
  Serial.print(SPEED);
  Serial.println();
  // Switch to the generated program and call the correspond method
  switch (programType) {
    case 0:
      inAndOut(); //lights the two middle LEDs then moves them out then back in again
      break;
    case 1:
      oneAfterAnotherLoop(); //light the LEDs one by one, then swith off backward
      break;
    case 2:
      oneOnAtATime();  //light the LEDs one by one, switch off the prevoius
      break;
    case 3:
      redOnlyOneAtTime(); //light red LEDs only one by one
      break;
    case 4:
      greenOnlyOneAtTime(); // light the green LEDs only one by one
      break;
    case 5:
      redOnlyAllOn(); //light all red LEDs
      break;
    case 6:
      redOnlyAllOff(); // switch off all red LEDs
      break;
    case 7:
      greenOnlyAllOn(); // light all green LEDs
      break;
    case 8:
      greenOnlyAllOff(); //switch off all green LEDs
      break;
    case 9:
      allOffAllOn(); // switch all LEDs one by one, and switch off one by one
      break;
    case 10:
       programmedOn(randomProgram()); //generate a random pattern for LEDs
      break;
    case 11: // sometimes switch off all LEDs, for a short "thinking time"
      programmedOn({0,0,0,0,0,0,0,0}); 
      if ((counter % 2)==0) delay(1000); 
      break;
    case 12:
      allOffAllOnFast(); // light all LEDs, switch off all LEDs fast, twice (some blinking effect)
      break;
  }
  counter++;
} 

void oneAfterAnotherLoop(){ ////light the LEDs one by one, then swith off backward
  int delayTime = SPEED;  
//Turn Each LED on one after another
  for(int i = 0; i <= 7; i++){
    digitalWrite(ledPins[i], HIGH);  
    delay(delayTime);                
  }                                  
 //Turn Each LED off one after another
  for(int i = 7; i >= 0; i--){  
    digitalWrite(ledPins[i], LOW);  
    delay(delayTime);                
  }                                  
}
 
void oneOnAtATime(){ //light the LEDs one by one, switch off the prevoius
  int delayTime = SPEED; 
  for(int i = 0; i <= 7; i++){
    int offLED = i - 1;  //Calculate which LED was turned on last time through
    if(i == 0) {         //however if i = 0 we don't want to turn of led -1 (doesn't exist)
      offLED = 7;        //instead we turn off LED 7, (looping around)
    }                    
    digitalWrite(ledPins[i], HIGH);     //turn on LED #i
    digitalWrite(ledPins[offLED], LOW); //turn off the LED we turned on last time
    delay(delayTime);
  }
}
 
void inAndOut(){ ////lights the two middle LEDs then moves them out then back in again
  int delayTime = SPEED; 
  for(int i = 0; i <= 3; i++){
    int offLED = i - 1;  
    if(i == 0) {         
      offLED = 3;        
    }                    
    int onLED1 = 3 - i;       
    int onLED2 = 4 + i;      
    int offLED1 = 3 - offLED; //turns off the LED we turned on last time
    int offLED2 = 4 + offLED; //turns off the LED we turned on last time
    digitalWrite(ledPins[onLED1], HIGH);
    digitalWrite(ledPins[onLED2], HIGH);    
    digitalWrite(ledPins[offLED1], LOW);    
    digitalWrite(ledPins[offLED2], LOW);        
    delay(delayTime);
  }
  //runs the LEDs into the middle
  for(int i = 3; i >= 0; i--){
    int offLED = i + 1;  
    if(i == 3) {         
      offLED = 0;        
    }                    
    int onLED1 = 3 - i;       
    int onLED2 = 4 + i;       
    int offLED1 = 3 - offLED; //turns off the LED we turned on last time
    int offLED2 = 4 + offLED; //turns off the LED we turned on last time
    digitalWrite(ledPins[onLED1], HIGH);
    digitalWrite(ledPins[onLED2], HIGH);    
    digitalWrite(ledPins[offLED1], LOW);    
    digitalWrite(ledPins[offLED2], LOW);        
    delay(delayTime);
  }
  digitalWrite(ledPins[3],LOW);
  digitalWrite(ledPins[4],LOW);
  delay(delayTime);
} //inAndOut() method

void allOffAllOn() { // switch all LEDs one by one, and switch off one by one
  int delayTime=SPEED;
  for (int i=0;i<=7;i++) {
    digitalWrite(ledPins[i],HIGH);
  }
  delay(delayTime);
  for (int i=0;i<=7;i++) {
    digitalWrite(ledPins[i],LOW);
  }
  delay(delayTime);
}

void allOffAllOnFast() { // light all LEDs, switch off all LEDs fast, twice (some blinking effect)
 int  delayTime=SPEED;
  for (int j=0;j<=2;j++) {
    for (int i=0;i<=7;i++) {
      digitalWrite(ledPins[i],HIGH);
    }
    delay(100);
    for (int i=0;i<=7;i++) {
      digitalWrite(ledPins[i],LOW);
    }
    delay(100);
  }
 delay(delayTime);
}

void redOnlyOneAtTime() {//light red LEDs only one by one
  int delayTime=SPEED;
  for (int i=1;i<=7;i=i+2) {
    digitalWrite(ledPins[i],HIGH);
    delay(delayTime);
  }
  delay(delayTime);
  for (int i=1;i<=7;i=i+2) {
    digitalWrite(ledPins[i],LOW);
    delay(delayTime);
  }
  delay(delayTime);
}

void greenOnlyOneAtTime() { // light the green LEDs only one by one
  int delayTime=SPEED;
  for (int i=0;i<=7;i=i+2) {
    digitalWrite(ledPins[i],HIGH);
    delay(delayTime);
  }
  delay(delayTime);
  for (int i=0;i<=7;i=i+2) {
    digitalWrite(ledPins[i],LOW);
    delay(delayTime);
  }
  delay(delayTime);
}

void redOnlyAllOn() { //light all red LEDs
  int delayTime=SPEED;
  for (int i=1;i<=7;i=i+2) {
    digitalWrite(ledPins[i],HIGH);
  }
  delay(delayTime);
}

void redOnlyAllOff() { // switch off all red LEDs
  int delayTime=SPEED;
  for (int i=1;i<=7;i=i+2) {
    digitalWrite(ledPins[i],LOW);
  }
  delay(delayTime);
}

void greenOnlyAllOn() { // light all green LEDs
  int delayTime=SPEED;
  for (int i=0;i<=7;i=i+2) {
    digitalWrite(ledPins[i],HIGH);
  }
  delay(delayTime);
}

void greenOnlyAllOff() { //switch off all green LEDs
  int delayTime=SPEED;
  for (int i=0;i<=7;i=i+2) {
    digitalWrite(ledPins[i],LOW);
  }
  delay(delayTime);
}

/* This method waits an array constant, {0,1,0,1,1,1,0,1} 0=OFF, 1=ON 
 * Array constant is excepted only.
 */
void programmedOn(const int (&leds) [8]) {
  int delayTime=SPEED;
  for (int i=0;i<=7;i++) {
    if (leds[i]>0) digitalWrite(ledPins[i],HIGH);
    else digitalWrite(ledPins[i],LOW);
  }
  delay(delayTime);
}

/*This method waits an array variable, the array elements must be 0 and 1, 0 means OFf, 1 means ON
 */
void programmedOn(int* s) {
  int delayTime=SPEED;
  for (int i=0;i<=7;i++) {
    if (s[i]>0) digitalWrite(ledPins[i],HIGH);
    else digitalWrite(ledPins[i],LOW);
  }
  delay(delayTime);
}

// This method return a randomly generated array, the elements are 0 or 1
int* randomProgram() {
  static int s[8];
  randomSeed(millis());
  for (int i=0;i<=7;i++) {
    s[i]=random(2);
  }
  return s;
}
