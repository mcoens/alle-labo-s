#include <SoftwareSerial.h>

//bluetooth
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
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
}

void loop() {
}
