
#include <Ethernet2.h>

//Ethernet declarations
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xA8, 0x11 };
EthernetServer server(80);

//Variables
int potMeter = 0;


void setup() {
  Serial.begin(9600);
  if(Ethernet.begin(mac)) {
    Serial.print("Server has started on ");
    Serial.println(Ethernet.localIP());
  }
}

void loop() {
  potMeter = analogRead(0);


  //Ethernet server
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
          client.println("");
          client.println("<BODY>");
          client.println("<H1 style=\"color:blue; font-family:courier new;\"> Waarde van de potentiometer </H1>");
          
          //Progress bar
          client.print("<progress value=\"");
          client.print(potMeter);
          client.print("\" max=\"1023\"></progress>");
          
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
