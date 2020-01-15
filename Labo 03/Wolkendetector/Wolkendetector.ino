byte metingen[1500];
int waarde;
int teller = 0;

byte mini = 255;
byte maxi = 0;
byte gemi = 0;
long tot = 0;

#define K2 2
void K1ISR() {
  Serial.print("Aantal     :");
  Serial.println(teller + 1);
  Serial.print("Minimum    :");
  Serial.println(minimum());
  Serial.print("Maximum    :");
  Serial.println(maximum());
  Serial.print("Gemiddelde :");
  Serial.println(gemiddelde());
  if (gemiddelde() > 85) {
    Serial.println("Bewolkt");
  } else if (gemiddelde() > 85 && gemiddelde() < 168) {
    Serial.println("Wisselend bewolkt");
  } else if (gemiddelde() > 168) {
    Serial.println("Helder");
  }
}

#define K1 2

void setup() {
  Serial.begin(9600);
  pinMode(K2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(K2), K1ISR, FALLING);
}

void loop() {
  waarde = analogRead(0);
  if (teller < 1500) {
    metingen[teller] = waarde * 0.36;
  } else {
    for (int i = 0; i < 1500; i++) {
      if (i != 1499) {
        metingen[i] = metingen[i + 1];
      }
      metingen[1499] = waarde * 0.36;
    }
  }


  teller++;
  delay(500);
}

int minimum() {
  for (int i = 0; i < 1500; i++) {
    if (metingen[i] < mini) {
      mini = metingen[i];
    }
  }
  return mini;
}

int maximum() {
  for (int i = 0; i < 1500; i++) {
    if (metingen[i] > maxi) {
      maxi = metingen[i];
    }
  }
  return maxi;
}

int gemiddelde() {
  for (int i = 0; i < 1500; i++) {
    if (metingen[i] > maxi) {
      tot = metingen[i];
    }
  }

  gemi = tot/teller;
  return gemi;
}
