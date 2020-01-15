#define K2 3

int teller = 0;
long tijd;
const byte DEBOUNCE = 100;

boolean flag = true;

void K2ISR() 
{
  if ((millis() - tijd) > DEBOUNCE) 
  {
    teller++;
    flag = true;
    tijd = millis();
  } 
}



void setup() 
{
  pinMode(K2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(K2), K2ISR, RISING);
  Serial.begin(9600);
}

void loop()
{
  if (flag) 
  {
    Serial.println(teller);
    flag = false;
  }
}
