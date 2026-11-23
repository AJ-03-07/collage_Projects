#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>

// Soil moisture sensor pin
const int soilMoisturePin = A0;

// LCD module address
const int lcdAddress = 0x27;
const int lcdCols = 16;
const int lcdRows = 2;

// LoRa module pins
const int loraCsPin = 10;
const int loraResetPin = 9;
const int loraIntPin = 2;

// Create an LCD object
LiquidCrystal_I2C lcd(lcdAddress, lcdCols, lcdRows);

void setup() {
  Serial.begin(9600);

  // Setup LCD
  lcd.begin(lcdCols, lcdRows);
  lcd.backlight();
  lcd.print("Soil Moisture:");

  // Setup LoRa module
  SPI.begin();
  LoRa.setPins(loraCsPin, loraResetPin, loraIntPin);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }
}

void loop() {
  // Read soil moisture value
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Send soil moisture value via LoRa
  sendMessage(soilMoistureValue);

  // Display soil moisture value on LCD
  lcd.setCursor(0, 1);
  lcd.print("Moisture: ");
  
  lcd.print( String(soilMoistureValue/10) + "%");
  delay(3000);
}

void sendMessage(int value) {
  // Send the soil moisture value via LoRa
  LoRa.beginPacket();
  LoRa.print(value);
  LoRa.endPacket();
  Serial.print("Soil Moisture sent: ");
  Serial.println(value);
}