#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>

#define LIGHT_ANALOG_PIN A0     
#define POTENTIOMETER_PIN A1     
#define BUZZER_PIN 8             


Adafruit_HTU21DF htu = Adafruit_HTU21DF();

int currentPage = 1;
int lastPage = 1;

LiquidCrystal_I2C lcd(0x27, 16, 2);




unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  if (!htu.begin()) {
    Serial.println("Ошибка HTU21D!");
  }
  
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Hello Sir!");
  
  delay(2000);
}


void playBeep() {
  tone(BUZZER_PIN, 523, 150);
  delay(200);
  tone(BUZZER_PIN, 698, 150);
  delay(200);
  noTone(BUZZER_PIN);
}


void loop() {

  float temp = htu.readTemperature();
  float humidity = htu.readHumidity();

  int sensorValue = analogRead(POTENTIOMETER_PIN);

  if (sensorValue >= 0 && sensorValue < 512) {
    currentPage = 1;
  }  else {
    currentPage = 2;
  }
  
  if (currentPage != lastPage) {
    playBeep();
    lastPage = currentPage;
  }

  lcd.clear();
  
  switch(currentPage) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Temperature:");
      lcd.setCursor(0, 1);
      lcd.print((int)temp);
      lcd.print(" C");
      break;
      
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Humidity:");
      lcd.setCursor(0, 1);
      lcd.print((int)humidity);
      lcd.print(" %");
      break;
      
  }
  

  delay(100);  
}