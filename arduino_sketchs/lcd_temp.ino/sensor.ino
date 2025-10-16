#include <LiquidCrystal.h>

// Definiciones de pines
const int temperature= A0;
const int LED_RED = 13;
const int Motor= 10;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(LED_RED, OUTPUT); 
  pinMode(Motor, OUTPUT); 
  lcd_1.begin(16, 2);       
}

void loop() {
  int sensorValue = analogRead(temperature);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100; 

  lcd_1.clear();

 lcd_1.setCursor(0, 0);
  lcd_1.print("Temperatura: ");
  lcd_1.print(temperature);
  lcd_1.print(" C");

  // Validaciones
  if (temperature <= 10) {
    digitalWrite(LED_RED, HIGH); 
    delay(500);    
    digitalWrite(LED_RED, LOW);
    delay(500);
    digitalWrite(Motor, LOW); 
  } else if (temperature >= 11 && temperature <= 25) {
    digitalWrite(LED_RED, LOW);   
    digitalWrite(Motor, LOW);
  } else if (temperature >= 26) {
    digitalWrite(LED_RED, HIGH); 
    digitalWrite(Motor, HIGH);
  }

  delay(1000); 
}
