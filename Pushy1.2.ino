/*
Pushy 1.2 Linear Acuator for Arduino UNO
Advanced Propulsion Laboratory
University of Washington

by Hans Martin 
2018
*/

// sudo chmod 666 /dev/ttyACM0

#include<LiquidCrystal.h>

const int enablePin = 7;
const int stepPin = 6;
const int directionPin = 5;
const int switchPin = 4;
const int buttonPin = 2;
int step;
int steps = 100;
int buttonState = 0;
int lastbuttonState = 0;
int buttonCounter = 0;
int switchState;
double resolution = steps/10;
int travel = 0;


LiquidCrystal lcd(13,12,11,10,9,8);

void setup() {
      
  lcd.begin(16,2); // 16x2 display
  lcd.setCursor(0,0);
  lcd.print("Res: 10");
  lcd.setCursor(10,0);
  lcd.print("mm");
  
  pinMode(enablePin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

}

void stepAction() {
  
  //if ( travel +10 < 230 && travel -10 > -230 ) {

  for (step = 0; step <= 500; step++) {
    delay(3.5);
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    lcd.setCursor(13,1);
    lcd.print("...");
  }
  
//}
}

void printPos() { 
  
  lcd.setCursor(5,2);
  lcd.print("    ");

  if (switchState == LOW) {
    
    travel = travel - 10;
    
  } else {
    
    travel = travel + 10;
    
  }
  
}

void listenSwitch() {
  
  switchState = digitalRead(switchPin);
  
  if (switchState == LOW) {
  
    lcd.setCursor(14,0);
    lcd.print("IN");
    digitalWrite(directionPin, LOW);
  
  } else {
  
    lcd.setCursor(14,0);
    lcd.print("OT");
    digitalWrite(directionPin, HIGH);
    
  }
  
}

void listenButton() {
  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastbuttonState) {
  
    if (buttonState == LOW) { //&& travel < 220 && travel > -220) {
      buttonCounter++;
      stepAction(); 
      printPos();
       
    } else {
      
      lcd.setCursor(13,1);
      lcd.print("   ");
    
    }
  
  delay(500);
    
  }
  
}

void loop() {
  
  lcd.setCursor(0,1);
  lcd.print("Pos: ");
  lcd.print(travel);
  lcd.setCursor(10,2);
  lcd.print("mm");
  
  listenSwitch();
  listenButton();
  
  lastbuttonState = buttonState;
  
}
