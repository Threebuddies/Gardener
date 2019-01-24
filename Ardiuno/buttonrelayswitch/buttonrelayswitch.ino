int button1 = 2;
int button2 = 3;
int relay1 = A0;
int relay2 = A1;

int state1 = HIGH;
int reading1;
int previous1 = LOW;

int state2 = HIGH;
int reading2;
int previous2 = LOW;

long time1 = 0;
long debounce1 = 200;

long time2 = 0;
long debounce2 = 200;

void setup()
{
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop()
{
  reading1 = digitalRead(button1);
  if (reading1 == HIGH && previous1 == LOW && millis() - time1 > debounce1) {
    if (state1 == HIGH)
      state1 = LOW;
    else
      state1 = HIGH;
    time1 = millis();    
  }
  digitalWrite(relay1, state1);
  previous1 = reading1;

//next relay
  reading2 = digitalRead(button2);
  if (reading2 == HIGH && previous2 == LOW && millis() - time2 > debounce2) {
    if (state2 == HIGH)
      state2 = LOW;
    else
      state2 = HIGH;
    time2 = millis();    
  }
  digitalWrite(relay2, state2);
  previous2 = reading2;
}
