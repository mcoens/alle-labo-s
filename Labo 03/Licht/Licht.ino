/*
 * Pieter-Jan Christiaens
 * 2ICT5
 * IOT Labo 3 Licht
 */
const byte leds[] = {2,3,4,5};
int waarde;
void setup() {
  for (int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  delay(200);
  waarde = analogRead(0);
  Serial.println(waarde);
  for (int i = 0; i < sizeof(leds); i++) {
    digitalWrite(leds[i], LOW);
  }  
if((waarde >=0) && (waarde <=140)) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } else if ((waarde >=141) && (waarde <= 280)) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } else if ((waarde >=281) && (waarde <= 320)) {
    for (int i = 0; i < 2; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } else if ((waarde >=321) && (waarde <= 460)) {
    for (int i = 0; i < 1; i++) {
      digitalWrite(leds[i], HIGH);
    } 
  } else if ((waarde >= 461) && (waarde <= 700)) {
    for (int i = 0; i < 0; i++) {
      digitalWrite(leds[i], HIGH);
    }
  }
}
