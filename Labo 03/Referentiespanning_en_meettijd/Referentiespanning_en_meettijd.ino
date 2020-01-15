/*
 * Pieter-Jan Christiaens
 * 2ICT5
 * IOT Labo 3 Referentiespanning en meettijd
 */
int waarde;
long t1 = 0;
long t2 = 0;


void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  t1 = micros();  
  waarde = analogRead(0);
  t2 = micros();
  Serial.println(t2 - t1);
  Serial.println(waarde);
}
