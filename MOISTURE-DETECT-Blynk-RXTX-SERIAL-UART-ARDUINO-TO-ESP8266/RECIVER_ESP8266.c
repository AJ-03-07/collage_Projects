#define BLYNK_TEMPLATE_ID             "TMPL3656ZMhH6"
#define BLYNK_TEMPLATE_NAME           "moisture value"
#define BLYNK_AUTH_TOKEN              "AhlYFQWcFBCQC2P89YQCZ4o22_6av0lL"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char ssid[] = "realme8";      // Replace with your Wi-Fi SSID
char password[] = "12345678";  // Replace with your Wi-Fi password
BlynkTimer timer;

void setup() {
  Serial.begin(115200);  // Initialize serial communication for debugging
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password); 
}

void loop() 
{
  Blynk.run();
    timer.run();     
  // Read data from the Arduino Uno
 if (Serial.available() > 0) {
    int dataReceived = Serial.parseInt();
    if (dataReceived != 0) {
      Serial.println("Received data: " + String(dataReceived));
      dataReceived= dataReceived/10;
      Blynk.virtualWrite(V3, dataReceived); 

    }
  }
}