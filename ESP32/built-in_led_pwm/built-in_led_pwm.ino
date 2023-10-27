/*
  ESP32 build-in LED pulse width modulation
  
	@g3jerrie
*/

int freq = 5000; // ON OFF timing of cycle
int ledchnl = 0;   // Choose one of the 16 channels available
int resol = 8;  // we can choose upto 16 bit resol

void setup() {

  ledcSetup(ledchnl, freq, resol); // setup part for PWM
  ledcAttachPin(2, ledchnl); // attaching channel to LED pin

}

void loop() {

  //as it is 8 bit the values will goto 255 (2^8 - 1)
  for (int i = 0; i <= 255; i++) // Increasing Brightness
  {
    ledcWrite(ledchnl, i);

    delay(5);
  }

  for (int i = 255; i >= 0; i--) // Decreasing Brightness
  {
    ledcWrite(ledchnl, i);

    delay(5);
  }
  delay (3600); // delay between each loop
}