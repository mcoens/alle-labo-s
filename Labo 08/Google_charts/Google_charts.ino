#include <Ethernet2.h>

//Ethernet declarations
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xA8, 0x11 };
EthernetServer server(80);

//Variables
int potPin = 0;


void setup() {
  Serial.begin(9600);
  if(Ethernet.begin(mac)) {
    Serial.print("Server has started on ");
    Serial.println(Ethernet.localIP());
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
        Serial.write(c);

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println();
          client.println("<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>");
          client.println("<script type=\"text/javascript\">");
          client.println("google.charts.load('current', {'packages':['gauge']});");
          client.println("google.charts.setOnLoadCallback(drawChart);");
          client.println("function drawChart() {");
          client.print("var data = google.visualization.arrayToDataTable([['Label', 'Value'],['Potmeter', ");
          client.print(analogRead(potPin));
          client.println("],]);");
          client.println("var options = {width: 600, height: 180,max: 1023,minorTicks: 5};");
          client.println("var chart = new google.visualization.Gauge(document.getElementById('chart_div'));");
          client.println("chart.draw(data, options);");
          client.println("}");
          client.println("</script>");
          client.println("<TITLE> Arduino PotChart </TITLE>");
          client.println("<meta http-equiv=\"refresh\" content=\"1\">");
          client.println("</HEAD>");
          client.println("<BODY style=\" margin: 0 auto;\">");
          client.println("<div id=\"chart_div\" style=\"width: 1600px; height: 480px;\"></div>");
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
