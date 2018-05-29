// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN1 2     // digital pin for inside sensor
#define DHTPIN2 3     // digital pin for outside sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht1(DHTPIN1, DHTTYPE); // initialize inside sensor
DHT dht2(DHTPIN2, DHTTYPE); // initialize outside sensor

void setup() {
  pinMode(7, OUTPUT); // Initialize the fan pin
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht1.begin();
  dht2.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = dht1.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println("Failed to read from 1st DHT sensor!");
    return;
  }

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  float f2 = dht2.readTemperature(true);
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from 2nd DHT sensor!");
    return;
  }

  if (h1 > 85) {   // if humidity is above 85% a fan will turn on
    digitalWrite(7, HIGH);
    } 
    else {
    digitalWrite(7, LOW);
  }
  
  Serial.print("Inside:  ");
  Serial.print("Humidity: ");
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t1);
  Serial.print(" *C ");
  Serial.print(f1);
  Serial.print(" *F\t");
  Serial.println();

  Serial.print("Outside: ");
  Serial.print("Humidity: ");
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t2);
  Serial.print(" *C ");
  Serial.print(f2);
  Serial.print(" *F\t");
  Serial.println();
  Serial.println();
  delay(10000);       // repeat scan every 10 seconds
}
