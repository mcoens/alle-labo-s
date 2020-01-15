/*
 * Pieter-Jan Christiaens
 * 2ICT5
 * IOT Labo 4 Rotary_encoder
 */
#include <LiquidCrystal.h>
#define inputA 6
#define inputB 7

LiquidCrystal lcd(12,11,5,4,3,2);

int aState;
int aLastState; 
int counter = 0; 


//Maak de karakters aan
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
  Serial.begin(9600);
  lcd.createChar(0, karakter0);
  lcd.createChar(1, karakter1);
  lcd.createChar(2, karakter2);
  lcd.createChar(3, karakter3);
  lcd.createChar(4, karakter4);
  lcd.createChar(5, karakter5);
  lcd.clear();
  pinMode (inputA,INPUT_PULLUP);
  pinMode (inputB,INPUT_PULLUP);
  aLastState = digitalRead(inputA); 
}

void loop() { 
  Serial.println(counter);
   aState = digitalRead(inputA);
   
   if (aState != aLastState){     
     
     if (digitalRead(inputB) != aState) { 
       counter++;
       if (counter > 100) counter = 100;
     } else {
       counter--;
       if (counter < 0) counter = 0;
     }
     lcd.clear();
     for(int i = 0; i < ((counter / 1.25) / 5) ; i++) {
        lcd.write(byte(5));
     }
     int op80 = counter / 1.25;
     int over = op80 % 5;
     lcd.write(byte(over));
     lcd.setCursor(0,1);
     lcd.print(counter);
     lcd.print("%");
   } 
   aLastState = aState; 
}
