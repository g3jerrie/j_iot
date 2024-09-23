#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3; // Reset pin
constexpr uint8_t SS_PIN = D4;  // Slave select pin

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
    Serial.begin(9600); // Initialize serial communications
    SPI.begin();        // Initialize SPI bus
    rfid.PCD_Init();    // Initialize MFRC522
    Serial.println("Scan a card...");
}

void loop() {
    // Look for a new card
    if (!rfid.PICC_IsNewCardPresent()) return;
    if (rfid.PICC_ReadCardSerial()) {
        Serial.print("Card UID: ");
        for (byte i = 0; i < rfid.uid.size; i++) {
            Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
        rfid.PICC_HaltA(); // Halt PICC
        rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    }
}