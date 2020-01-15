#include <Ethernet2.h>
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xA8, 0x10 };

EthernetServer server(23);

//Variables
bool printMenu = true;
char keuze;
String keuzeC;
int keuzeLed;
bool keuzeStand;
bool wachten = false;
const byte leds[] = {2,3,4,5};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  if(Ethernet.begin(mac)) {
    Serial.print("Server has started on ");
    Serial.println(Ethernet.localIP());
  }
}

void loop() {
  EthernetClient client = server.available();

  if(client) {
    while(client.connected()) {
      if(printMenu) {
        client.println("Toets de letter in naar uw keuze:");
        client.println("a.   alle LED's aan");
        client.println("b.   alle LED's uit");
        client.println("c.   individuele LED aansturen");
        client.println("q.   verbinding verbreken.");
        
        printMenu = false;
      }

      if(client.available() > 0) {
        keuze = client.read();
        switch (keuze) {
          case 'a':
            client.println("a.    Alle leds aan");
            for (int i = 0; i < sizeof(leds); i++) {
              digitalWrite(leds[i], HIGH);
            }
            break;
          case 'b':
            client.println("b.    Alle leds uit");
            for (int i = 0; i < sizeof(leds); i++) {
              digitalWrite(leds[i], LOW);
            }
            break;
          case 'c':
            wachten = true;
            while(wachten) {
              if (client.available() > 0) {
                keuzeC = client.readString();
                keuzeLed = keuzeC.charAt(0);
                if (keuzeC.charAt(1) == 'A') {
                  keuzeStand = true;
                  aansturen(keuzeLed, true);
                } else if (keuzeC.charAt(1) == 'U') {
                  keuzeStand = false;
                  aansturen(keuzeLed, false);
                } else {
                  client.println("Geen geldige keuze");
                } 
                wachten = false;       
              }
            }
            break;
          case 'q':
            
            client.println("Disconnecting...");
            client.stop();
            break;
        }
      }
    }
  }
}

void aansturen(int led, bool aanstuurKeuze) {
  switch(led) {
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
