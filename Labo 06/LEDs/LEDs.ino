#include <Ethernet2.h>
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xA8, 0x10 };

EthernetServer server(80);

//Variables
bool LED1Stand = false;
bool LED2Stand = false;

#define K1 2
#define K2 3

#define LED1 4
#define LED2 5

void K1ISR() {
  digitalWrite(LED1, !LED1Stand);
  LED1Stand = !LED1Stand;
}

void K2ISR() {
  digitalWrite(LED2, !LED2Stand);
  LED2Stand = !LED2Stand;
}

void setup() {
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(K1), K1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(K2), K2ISR, FALLING);
  
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  if(Ethernet.begin(mac)) {
    Serial.print("Server has started on ");
    Serial.println(Ethernet.localIP());
  }
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New Client");
    //initPage(client);
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE> Arduino LedWeb </TITLE>");
          client.println("<meta http-equiv=\"refresh\" content=\"1\">");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1 style=\"color:blue; font-family:courier new;\"> LED besturing </H1>");
          client.println("<div style=\"border-style: dotted; border-color: Cyan; margin: 10px; padding: 20px; width: 120px; \">");
          client.print("LED1: ");
          client.println(LED1Stand);
          client.print("<br>LED2: ");
          client.println(LED2Stand);
          client.println("</div>");
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1);
          client.stop();
          Serial.println("Client disconnected");
        }
      }
    }
  }  
}
