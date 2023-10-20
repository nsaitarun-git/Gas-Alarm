#include <LiquidCrystal.h>
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

int rs=2;
int en=3;
int d4=8;
int d5=9;
int d6=10;
int d7=11;
int gasPin=A0;
int gasVal;

int touchPin=6;
int touchState;
int buzzPin=5; 
int ledPin=7;


void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(gasPin,INPUT);
  pinMode(touchPin,INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(buzzPin,OUTPUT);
  digitalWrite(buzzPin,LOW);
  digitalWrite(ledPin,LOW);

  lcd.setCursor(1,0);
  lcd.print("Saitarun's Gas");
  lcd.setCursor(6,1);
  lcd.print("Alarm");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("Calibrating MQ-2");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  delay(5000);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Done");
  lcd.setCursor(3,1);
  lcd.print("Calibrating");
  delay(2000);
  lcd.clear();
}

void loop() {
  
  gasVal=analogRead(gasPin);
  Serial.println(gasVal);
  touchState=digitalRead(touchPin);

  if(touchState==0 && gasVal<=290){
  while(gasVal<=290){
  gasVal=analogRead(gasPin);
  lcd.setCursor(0,0);
  lcd.print("Gas Value =");
  lcd.setCursor(11,0);
  lcd.print(gasVal);
  lcd.setCursor(0,1);
  lcd.print("Gas Con = LOW");
  delay(1000);
  lcd.clear();
   }
}

  if(gasVal>=290 && touchState==0){
    while(digitalRead(touchPin)==0){
      gasVal=analogRead(gasPin);
      digitalWrite(buzzPin,HIGH);
      digitalWrite(ledPin,HIGH);
      lcd.setCursor(0,0);
      lcd.print("Gas Value =");
      lcd.setCursor(11,0);
      lcd.print(gasVal);
      lcd.setCursor(0,1);
      lcd.print("Gas Con = HIGH");
      delay(3000);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Potential Gas");
      lcd.setCursor(5,1);
      lcd.print("Leakage");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Check Gas Source");
      lcd.setCursor(6,1);
      lcd.print("Now!");
      delay(3000);
      lcd.clear();
   }
  }

  if(digitalRead(touchPin)==1){
    lcd.setCursor(5,0);
    lcd.print("Alarm");
    lcd.setCursor(3,1);
    lcd.print("Deactivated");
    digitalWrite(buzzPin,LOW);
    digitalWrite(ledPin,LOW);
    delay(2000);
    lcd.clear();
    
  }
}
