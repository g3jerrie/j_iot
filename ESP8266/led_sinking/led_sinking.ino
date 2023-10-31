/*
  ESP8266 build-in & E0 LED Sinking
  Two ways of connecting an LED - Sourcing & Sinking
  
	@g3jerrie
*/



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW); //LED ON when the voltage is LOW due to LED Sinking
  digitalWrite(D0, HIGH); // LED remains OFF
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH); //LED turns OFF when the voltage is HIGH due to LED Sinking
  digitalWrite(D0, LOW); // LED turns ON
  delay(1000);

}
