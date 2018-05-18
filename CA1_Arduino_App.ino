#include <boarddefs.h> //Including IR remote library.
#include <IRremote.h> //Including IR remote library.
#include <NewTone.h> //Including New Tone library.
#include <LiquidCrystal.h> //Including Display library.
#define TONE_PIN 8 //Defing piezo/speaker ping.

IRsend irsend; //Declaring IR send
LiquidCrystal lcd(12, 11, 7, 6, 5, 4); //Declaring pins for display.
const int buttonPin = 2; //Declaring pin for button input.
int buttonState = 0; //Declaring button state.        
const int speakerPin = 13; //Declaring pin for speaker.
int soundVal = 0; //Declaring intial sound int value.
String currentBus = ""; //Declaring intial currentBus value.

void setup() //Setup of initial variables.
{  
  Serial.begin(9600); //Initialize serial communication at 9600 bits per second.
  lcd.begin(16, 2); //Declaring display rows and colums.
  pinMode(buttonPin, INPUT); //Declaring button pin as input.
}

void loop() { 
  int sensorValue = analogRead(A0); //Read the input value of the potentiometer on analog pin 0.
  buttonState = digitalRead(buttonPin); //Read the state of the button value.
  if (sensorValue <= 341){ //Check if the potentiometer value is less then 341.
    if (soundVal != 1){ //Check if soundVal is not equal to 1.
      NewTone(TONE_PIN, 1000, 250); //Play note sound for duration.
      soundVal = 1; //Change soundVal to 1.
      lcd.clear(); //Clear the LCD.
      lcd.print("Route 46a"); //Print a message to the LCD.
      delay(1); //Add delay.
    }
    irsend.sendSony(1130, 12); //Output decimal  value to IR blaster.
    currentBus = "46a"; //Change currentBus value.
    delay(40); //Add delay.
  }
  if (sensorValue > 341 && sensorValue <= 682){ //Check if the potentiometer value is greater then 341 and less then 682.
    if (soundVal != 2){ //Check if soundVal is not equal to 2.
      NewTone(TONE_PIN, 600, 250); //Play note sound for duration.
      soundVal = 2; //Change soundVal to 2.
      lcd.clear(); //Clear the LCD.
      lcd.print("Route 102"); //Print a message to the LCD.
      delay(1); //Add delay.
    }
    irsend.sendSony(258, 12); //Output decimal value to IR blaster.
    currentBus = "102"; //Change currentBus value.
    delay(40); //Add delay.
  }
  if (sensorValue > 682 && sensorValue <= 1023){ //Check if the potentiometer value is greater then 682 and less then 1023.
    if (soundVal != 3){ //Check if soundVal is not equal to 3.
      NewTone(TONE_PIN, 900, 250); //Play note sound for duration.
      soundVal = 3; //Change soundVal to 3.
      lcd.clear(); //Clear the LCD.
      lcd.print("Route 32x"); //Print a message to the LCD
      delay(1); //Add delay.
    }
    irsend.sendSony(815, 12); //Output decimal value to IR blaster.
    currentBus = "32x"; //Change currentBus value.
    delay(40); //Add delay.
  }
  if (buttonState == HIGH){ //Check if button is pressed.
    lcd.clear(); //Clear the LCD.
    lcd.print("Last Call: " + currentBus); //Print a message to the LCD
    delay(2000); //Add delay.
    irsend.sendSony(111, 12); //Output decimal value to IR blaster.
    soundVal = 0; //Reset soundVal back to 0.
  }
}
