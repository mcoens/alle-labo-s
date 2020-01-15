#include <SoftwareSerial.h>

//bluetooth
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial has started");
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("D");
  delay(100);
  while (bluetooth.available()) {
    Serial.print((char)bluetooth.read());
  }
  bluetooth.println("---");
  bluetooth.print("stuur a om de led aan te zetten en b om de led uit te zetten");
}

void loop() {
  while (bluetooth.available()) {
    char karakter = (char)bluetooth.read();
    Serial.print(karakter);
    if (karakter == 'a') {
      digitalWrite(4, HIGH);
    } 
    if (karakter == 'b') {
      digitalWrite(4, LOW);
    }
  }
  while (Serial.available()) {
    bluetooth.print((char)Serial.read());
  }
}
