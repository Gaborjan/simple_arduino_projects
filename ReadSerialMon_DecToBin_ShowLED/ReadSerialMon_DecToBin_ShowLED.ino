/*
 * 
 *This program demonstrate how read an integer number from serial monitor. Then from this decimal
 *number we make a binary number, and show this binary number with LEDs. 
 *As we have 8 LEDs only, the min. number is 1, de max. number is 255.
 *It is interesting to see how LEDs change to 1,2,4,8,16,32,64,128, or we just add DEC 1 to these numbers.
 *Also interesting type 85 and 170.
 *Have fun.
 *
 *Gábor Jánvári, 01.2019.
 */

int ledPins[] = {2,3,4,5,6,7,8,9}; //LED channels we use
int number; // the decimal number 
int* binary=new int[8]; // we can store the binary number in this array

void setup() {
  Serial.begin(9600); //setup serial port
  for(int i = 0; i < 8; i++){         
    pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output 
  } 
}

void loop() 
  {
    if (Serial.available() > 0) // is a character available?
    {    
      number=Serial.parseInt(); // reading a row, as an integer number (on monitor, choose new row option)
      if (Serial.read()=='\n') // if no more character in the row (we get one integer number in the previous line)
      {
        if ((number >= 1) && (number <= 255)) //check the number
        {
          Serial.print("Decimal number received: "); // print the DEC number
          Serial.print(number);
          binary=decToBin(number);// call the decToBin method,
          Serial.print(", in binary: " );
          for (int i=0;i<=7;i++) //print the elements of binary array
          {
            Serial.print(binary[i]);
          }
          Serial.print(" ---> I'm showing on LEDs!");
          Serial.println();
          deleteLEDScreen(); //must switch off all LEDs, may be the previous number is shown
          showBinaryOnLED(decToBin(number)); // call the lights up method, we could use binary array too as a 
          //parameter
        } 
        else 
        {
          Serial.println("Number must be min. 1 max. 255!");
        }
      }
      else
      { 
        Serial.println("Not number!");
      }
    }  
  }

//This method convert a decimal number to a binary number. The result will be in an array.
int* decToBin(int number) 
  {
    static int  s[8]; //a template array
    /*That is the algorithm to convert, as we know we want an 8 length binary number we can use for 
     *Since we get the last binary digit in the first step, we have to use the 7-0=7, for the last 
     *array place. In the second round 7-1=6, and so on. We could use "i", but after the cicle we should have
     *reverse the elements of the array. This way no need another for cicle.
     */
    for (int i=0;i<=7;i++) 
    {
      if ((number%2)==0) 
      {
        s[7-i]=0;
      }
      else
      {
        s[7-i]=1;
      }
      number=number/2; 
    }
    return s;
  }

//This simple method lights on that LEDs, where is '1' in the array.
void showBinaryOnLED(int* s) 
  {
    for (int i=0;i<=7;i++) 
    {
      if (s[i]==1) digitalWrite(ledPins[i],HIGH);
    }
  }

//This simple method switch off all LEDs.
void deleteLEDScreen()
  {
    for (int i=0;i<=7;i++) 
    {
      digitalWrite(ledPins[i],LOW);
    }  
  }
