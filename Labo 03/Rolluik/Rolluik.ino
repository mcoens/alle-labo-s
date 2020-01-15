/*
 * Pieter-Jan Christiaens
 * 2ICT5
 * IOT Labo 3 Rolluik
 */
#define ROLLUIK 2
#define VERLICHTING 3
int waarde;
int MAX = 700;

void setup() {
  pinMode(ROLLUIK, OUTPUT);
  pinMode(VERLICHTING, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  waarde = analogRead(0);
  Serial.println(waarde);
  delay(250);
  
  if(waarde >= (MAX * 0.85)) {
    digitalWrite(VERLICHTING, LOW);
  } else if (waarde <= (MAX * 0.75)) {
    digitalWrite(VERLICHTING, HIGH);
  }

  if(waarde >= (MAX * 0.25)) {
    digitalWrite(ROLLUIK, LOW); 
  } else if (waarde <= (MAX * 0.15)) {
    digitalWrite(ROLLUIK, HIGH);
  }
}
