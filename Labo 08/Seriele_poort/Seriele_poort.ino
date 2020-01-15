#include <Ethernet2.h>

byte LED[] = {2, 3, 4, 5};
int nrLED;
bool statusLED;
String inlezen;

//Ethernet declarations
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xA8, 0x11 };
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < sizeof(LED); i++) {
    pinMode(LED[i], OUTPUT);
  }
  if(Ethernet.begin(mac)) {
    Serial.print("Server has started on ");
    Serial.println(Ethernet.localIP());
    delay(1000);
    server.begin();
  }
}

void loop() {
  
  //Ethernet server
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New Client");
    //initPage(client);
    while (client.connected()) {
      if (client.available()) { 
        char c = client.read();
        if (inlezen.length() < 100) {
          inlezen += c;
        }
        //Serial.println(inlezen);
        if(inlezen.substring(6,10) == "LED=") {
          nrLED = inlezen.charAt(10) + 0x31;
          statusLED = bool(inlezen.charAt(14) + 0x31);
          Serial.println(nrLED); 
          Serial.println(statusLED);
          digitalWrite(LED[nrLED], statusLED);
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE> Arduino LedWeb </TITLE>");
          //client.println("<meta http-equiv=\"refresh\" content=\"1\">");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1 style=\"color:blue; font-family:courier new;\"> Say something I'm giving up on you </H1>");
          
          for (int i = 0; i < sizeof(LED); i++) {
            client.print("<input type=checkbox onclick=location.href=\"/?LED=");
            client.print(i+1);
            client.print("&S=");
            client.print(!digitalRead(LED[i]));
            client.print("\" /> LED");
            client.print(i);
            client.print("<br></input>");
          }
          
          client.println("</div>");
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1);
          client.stop();
          inlezen="";
          Serial.println("Client disconnected");
        }
      }
    }
  }
}
