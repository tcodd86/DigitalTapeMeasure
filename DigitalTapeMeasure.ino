#include <LiquidCrystal.h>
#define trigPin 9
#define echoPin 8
#define button 2
#define units 3

long duration;
long distance;
bool siUnits;

LiquidCrystal lcd(13, 11, 5, 4, 7, 6);

void setup() {  
  lcd.begin(16, 2);
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button, INPUT);
  pinMode(distance, INPUT);
  siUnits = true;
  attachInterrupt(digitalPinToInterrupt(button), Measure, RISING);
  attachInterrupt(digitalPinToInterrupt(units), Units, RISING);
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
  if(siUnits){
    WriteSI();
  }
  else{
    WriteMetric();
  }
}

void PrintLCD(String top, String bottom){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(top);
  lcd.setCursor(0, 1);
  lcd.print(bottom);
}

void Units(){
  if(siUnits){
    siUnits = false;
    if(duration != 0){
      WriteMetric();
    }
  }
  else{
    siUnits = true;
    if(duration != 0){
      WriteSI();
    }
  }
}

void WriteSI(){
  double distanceInch = (duration * 6.75198)/1000;
  int feet = floor(distanceInch/12);
  float inch = distanceInch - feet*12.0;
  PrintLCD("Distance (in ft)", String(feet) + "ft " + String(inch, 1) + " inches");
}

void WriteMetric(){
  distance = (duration/2) / 29.1;
  PrintLCD("Distance:", String(distance) + " cm");
}
