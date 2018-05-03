/*
  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)
  A0 - A5 connected to the sensors
  sensor 1 = external temp
  sensor 2 = external humidity
  sensor 3 = internal temp
  sensor 4 = internal humidity
*/
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);
// set up the lcd
const int registerSelect = 12;
const int enablePin = 11;
const int lcdData4 = 5;
const int lcdData5 = 4;
const int lcdData6 = 3;
const int lcdData7 = 2;
LiquidCrystal lcd(registerSelect, enablePin, lcdData4, lcdData5, lcdData6, lcdData7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  // start up server
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  //Inialize all the analog sensor pins

  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
  // Prints all the sensor values to serial
  Serial.println("Sensor 0 value = " + sensorValue0);
  Serial.println("Sensor 1 value = " + sensorValue1);
  Serial.println("Sensor 2 value = " + sensorValue2);
  Serial.println("Sensor 3 value = " + sensorValue3);
  Serial.println("Sensor 4 value = " + sensorValue4);
  Serial.println("Sensor 5 value = " + sensorValue5);

  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          int sensorValue0 = analogRead(A0);
          int sensorValue1 = analogRead(A1);
          int sensorValue2 = analogRead(A2);
          int sensorValue3 = analogRead(A3);
          int sensorValue4 = analogRead(A4);
          int sensorValue5 = analogRead(A5);
          // Prints all the sensor values to server
          client.println("Sensor 0 value = " + sensorValue0);
          client.println("Sensor 1 value = " + sensorValue1);
          client.println("Sensor 2 value = " + sensorValue2);
          client.println("Sensor 3 value = " + sensorValue3);
          client.println("Sensor 4 value = " + sensorValue4);
          client.println("Sensor 5 value = " + sensorValue5);
          client.println("</html>");
          break;
        }
        //checks to see if the current line is blank
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    // limit output spam
    delay(1);
  }
}
