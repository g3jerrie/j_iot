#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// #define BUZZER_PIN A0 // Pin connected to the buzzer (GPIO16)

// RFID reader pins
#define SS_PIN D4  // Slave Select pin for RC522
#define RST_PIN D3 // Reset pin for RC522

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

// const char* ssid = "g3jerrie_phone1"; // Replace with your Wi-Fi SSID
// const char* password = "Jre@Phone(1)"; // Replace with your Wi-Fi Password
const char* ssid = "No Internet Access"; // Replace with your Wi-Fi SSID
const char* password = "tcjb2805"; // Replace with your Wi-Fi Password
const char* apiKey = "NS8076MO9VB5P179"; // Replace with your ThingSpeak Read API Key
const char* channelID = "2655542"; // Replace with your ThingSpeak Channel ID

// Authorized card UID (example UID, replace with your actual UID)
byte authorizedUID[] = {0xC1, 0xB4, 0x6A, 0x24}; // Replace with your card's UID

// Variable to store the last displayed entry ID
int lastEntryId = 0;

// Variable to validate if is new message received.
bool isNewMessageReceived = false;

// Variable to validate if latest message displayed or not.
bool isNewMessageDisplayed = false;

bool isNewMessage();
void scanRFID();
bool isAuthorized(byte*);
void readMessageFromThingSpeak();
String parseMessage(String);
void displayMessage(String);
void beepBuzzer();

void setup() {
  Serial.begin(9600);
  // digitalWrite(D0, LOW); // Ensure the buzzer is off initially
  // pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  // digitalWrite(BUZZER_PIN, LOW); // Ensure the buzzer is off initially

  SPI.begin(); // Initialize SPI bus

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  
  if (isNewMessageReceived == true && isNewMessageDisplayed == false){
    displayMessage("New message received, scan your RFID to read the message.");
    scanRFID(); // Authorize via RFID to display message
  } else if (isNewMessageReceived == false && isNewMessageDisplayed == false) {
    Serial.println("Waiting for New Message...");
    displayMessage("Waiting for New Message...");
    isNewMessage();
    if (isNewMessageReceived == false && isNewMessageDisplayed == false){
          delay(30000); // Check for new messages every 30 seconds
    }
  } else if(isNewMessageReceived == false && isNewMessageDisplayed == true){
    delay(15000); // Show new messages for 15 seconds
    display.clearDisplay();
    isNewMessageDisplayed = false;
  }
  delay(1000); // Check for new messages every 1 seconds
  }

bool isNewMessage(){
    WiFiClient client;
  if (client.connect("api.thingspeak.com", 80)) {
    String url = "/channels/" + String(channelID) + "/feeds.json?api_key=" + String(apiKey) + "&results=1";
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: api.thingspeak.com\r\n" +
                 "Connection: close\r\n\r\n");
    delay(500);
    
    String response = "";
    while (client.available()) {
      response += client.readStringUntil('\n');
    }

    // Check if the response contains a new message
    Serial.println(response);
    if (response.indexOf("\"entry_id\":") != -1) {
      // Parse the entry ID from the response
      int startIndex = response.indexOf("\"entry_id\":") + 11;
      int endIndex = response.indexOf(",", startIndex);
      int entryId = response.substring(startIndex, endIndex).toInt();
      
      // Check if the entry ID is different from the last displayed entry ID
      if (entryId != lastEntryId) {
        Serial.println("New message received.");
        isNewMessageReceived = true;
        lastEntryId = entryId; // Update the last entry ID
        isNewMessageDisplayed = false;
        // beepBuzzer();
        return true;
      } else {
        Serial.println("No new message received.");
        return false;
      }
    } else {
      Serial.println("No new message received.");
      isNewMessageReceived = false;
      return false;
    }
  } else {
    Serial.println("Connection failed");
    displayMessage("Wi-Fi Connection failed, no new message received. Reconnecting...");
    return false;
  }
}

// Function to send a message to ThingSpeak
void readMessageFromThingSpeak() {
  WiFiClient client;

  if (client.connect("api.thingspeak.com", 80)) {
    String url = "/channels/" + String(channelID) + "/fields/1/last.json?api_key=" + String(apiKey);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: api.thingspeak.com\r\n" +
                 "Connection: close\r\n\r\n");
    delay(500);
    
    String response = "";
    while (client.available()) {
      response += client.readStringUntil('\n');
    }

    // Parse the JSON response to extract the message
    String message = parseMessage(response);
    displayMessage(message);
    isNewMessageDisplayed = true;
    isNewMessageReceived = false;
  } else {
    Serial.println("Connection failed");
    displayMessage("Wi-Fi Connection failed, unable to read new message. Reconnecting, try after sometime.");
    delay(1000);
  }
}

// Function to parse the JSON response and extract the message
String parseMessage(String response) {
  // Find the start and end of the message
  int startIndex = response.indexOf("field1\":\"") + 9; // Adjust index based on field
  int endIndex = response.indexOf("\"", startIndex);
  return response.substring(startIndex, endIndex);
}

// Function to display a message on the OLED
void displayMessage(String message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message); // Display the message on the OLED
  display.display();
}

// // Function to beep the buzzer
// void beepBuzzer() {
//   digitalWrite(BUZZER_PIN, HIGH); // Turn the buzzer on
//   delay(200);                      // Beep duration
//   digitalWrite(BUZZER_PIN, LOW);  // Turn the buzzer off
//   delay(200);                      // Pause between beeps
// }

// // Function to beep the passive buzzer
// void beepBuzzer() {
//   for (int i = 0; i < 3; i++) { // Beep 3 times
//     tone(BUZZER_PIN, 1000); // Play a tone at 1000 Hz
//     delay(200);             // Beep duration
//     noTone(BUZZER_PIN);     // Stop the tone
//     delay(200);             // Pause between beeps
//   }
// }

void scanRFID(){
  rfid.PCD_Init(); // Initialize the RFID reader

  // Check for a new RFID card
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Read the UID of the scanned card
    byte scannedUID[4];
    for (byte i = 0; i < 4; i++) {
      scannedUID[i] = rfid.uid.uidByte[i];
    }

    // Check if the scanned UID matches the authorized UID
    if (isAuthorized(scannedUID)) {
      readMessageFromThingSpeak(); // Read message from ThingSpeak
    } else {
      displayMessage("Access Denied");
    }
    rfid.PICC_HaltA(); // Halt the PICC
  }
  delay(1000); // Delay to avoid multiple readings
}

// Function to check if the scanned UID is authorized
bool isAuthorized(byte* uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID[i]) {
      return false; // UID does not match
    }
  }
  // beepBuzzer();
  return true; // UID matches
}
