#include <SimpleTimer.h>

#define BLYNK_TEMPLATE_ID "TMPL3_4GNsMIo"
#define BLYNK_TEMPLATE_NAME "HUMIDITY AND TEMPERATURE"
#define BLYNK_AUTH_TOKEN "IoNp-D3g19B8jhpbkyFIhAbYdm1LJgYA"


#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define rain A0
#define light D0
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi Note 10s";
char pass[] = "11111111";

#define DHTPIN 2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address to 0x27 and 16x2 display size
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: Humidity:");

}

void loop()
{
  Blynk.run();
  timer.run();

   delay(2000); // Delay for 2 seconds between sensor readings
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(false); // true for Fahrenheit, false for Celsius

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: " + String(temperature) + (char)223 + "C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: " + String(humidity) + "%");

  delay(3000); // Delay for 5 seconds between LCD updates
}