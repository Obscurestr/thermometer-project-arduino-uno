#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <LowPower.h>
#define DHTTYPE DHT11   

// Sensor pins
#define DHTPIN1 2
#define DHTPIN2 3

// Relay and threshold
#define RELAY_PIN 8
#define TEMP_THRESHOLD 22.0 

// SD card
#define CSPIN 4

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
File logFile;

void setup() {
  Serial.begin(9600);

  // Initialize sensors
  dht1.begin();
  dht2.begin();

  // Relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thermometer");

  // SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(CSPIN)) {
    Serial.println("FAILED");
    lcd.setCursor(0, 1);
    lcd.print("SD FAIL");
  } else {
    Serial.println("READY");
    lcd.setCursor(0, 1);
    lcd.print("SD Ready");
    delay(1000);
  }
}

void loop() {
  delay(2000);

  // Read sensors
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();

  if (isnan(t1) || isnan(h1) || isnan(t2) || isnan(h2)) {
    Serial.println("Error reading sensors!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor error");
    return;
  }

  // Serial output
  Serial.print("Room1: "); Serial.print(t1); Serial.print("C "); Serial.print(h1); Serial.print("% | ");
  Serial.print("Room2: "); Serial.print(t2); Serial.print("C "); Serial.println(h2);

  // LCD output
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R1:"); lcd.print(t1, 1); lcd.print("C "); lcd.print(h1, 0); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("R2:"); lcd.print(t2, 1); lcd.print("C "); lcd.print(h2, 0); lcd.print("%");

  // Relay control (based on Room1 temperature)
  if (t1 < TEMP_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.setCursor(10, 1);
    lcd.print("Heat ON ");
    Serial.println("Heater ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(10, 1);
    lcd.print("Heat OFF");
    Serial.println("Heater OFF");
  }

  // SD card logging
  logFile = SD.open("data.txt", FILE_WRITE);
  if (logFile) {
    logFile.print("R1 Temp: "); logFile.print(t1); logFile.print("C Hum: "); logFile.print(h1);
    logFile.print("% | R2 Temp: "); logFile.print(t2); logFile.print("C Hum: "); logFile.print(h2); logFile.println("%");
    logFile.close();
    Serial.println("Data saved to SD");
  } else {
    Serial.println("Error opening data.txt");
  }
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
 