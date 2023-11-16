/*
  ESP32 access build-in temperature & hall sensors reading
  and send it to ThingSpeak as an IoT Node

  @g3jerrie
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
// Created an Header file @ ./include/creds.h & declared variables with my creds here
#include <creds.h>

// Declaring Objects
WiFiClient client;
HTTPClient http;

extern "C" // Extern C is used when we are using a funtion written in "C" language in a C++ code.
{
  uint8_t temprature_sens_read(); // This function is written in C language
}

// Declaring the methods
void connectWiFi(void);
uint8_t temprature_sens_read(); // Declaring again in C++ section
float getTempReading();
int getHallReading();
void sendTSDataFeed(float, int);

void setup()
{
  Serial.begin(115200); // Begining the Serial Monitor at the provided Baud rate
  while (!Serial)
  {
    delay(100);
  }
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush(); // flush is used to clear the stack
    delay(1000);
  }
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); // for blinking status

  connectWiFi(); // Connecting to WiFi Network
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  // Call the function to get the Temp and Hall Readings
  float tempC = getTempReading();
  int hallSensorReading = getHallReading();
  sendTSDataFeed(tempC, hallSensorReading);
  digitalWrite(LED_BUILTIN, LOW);
  // Wait for 16 seconds, because the message update interval limit is every 15 seconds in the free license ThingSpeak account
  delay(16000);
}

void connectWiFi()
{
  Serial.println();
  Serial.println("*******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid1);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid1, password1);
  digitalWrite(LED_BUILTIN, HIGH);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("");
  Serial.println("Connected to WiFi.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
}

// Define a function to convert and print the temperature
float getTempReading()
{
  // Read the temperature sensor
  float tempF = temprature_sens_read();
  // Convert Fahrenheit to Celsius
  float tempC = (tempF - 32) / 1.8;
  // Create a buffer to store the formatted output
  char buffer[93];
  // Use sprintf() to format the output as a single string
  sprintf(buffer, "Temperature in degree Fahrenheit: %.2f F\nTemperature in degree Celsius: %.2f C\n", tempF, tempC);
  // Print the buffer with one Serial.print() call
  Serial.print(buffer);
  return (tempC);
}

int getHallReading()
{
  int hallSensorReading = hallRead();
  Serial.printf("Hall Sensor Value is: %i\n", hallSensorReading);
  return (hallSensorReading);
}

void sendTSDataFeed(float temp, int hall)
{
  
  String url = baseUrl + "/update?" + "api_key=" + writeApiKey + "&field1=" + temp + "&field2=" + hall;
  Serial.printf("Sending thingspeak datafeed via: %s \n", url.c_str());
  http.begin(client, url);
  Serial.println("Waiting for reponse");
  int httpCode = http.GET();
  if (httpCode > 0)
  {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode); // on unsucessful connection code will be -1
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
