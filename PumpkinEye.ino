#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

long randNumber;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address

  randomSeed(analogRead(0));
}

static const uint8_t PROGMEM
  eyeball[] = {
    B00111100,
    B01111110,
    B11111111,
    B11100111,
    B11100111,
    B11111111,
    B01111110,
    B00111100
  },
  blank[] {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  eyeDownRight1[] {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11110011,
    B11110011,
    B01111110,
    B00111100
  },
  eyeDownRight2[] {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111001,
    B01111000,
    B00111100
  },  
  blink1[] = {
    B00000000,
    B01111110,
    B11111111,
    B11100111,
    B11100111,
    B11111111,
    B01111110,
    B00111100
  },
  blink2[] = {
    B00000000,
    B00000000,
    B11111111,
    B11100111,
    B11100111,
    B11111111,
    B01111110,
    B00111100
  },
  blink3[] = {
    B00000000,
    B00000000,
    B00000000,
    B11100111,
    B11100111,
    B11111111,
    B01111110,
    B00111100
  },
  blink4[] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11100111,
    B11111111,
    B01111110,
    B00111100
  },
  blink5[] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B01111110,
    B00111100
  },
  blink6[] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01111110,
    B00111100
  },
  blink7[] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00111100
  },
  blink8[] = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }          
  ;


void loop() {

  randNumber = random(300);
  Serial.println(randNumber);  

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(5000);

  lookDownRight();

  delay(2500);
  blink();

  delay(2500);

  snooze();  
  delay(2500);
}

void lookDownRight() {

  matrix.clear();
  matrix.drawBitmap(0,0, eyeDownRight1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);

  matrix.clear();
  matrix.drawBitmap(0,0, eyeDownRight2, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(750);
  
  matrix.clear();
  matrix.drawBitmap(0,0, eyeDownRight1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);  
}

void blink() {

  matrix.clear();
  matrix.drawBitmap(0,0, blink1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink2, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink3, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink4, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink5, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink6, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink7, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink8, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink8, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink7, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink6, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink5, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink4, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);
  
  matrix.clear();
  matrix.drawBitmap(0,0, blink3, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink2, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);

  matrix.clear();
  matrix.drawBitmap(0,0, blink1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(25);      

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);  
}

void snooze() {
  matrix.setTextSize(1);
  matrix.setTextWrap(false); 
  matrix.setTextColor(LED_ON);
  for (int8_t x=0; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("ZZZZZZZZZZZZZZZZ");
    matrix.writeDisplay();
    delay(100);
  }

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(20);    
}









