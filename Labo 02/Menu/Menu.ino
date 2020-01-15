// Declaratie variabelen
String keuze;
String keuzeC;
int keuzeLed;
bool keuzeStand;
bool wachten = false;
const byte leds[] = {3,4,5,6};

void setup() 
{
  for (int i = 0; i < sizeof(leds); i++) 
  {
    pinMode(leds[i], OUTPUT);
  }
  
  Serial.begin(115200);
  Serial.println("\nToets de letter in naar uw keuze:\n a.   alle LED's aan\n b.   alle LED's uit\n c.   individuele LED aansturen\n");
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    keuze = Serial.read();
    if (keuze.equals("99"))
    {
      Serial.println("geef het nummer van de LED gevolgd door A (aan) of U (uit), bv. 3A:");
      wachten = true;
      while(wachten) 
      {
        if (Serial.available() > 0)
        {
          keuzeC = Serial.readString();
          keuzeLed = keuzeC.charAt(0);
          if (keuzeC.charAt(1) == 'A') 
          {
            keuzeStand = true;
            aansturen(keuzeLed, true);
          } 
          else if (keuzeC.charAt(1) == 'U')
          {
            keuzeStand = false;
            aansturen(keuzeLed, false);
          } 
          else 
          {
            Serial.println("Geen geldige keuze");
          } 
          wachten = false;
        }
      }
    }
    else
    {

      if (keuze.equals("97"))
      {
        for (int i = 0; i < sizeof(leds); i++)
        {
          digitalWrite(leds[i], HIGH);
        } 
      } 
      else if (keuze.equals("98")) 
      {
        for (int i = 0; i < sizeof(leds); i++)
        {
          digitalWrite(leds[i], LOW);
        } 
      } 
      else 
      {
        Serial.println("Geen geldige keuze");
      }
    }
    
  }
}

void aansturen(int led, bool aanstuurKeuze) 
{
  switch(led)
  {
          case 49:
            digitalWrite(leds[0], aanstuurKeuze);
            break;
          case 50:
            digitalWrite(leds[1], aanstuurKeuze);
            break;
          case 51:
            digitalWrite(leds[2], aanstuurKeuze);
            break;
          case 52:
            digitalWrite(leds[3], aanstuurKeuze);
            break;
          default:
            Serial.println("Geen geldige keuze 3");
  } 
}
