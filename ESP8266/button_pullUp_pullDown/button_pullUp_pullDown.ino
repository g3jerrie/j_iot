/*
  Two Methods of connecting an Button - Pull Up & Pull Down
  Configured ESP8266 NodeMCU digital pin out to use onboard pull up resistor for pull up button.
  for pull down botton used external 10KΩ resistor
  
	@g3jerrie
*/

// Define the pins for the Buttons and LEDs
#define BUTTON_PULL_UP_PIN D5 // connected a button in pull up method
#define BUTTON_PULL_DOWN_PIN D6 // connected a button in pull down method
#define LED_EXTERNAL_SINKING_PIN D1 // connected external LED in Sinking
#define LED_EXTERNAL_SOURCING_PIN D2 // connected external LED in Sourcing

// Create variable to access button state
int pullUpButtonState, pullDownButtonState;


void setup() {
  // Set the pins as outputs
  pinMode(BUTTON_PULL_UP_PIN, INPUT_PULLUP); // using internal pull up resistor
  pinMode(BUTTON_PULL_DOWN_PIN, INPUT); // connected to external pull down resistor
  pinMode(LED_EXTERNAL_SINKING_PIN, OUTPUT);
  pinMode(LED_EXTERNAL_SOURCING_PIN, OUTPUT);
}

void loop() {
  // capture buttons state
  pullUpButtonState = digitalRead(D5);
  pullDownButtonState = digitalRead(D6);

  if(pullUpButtonState == LOW) // when pull up button is pressed
  {
    digitalWrite(LED_EXTERNAL_SINKING_PIN, LOW); // sinking LED On if button pressed
  }
  else
  {
    digitalWrite(LED_EXTERNAL_SINKING_PIN, HIGH); // sinking LED remains Off
  }


  if(pullDownButtonState == HIGH) // when pull down button is pressed
  {
    digitalWrite(LED_EXTERNAL_SOURCING_PIN, HIGH); // sourcing LED On if button pressed
  }
  else
  {
    digitalWrite(LED_EXTERNAL_SOURCING_PIN, LOW); // sourcing LED remains Off
  }
 
}
