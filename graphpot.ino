
// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


// Replace with your network credentials
const char* ssid = "ssid";
const char* password = "sifra";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const int potPin = 34;

float PotValue = 0;

 
String readPotValue = String(float(analogRead(potPin)/1170.0));

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);


  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/napon", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPotValue.c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  readPotValue = analogRead(potPin)/1170.0;
  Serial.println(readPotValue);
  delay(200);
}
  
