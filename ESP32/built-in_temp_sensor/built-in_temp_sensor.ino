/*
  ESP32 access build-in temperature sensor

  code enhanced with help of Bing Chat with GPT-4
  
	@g3jerrie
*/


//

extern "C" // Extern C is used when we are using a funtion written in "C" language in a C++ code.
{

  uint8_t temprature_sens_read(); // This function is written in C language
}

uint8_t temprature_sens_read(); //Declaring again in C++ section

void setup() {
  Serial.begin(115200); //Begining the Serial Monitor at the provided Baud rate 
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// Define a constant variable for the conversion factor
const float F_TO_C = 1.8;

// Define a function to convert and print the temperature
void printTemp(float tempF) {
  // Convert Fahrenheit to Celsius
  float tempC = (tempF - 32) / F_TO_C;
  // Create a buffer to store the formatted output
  char buffer[93];
  // Use sprintf() to format the output as a single string
  sprintf(buffer, "Temperature in degree Fahrenheit: %.2f F\nTemperature in degree Celsius: %.2f C\n", tempF, tempC);
  // Print the buffer with one Serial.print() call
  Serial.print(buffer);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  // Read the temperature sensor
  float temp = temprature_sens_read();
  // Call the function to print the temperature
  printTemp(temp);
  digitalWrite(LED_BUILTIN, LOW);
  // Wait for 5 seconds
  delay(5000);
}
