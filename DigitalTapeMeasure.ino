#include <LiquidCrystal.h>
#define trigPin 9
#define echoPin 8
#define button 2

long duration;
long distance;
int buttonState;

LiquidCrystal lcd(13, 11, 5, 4, 3, 6);

void setup() {  
  lcd.begin(16, 2);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button, INPUT);
  buttonState = 0;
  attachInterrupt(digitalPinToInterrupt(button), Measure, RISING);
  PrintLCD("Ready to Measure!", "");
}

void loop() { 
}

void Measure(){
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  PrintLCD("Distance (in cm)", String(distance));
  Serial.println(distance);
}

void PrintLCD(String top, String bottom){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(top);
  lcd.setCursor(0, 1);
  lcd.print(bottom);
}
