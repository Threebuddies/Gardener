/*
  Reads analog sensors on A0 - A5 and prints to serial monitor
  A 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.
  Prints "Hello World!" to the LCD and uses the
  display() and noDisplay() functions to turn on and off
  the display.

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
  http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
  A0 - A5 connected to the sensors
*/

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

// Initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to.
const int registerSelect = 12;
const int enablePin = 11;
const int lcdData4 = 5;
const int lcdData5 = 4;
const int lcdData6 = 3;
const int lcdData7 = 2;
LiquidCrystal lcd(registerSelect, enablePin, lcdData4, lcdData5, lcdData6, lcdData7);

void setup() {
  Serial.begin(9600);
  // lcd
  lcd.begin(16, 2);
  lcd.print("hello, world!");

  // start the Ethernet connection and server
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  //Inialize all the analog pins
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
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data and to limit serial spam
    delay(1);
}
}
