#include <SPI.h>
#include <LoRa.h>
#define BLYNK_TEMPLATE_ID "TMPL3DSzTmYfF"
#define BLYNK_TEMPLATE_NAME "SOIL MOISTURE"
#define BLYNK_AUTH_TOKEN "P45voobmXR_MJlGu1g65NrhxGTUoK-Ib"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>


char ssid[] = "vivo T2";      // Replace with your Wi-Fi SSID
char password[] = "Sukhadchinawale";  // Replace with your Wi-Fi password
BlynkTimer timer;

// LoRa module pins
const int loraCsPin = 15;
const int loraResetPin = 16;
const int loraIntPin = 2;

void setup() {
  Serial.begin(9600);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
 
  // Setup LoRa module
   SPI.begin();
  LoRa.setPins(loraCsPin, loraResetPin, loraIntPin);

  if (!LoRa.begin(433E6)) 
  {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }

  Serial.println("LoRa Receiver is ready.");    
}

void loop() {
   Blynk.run();
    timer.run(); 
    
  // Check if a LoRa packet is received
  if (LoRa.parsePacket()) 
  {
    // Read and print the received soil moisture value
    int receivedSoilMoistureValue = LoRa.parseInt();
    Serial.print("Received Soil Moisture: ");
    Serial.println(receivedSoilMoistureValue);
     Blynk.virtualWrite(V2, receivedSoilMoistureValue/10); 
  }
}