#define LED 7
#define K1 2
#define K2 3

void K1ISR() 
{
  digitalWrite(LED, HIGH);
}

void K2ISR() 
{
  digitalWrite(LED, LOW);
}

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(K1), K1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(K2), K2ISR, FALLING);
}

void loop() 
{
}
