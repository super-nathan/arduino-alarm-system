// --------------------------------------------------------------------------
// +
// +               COPYRIGHT 2013 JOSEPH KO AND NATHAN WEBER
// +
// +                   RELEASED UNDER THE MIT LICENSE
// +                  http://rem.mit-license.org/license.txt
// +
// -------------------------------------------------------------------------





#include <Keypad.h>  // requires "keypad" library

char* secretCode = "235711";  // Change this to change access codes

// PINS
int redPin = 13;
int greenPin = 12;
int buttonPin = 10;    
int photocellPin = 1;    
int speakerPin = 9; 


int photocellReading;     
int position = 0;
int buttonState = 0; 
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// MORE PINS!!!!!!!!!!  THESE ARE FOR THE KEYPAD
byte rowPins[rows] = {5, 4, 3, 2}; 
byte colPins[cols] = {8, 7, 6}; 




Keypad keypad = Keypad(makeKeymap(keys), 
                       rowPins, colPins,
                       rows, cols);




void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT);     
  setLocked(true);
  Serial.begin(9600);   

}





void loop()
{
  photocellReading = analogRead(photocellPin);  
  if (photocellReading < 520) 
  {
    ALARM();
  } 
  else{
  char key = keypad.getKey();
 
  if (key == secretCode[position]) {
    position++;
  }}
    buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {     
    setLocked(false);
    position = 0;
    delay(5000);
    setLocked(true);
  }
  
  if (position == 6) {
    setLocked(false);
    position = 0;
    delay(5000);
    setLocked(true);
  }
  
 
  delay(50);
}

void setLocked(int locked)
{
  Serial.println(locked);
  if (locked) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }
}

void ALARM()  { 
  // fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(speakerPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(speakerPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}

