
/*
 * Pieter-Jan Christiaens
 * 2ICT5
 * IOT Labo 4 Aangepaste_Karakters
 */
 #include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);


byte karakter0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte karakter1[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};

byte karakter2[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};

byte karakter3[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};

byte karakter4[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};

byte karakter5[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  lcd.begin(16,2);
  lcd.createChar(0, karakter0);
  lcd.createChar(1, karakter1);
  lcd.createChar(2, karakter2);
  lcd.createChar(3, karakter3);
  lcd.createChar(4, karakter4);
  lcd.createChar(5, karakter5);
  lcd.clear();
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));

}

void loop() {
}
