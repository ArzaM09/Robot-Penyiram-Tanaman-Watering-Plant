int relay = 8;
#define soil A0
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SoftwareSerial.h>
SoftwareSerial bt(6, 7); // RX, TX
#include <Servo.h> // servo library 
Servo myservo; // servo name

int motor1 = 5;
int motor2 = 4;
int motor3 = 3;
int motor4 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(relay, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  Serial.begin(9600);
  bt.begin(9600);
  myservo.attach(9);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("=== Soil Bot ===");
  lcd.setCursor(0, 1);

  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
   if(bt.available()> 0 ) // receive number from bluetooth
  {
   String terima = bt.readString();

    if (terima == "S"){
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, HIGH);
    }
    else if (terima == "M"){
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, HIGH);
    }
    else if (terima == "L"){
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
    }
    else if (terima == "R"){
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, HIGH);
    }
    else if (terima == "A"){
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, HIGH);
      digitalWrite(motor4, LOW);
    }
    else if (terima == "C"){
      myservo.write(0);
    }
    else if (terima == "D"){
      myservo.write(90);
    }
  }
  
  
  int value = analogRead(soil); // read the analog value from sensor
  // Serial.print("Moisture: ");
  // Serial.println(value);
  lcd.setCursor(0, 0);
  lcd.print("Moisture : ");
  lcd.setCursor(11, 0);
   lcd.print(value);
  lcd.setCursor(0, 1);
  lcd.print("Keadaan: ");
  if(value > 400 && value<=900){
    digitalWrite(relay, HIGH);
    // Serial.println("hidup");
    lcd.setCursor(9, 1);
    lcd.print("Kering");
  }
  else if(value>0 && value<=400){
    digitalWrite(relay, LOW);
    // Serial.println("Mati");
    lcd.clear();
    lcd.setCursor(9, 1);
    lcd.print("Basah");
  }
  else{
    lcd.setCursor(9, 1);
    lcd.print("Normal"); 
  }
  delay(500);
}