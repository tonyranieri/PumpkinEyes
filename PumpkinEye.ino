#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

long randNumber;

int const defaultPupilX = 3,
          defaultPupilY = 3;
int pupilX = 3,
    pupilY = 3;

const int 
    UP = 1,
    UP_RIGHT = 2,
    RIGHT = 3,
    DOWN_RIGHT = 4,
    DOWN = 5,
    DOWN_LEFT = 6,
    LEFT = 7,
    UP_LEFT = 8,
    CENTER = 9;

void movePupilToLocation(int destination) {
    drawEye();
    delay(20);

    int targetX = getPupilTargetX(destination),
        targetY = getPupilTargetY(destination);

    for(; pupilX != targetX, pupilY != targetY; updatePupilX(targetX), updatePupilY(targetY)) {
      Serial.println(pupilX);
        drawEye();
        delay(50);
    }

    delay(2000);

    resetPupilLocation();    
}

int getPupilTargetX(int destination) {
    switch(destination) {
        case UP:
        case CENTER:
        case DOWN:
            return 3;
            break;

        case UP_LEFT:
        case LEFT:
        case DOWN_LEFT:        
            return 0;
            break;
        
        case UP_RIGHT:
        case RIGHT:    
        case DOWN_RIGHT:
            return 6;
            break;
    }
}

int getPupilTargetY(int destination) {
    switch(destination) {
        case UP_LEFT:
        case UP:        
        case UP_RIGHT:
            return 0;
            break;

        case LEFT:
        case CENTER:
        case RIGHT:    
            return 3;
            break;

        case DOWN_LEFT:
        case DOWN:                
        case DOWN_RIGHT:
            return 6;
            break;
    }
}

void updatePupilX(int target) {
    if(pupilX < target) {
        pupilX++;
    } else if (pupilX > target) {
        pupilX--;
    }
}

void updatePupilY(int target) {
    if(pupilY < target) {
        pupilY++;
    } else if (pupilY > target) {
        pupilY--;
    }
}

void drawEye() {
    matrix.clear();
    drawBaseEyeBall();
    drawPupil();
    matrix.writeDisplay();
}

void drawPupil() {
    matrix.fillRect(pupilX, pupilY, 2, 2, LED_OFF);
}

void resetPupilLocation() {
    pupilX = defaultPupilX;
    pupilY = defaultPupilY;
}

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address

  randomSeed(analogRead(0));
}

static const uint8_t PROGMEM
  baseEyeball[] = {
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
  },
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
  }
  ;


void loop() {

  drawDefaultEye();

  int wait = random(10,10000);
  delay(wait);

  movePupilToLocation(UP_RIGHT);

//   Serial.println(getWeightedRandomNumber());

//   blink();
  
//  lookDown();



  //lookDownRight();

  //pulsateEye();

  // matrix.setBrightness(1);
  // blink();
  // delay(2500);

  //snooze();  
  //delay(2500);
}

int getWeightedRandomNumber() {
  
    int weightedChoices[] = { 75, 50, 25 };
    int sumOfWeight = 150;
    int choiceCount = 3;
        
    for(int i = 0; i < choiceCount; i++) {
       sumOfWeight += weightedChoices[i];
    }
    
    int rnd = random(sumOfWeight);
    
    for(int i = 0; i < choiceCount; i++) {
      if(rnd < weightedChoices[i])
        return i;
      rnd -= weightedChoices[i];
    }
}

void lookDown() {
    matrix.clear();
    drawDefaultEye();
    matrix.writeDisplay();

    delay(200);

    for(int i = 4; i < 7; i++){
        drawBaseEyeBall();
        matrix.fillRect(i, 3, 2, 2, LED_OFF);
        matrix.writeDisplay();
        delay(20);
    }
    delay(2000);

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

void snooze() {
  matrix.clear();
  matrix.drawBitmap(0,0, blank, 8, 8, LED_ON);
  matrix.writeDisplay();

  matrix.setTextSize(1);
  matrix.setTextWrap(false); 
  matrix.setTextColor(LED_ON);

  delay(2500);    

  for (int8_t x=0; x>=-60; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("ZZZZZZZZZZZZZZZZ");
    matrix.writeDisplay();
    delay(100);
  }

  matrix.clear();
  matrix.drawBitmap(0,0, blank, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);    

  matrix.clear();
  matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void blink() {
    int blinkSpeed = getRandomBlinkSpeed();
    closeEyeLid(blinkSpeed);
    openEyeLid(blinkSpeed);
}

int getRandomBlinkSpeed() {
    return random(10, 45);
}

void closeEyeLid(int blinkSpeed) {
    for(int lidHeight = 0; lidHeight < 9; lidHeight++) {
        drawEyeWithLid(lidHeight);
        delay(blinkSpeed);
    }
}

void openEyeLid(int blinkSpeed) {
    for(int lidHeight = 9; lidHeight >= 0; lidHeight--) {
        drawEyeWithLid(lidHeight);
        delay(blinkSpeed);
    }
}

void drawEyeWithLid(int lidHeight) {
    drawBaseEyeBall();
    drawCenteredPupil();
    matrix.fillRect(-1,-1, lidHeight, 9, LED_OFF);
    matrix.writeDisplay();
}

void drawDefaultEye() {
  drawBaseEyeBall();
  drawCenteredPupil();
  matrix.writeDisplay();
}

void drawBaseEyeBall() {
    matrix.clear();
    matrix.drawBitmap(0,0, baseEyeball, 8, 8, LED_ON);
}

void drawCenteredPupil() {
    matrix.fillRect(defaultPupilX, defaultPupilY, 2, 2, LED_OFF);
}

void pulsateEye() {    
    for(int i = 0; i < 100; i++) {
        dimEye();
        brightenEye();
    }    
}

void dimEye() {
    for(int brightness = 16; brightness > 0; brightness--) {
        setBrightnessAndDrawEye(brightness);
        delay(1);
    }
}

void brightenEye() {
    for(int brightness = 0; brightness < 16; brightness++) {
        setBrightnessAndDrawEye(brightness);
        delay(1);        
    }
}

void setBrightnessAndDrawEye(int brightness) {
    matrix.setBrightness(brightness);
    drawBaseEyeBall();
    drawCenteredPupil();
    matrix.writeDisplay();
}


