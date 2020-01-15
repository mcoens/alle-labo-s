bool staat = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  digitalWrite(7, !staat);
  digitalWrite(8, staat);
  delay(20);
  staat = !staat;
}
