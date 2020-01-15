#define LED1 7
#define LED2 8
#define K1 2
#define K2 3

boolean inter = true;

void K1ISR() 
{
  digitalWrite(LED1, !digitalRead(LED1));
}

void K2ISR() 
{
  if (!inter) 
  {
    EIFR = 0x01;
    attachInterrupt(digitalPinToInterrupt(K1), K1ISR, FALLING);
    digitalWrite(LED2, LOW);
    inter = true;
  } 
  else 
  {
    detachInterrupt(digitalPinToInterrupt(K1));
    digitalWrite(LED2, HIGH);
    inter = false;
  }
}



void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(K1), K1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(K2), K2ISR, FALLING);
  Serial.begin(9600);
}

void loop() 
{
}
