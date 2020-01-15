#include <SPI.h>
#include <Ethernet2.h>
#include <PubSubClient.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xA8, 0xA9 };
IPAddress server(10, 129, 18, 32);


void callback(char* topic, byte* payload, unsigned int length) {
  String tempStr = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    tempStr += (char)payload[i];
  }
  
  if ((String)topic == "labo/licht/lamp1") digitalWrite(3, (char)payload[0] - 0x30);
  else if ((String)topic == "labo/licht/lamp2") digitalWrite(4, (char)payload[0] - 0x30);
  
  if ((String) topic == "labo/klimaat/temp") {
    float temp = tempStr.toFloat();
    Serial.println("");
    Serial.print("De temperatuur in het labo is : ");
    Serial.print(temp, 1);
    Serial.println("°C");
  }
  Serial.println();
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("RasPI3")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("labo/dantedebruyne/test","hello world");
      // ... and resubscribe
      client.subscribe("labo/#");
      
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac);
  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
