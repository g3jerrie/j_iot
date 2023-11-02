/*
  Two ways of connecting an LED - Sourcing & Sinking
  In ESP8266 build-in & NodeMCU Onboard LEDs are connected in Sinking
  
	@g3jerrie
*/



void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // ESP8266 inbuilt LED Sinking, can also be accessed by D4 pin
  pinMode(D0, OUTPUT); // NodeMCU onboard LED Sinking 
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW); // LED ON when the voltage is LOW due to LED Sinking
  digitalWrite(D0, HIGH); // LED OFF when the voltage is HIGH due to LED Sinking
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH); // LED turns OFF when the voltage is HIGH due to LED Sinking
  digitalWrite(D0, LOW); // LED turns ON when the voltage is LOW due to LED Sinking
  delay(1000);

}
