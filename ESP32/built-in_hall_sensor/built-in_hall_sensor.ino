/*
  ESP32 access build-in Hall sensor
  
	@g3jerrie
*/

int hallSensorReading;

void setup() {

  Serial.begin(115200);

}

void loop() {
  hallSensorReading = hallRead();
  Serial.printf("Hall Sensor Value is: %i\n", hallSensorReading);
  delay(3600);
}