String ingave;
int nummers;
const byte leds[] = {3,4,5,6};
bool staat = true;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    ingave = Serial.readString();
    Serial.println(ingave);
    if (true) {
      nummers = ingave.toInt();
      Serial.println(nummers);
      for (int i = 0; i < sizeof(leds); i++) {
          digitalWrite(leds[i], LOW);
        }
      if ((nummers >= 0) && (nummers <= 9)) {
        digitalWrite(leds[0], HIGH);
      } else if ((nummers >= 10) && (nummers <= 99)) {
        digitalWrite(leds[1], HIGH);
      } else if ((nummers >= 100) && (nummers <= 999)) {
        digitalWrite(leds[2], HIGH);
      } else if ((nummers >= 1000) && (nummers <= 9999)) {
        digitalWrite(leds[3], HIGH);
      } else if (nummers > 9999) {
        for (int i = 0; i < 6; i++) {
          for (int i = 0; i < sizeof(leds); i++) {
            digitalWrite(leds[i], staat);
          }
          staat = !staat;
          delay(500);
        }
      } else {
        Serial.println("Geen geldige ingave");
      }
    } else {
      Serial.println("Geef een geldig getal in");
    }
  }
}
