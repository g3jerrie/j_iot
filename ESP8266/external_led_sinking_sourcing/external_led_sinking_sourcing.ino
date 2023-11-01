/*
  Two ways of connecting an LED - Sourcing & Sinking
  In ESP8266 build-in & NodeMCU E0 LED are connected in Sinking
  
	@g3jerrie
*/

// Define the pins for the LEDs
//#define LED_BUILTIN_PIN LED_BUILTIN // ESP8266 inbuilt LED Sinking
//#define LED_ONBOARD_PIN D0 // NodeMCU onboard LED Sinking 
#define LED_EXTERNAL_SINKING_PIN D1 // connected external LED in Sinking
#define LED_EXTERNAL_SOURCING_PIN D2 // connected external LED in Sourcing

// Define the LED states
const int LED_ON = LOW; // LED ON when the voltage is LOW due to LED Sinking
const int LED_OFF = HIGH; // LED OFF when the voltage is HIGH due to LED Sinking

void setup() {
  // Set the pins as outputs
  //pinMode(LED_BUILTIN_PIN, OUTPUT);
  //pinMode(LED_ONBOARD_PIN, OUTPUT);
  pinMode(LED_EXTERNAL_SINKING_PIN, OUTPUT);
  pinMode(LED_EXTERNAL_SOURCING_PIN, OUTPUT);
}

void loop() {
  // Toggle the LEDs in a sequence

/*  for (int i = 0; i < 4; i++) {
    // Turn on the i-th LED and turn off the others
    digitalWrite(LED_BUILTIN_PIN, i == 0 ? LED_ON : LED_OFF);
    digitalWrite(LED_ONBOARD_PIN, i == 1 ? LED_ON : LED_OFF);
    digitalWrite(LED_EXTERNAL_SINKING_PIN, i == 2 ? LED_ON : LED_OFF); 
    digitalWrite(LED_EXTERNAL_SOURCING_PIN, i == 3 ? !LED_ON : !LED_OFF); // Note the inversion for LED Sourcing
    delay(1000); // Wait for a second
  }
*/

  for (int i = 0; i < 2; i++) {
    // Turn on the i-th LED and turn off the others
    digitalWrite(LED_EXTERNAL_SINKING_PIN, i==0 ? LED_ON : LED_OFF);
    digitalWrite(LED_EXTERNAL_SOURCING_PIN, i == 1 ? !LED_ON : !LED_OFF); // Note the inversion for LED Sourcing
    delay(1000); // Wait for a second
  }
}
