int ledPins[] = {2,3,4,5,6,7,8,9}; 
int number;
int* binary=new int[8];

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++){         
    pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output 
  } 
}

void loop() 
  {
    if (Serial.available() > 0) // is a character available?
    {    
      number=Serial.parseInt();
      if (Serial.read()=='\n') 
      {
        if ((number >= 1) && (number <= 255)) 
        {
          Serial.print("Decimal number received: ");
          Serial.print(number);
          binary=decToBin(number);
          Serial.print(", in binary: " );
          for (int i=0;i<=7;i++) 
          {
            Serial.print(binary[i]);
          }
          Serial.print(" ---> I'm showing on LEDs!");
          Serial.println();
          deleteLEDScreen();
          showBinaryOnLED(binary);
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


int* decToBin(int number) 
  {
    static int  s[8];
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

void showBinaryOnLED(int * s) 
  {
    for (int i=0;i<=7;i++) 
    {
      if (s[i]==1) digitalWrite(ledPins[i],HIGH);
    }
  }

void deleteLEDScreen()
  {
    for (int i=0;i<=7;i++) 
    {
      digitalWrite(ledPins[i],LOW);
    }  
  }
