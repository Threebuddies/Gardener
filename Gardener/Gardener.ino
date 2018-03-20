/*
  Reads on A0 and prints to serial monitor
  Attach to +5, gnd, A0
*/
void setup() {
  Serial.begin(9600);
}

void loop() {
  //Anitialize all the analog pins
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
  
  // Prints all the sensor values to serial
  Serial.println("Sensor 0 " + sensorValue0);
  Serial.println("Sensor 1 " + sensorValue1);
  Serial.println("Sensor 2 " + sensorValue2);
  Serial.println("Sensor 3 " + sensorValue3);
  Serial.println("Sensor 4 " + sensorValue4);
  Serial.println("Sensor 5 " + sensorValue5);
  delay(2);       
}
