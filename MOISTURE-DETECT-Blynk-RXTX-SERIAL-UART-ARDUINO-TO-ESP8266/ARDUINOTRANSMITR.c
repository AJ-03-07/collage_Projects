#include <SoftwareSerial.h>
int Capacitive_Soil_Moisture_Sensor = A0;
int Soil_Moisture_Sensor_data = 0;
 
 
int data_length; 
String sensorsdata;


SoftwareSerial espSerial(2, 3); // RX, TX (Connect Arduino's TX to ESP's RX and vice versa)

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  pinMode(Capacitive_Soil_Moisture_Sensor,INPUT); 
}

void loop() {
 
MultipleSensors();
/*send_data(sensorsdata , data_length); */
 
sensorsdata = ""; 
 
  
  espSerial.print("V1"); // Send value to virtual pin V1 on Blynk
  espSerial.println(Soil_Moisture_Sensor_data);
sensorsdata = "";
  delay(1000); // Adjust the delay as needed
}
void MultipleSensors()
{
 Soil_Moisture_Sensor_data = analogRead(Capacitive_Soil_Moisture_Sensor); 
 
 sensorsdata = sensorsdata + Soil_Moisture_Sensor_data/10 ; 
/* Serial.print("sensor value:");*/
 Serial.println(Soil_Moisture_Sensor_data);
}