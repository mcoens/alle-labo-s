#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

String tekst = "Wie is de beste club van Gent?";
String  flashTekst = "Moeder KILA";

void setup() {
  lcd.begin(16,2);
}

void loop() {
  lcd.print(tekst);
  delay(500);
  for (int i = 0; i < tekst.length() - 16; i++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
  for (int j = 0; j < 3; j++) {
    lcd.print(flashTekst);
    delay(250);
    lcd.clear();
    delay(250);
  }
}
