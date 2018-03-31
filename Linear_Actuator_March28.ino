/* 
Linear Acuator for Arduino UNO
Advanced Propulsion Laboratory
University of Washington

by Hans Martin 
January 2018
*/

#include <LiquidCrystal.h>

int step;
float travel;
float traveled;

const float hobbRad = 5; // mm
const float stepAngle = 0.01570796; //rad //0.9; //deg
int switchState = 0.0;
int steps = 100;
float resolution = steps/10;

const int buttonPin = 2;
int buttonState = 0;

LiquidCrystal lcd(13,12,11,10,9,8);

void setup()
{
	Serial.begin(9600); // Set Buadrate
	while (! Serial);
	
	lcd.begin(16,2); // 16x2 display
	lcd.setCursor(0,0);
	lcd.print("Res.   ");
	lcd.print(resolution);
	lcd.print("mm");
	
	pinMode(7, OUTPUT); // Enable
	pinMode(6, OUTPUT); // Step
	pinMode(5, OUTPUT); // Direction
	pinMode(4, INPUT); // Switch State
	
	pinMode(2, INPUT);
	
	digitalWrite(7, LOW);
	Serial.print("Type d for in, a for out");
}

void loop ()
{
  buttonState = digitalRead(buttonPin); 
	switchState = digitalRead(4); // Read Switch State
	
	lcd.setCursor(0,1);
	lcd.print(travel);
	lcd.setCursor(12,1);
	lcd.print("mm");


	digitalWrite(5, HIGH); // Toggle Direction

  if (buttonState == HIGH && switchState == HIGH) 
  {
  	digitalWrite(5, HIGH);
  
  	for (step = 0; step <= steps-1; step++)
  	{
  		digitalWrite(6, HIGH);
  		delayMicroseconds(500);
  		digitalWrite(6, LOW);
  		delayMicroseconds(500);
  		travel += resolution/100;
  		
  	}
  }
  
  if (buttonState == HIGH && switchState == LOW)
  {
  	digitalWrite(5, LOW); 
  
  	for (step = 0; step <= steps-1; step++)
  	{
  		digitalWrite(6, HIGH); 
  		delayMicroseconds(500);
  		digitalWrite(6, LOW);
  		delayMicroseconds(500);
  		travel -= resolution/100;
  		
  	}
  }
}