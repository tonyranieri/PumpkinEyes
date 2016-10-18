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
    UP = 0,
    UP_RIGHT = 1,
    RIGHT = 2,
    DOWN_RIGHT = 3,
    DOWN = 4,
    DOWN_LEFT = 5,
    LEFT = 6,
    UP_LEFT = 7,
    CENTER = 8;

const int // standard moves
    BLINK = 0,
    MOVE_EYE = 1,
    SPECIAL = 2;
    
const int // special moves
    SPIN = 0,
    ROLL = 1, 
    TWIRL = 2,
    FLASH = 3,
    PINGPONG = 4;


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
  blank[] {
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

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);  // pass in the address
  randomSeed(analogRead(0));

  drawDefaultEye();
}

void loop() {
    int wait = random(10, 5000);
    delay(wait);

    int nextAction = getRandomAction();
    Serial.print("Next Action: ");
    Serial.println(nextAction);

    switch(nextAction) {
        case BLINK:
            blink();
            break;
        case MOVE_EYE:
            movePupilToLocation(getRandomGaze());
            break;
        case SPECIAL:
            performSpecialMove(getRandomSpecialMove());
            break;
    } 
}

void performSpecialMove(int specialMove) {
    Serial.print("Next Special Move: ");
    Serial.println(specialMove);
  
    switch(specialMove) {
        case SPIN:
            spinEye();
            break;
        case ROLL:
            rollEye();
            break;
        case TWIRL:
            twirlEye();
            break;
        case FLASH:
            pulsateEye();
            break;
        case PINGPONG:
            pingpongEyeball();
            break;
    }
}

int getRandomAction() {
    int weightedChoices[] = { 80, 50, 10 };
    return getWeightedRandomNumber(weightedChoices, 3);
}

int getRandomSpecialMove() {
    int weightedChoices[] = { 20, 20, 20, 1, 10 };
    return getWeightedRandomNumber(weightedChoices, 5);
}

int getRandomGaze() {
    int weightedChoices[] = {10, 10, 10, 10, 10, 10, 10, 10, 70};
    return getWeightedRandomNumber(weightedChoices, 9);
}

// weightedChoices - array of weights corresponding to how often something should occur 
// choiceCount - total # of choices in the weightedChoices array
int getWeightedRandomNumber(int weightedChoices[], int choiceCount) {
    int sumOfWeight = 0;
    
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

void setPupilToLocatoin(int location) {
    pupilX = getPupilTargetX(location);
    pupilY = getPupilTargetY(location);
    drawEye();
}

void movePupilToLocation(int destination) {
    movePupilToLocation(destination, 50);
}

// delayms - smaller delay will make the animation faster, longer will make animation slower 
void movePupilToLocation(int destination, int delayms) {
    drawEye();
    delay(20);

    int targetX = getPupilTargetX(destination),
        targetY = getPupilTargetY(destination);

    Serial.print("pupil moving to destination: ");
    Serial.println(destination);

    while(pupilX != targetX || pupilY != targetY) {
        updatePupilX(targetX);
        updatePupilY(targetY);
        drawEye();        
        delay(delayms);  // delay while we're drawing the pupil movement so we can see it happen
    }
}

int getPupilTargetY(int destination) {
    switch(destination) {
        case UP:
        case CENTER:
        case DOWN:
            return 3;
            break;

        case UP_LEFT:
        case LEFT:
        case DOWN_LEFT:        
            return 6;
            break;
        
        case UP_RIGHT:
        case RIGHT:    
        case DOWN_RIGHT:
            return 0;
            break;
    }
}

int getPupilTargetX(int destination) {
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

// void snooze() {
//   matrix.clear();
//   matrix.drawBitmap(0,0, blank, 8, 8, LED_ON);
//   matrix.writeDisplay();

//   matrix.setTextSize(1);
//   matrix.setTextWrap(false); 
//   matrix.setTextColor(LED_ON);

//   delay(2500);    

//   for (int8_t x=0; x>=-60; x--) {
//     matrix.clear();
//     matrix.setCursor(x,0);
//     matrix.print("ZZZZZZZZZZZZZZZZ");
//     matrix.writeDisplay();
//     delay(100);
//   }

//   matrix.clear();
//   matrix.drawBitmap(0,0, blank, 8, 8, LED_ON);
//   matrix.writeDisplay();
//   delay(3000);    

//   matrix.clear();
//   matrix.drawBitmap(0,0, eyeball, 8, 8, LED_ON);
//   matrix.writeDisplay();
// }

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
    drawPupil();
    matrix.fillRect(-1,-1, lidHeight, 9, LED_OFF);
    matrix.writeDisplay();
}

void drawDefaultEye() {
  drawBaseEyeBall();
  movePupilToLocation(CENTER);
  drawPupil();
  matrix.writeDisplay();
}

void drawBaseEyeBall() {
    matrix.clear();
    matrix.drawBitmap(0,0, baseEyeball, 8, 8, LED_ON);
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
    drawPupil();
    matrix.writeDisplay();
}

void pingpongEyeball() {
    int spinCount = 3;

    int direction1 = random(0,7);
    int direction2 = pickOppositeDirection(direction1);
    int delayms = 15;

    for(int i = 0; i < spinCount; i++) {
        movePupilToLocation(CENTER, delayms);
        movePupilToLocation(direction1, delayms);
        movePupilToLocation(direction2, delayms);
    }

    movePupilToLocation(CENTER);
}

int pickOppositeDirection(int direction) {

    switch (direction) {
        case UP: 
            return DOWN;
            break;
        case UP_RIGHT:
            return DOWN_LEFT;
            break;
        case RIGHT:
            return LEFT;
            break;
        case DOWN_RIGHT:
            return UP_LEFT;
            break;
        case DOWN:
            return UP;
            break;
        case DOWN_LEFT:
            return UP_RIGHT;
            break;
        case LEFT:
            return RIGHT;
            break;
        case UP_LEFT:
            return DOWN_RIGHT;
            break;
    }
}

void spinEye() {
    int spinCount = 5;
    int delayms = 15;

    for(int i = 0; i < spinCount; i++) {
        movePupilToLocation(CENTER, delayms);
        movePupilToLocation(RIGHT, delayms);
        drawBaseEyeBall();
        matrix.writeDisplay();
        delay(150);
        setPupilToLocatoin(LEFT);
    }

    movePupilToLocation(CENTER);
}

void rollEye() {
    int rollCount = 5;
    int delayms = 15;

    for(int i = 0; i < rollCount; i++) {
        movePupilToLocation(CENTER, delayms);
        movePupilToLocation(UP, delayms);
        drawBaseEyeBall();
        matrix.writeDisplay();
        delay(150);
        setPupilToLocatoin(DOWN);
    }

    movePupilToLocation(CENTER);
}

void twirlEye() {
    int twirlCount = 3;
    int delayms = 10;

    movePupilToLocation(CENTER, delayms);

    for(int i = 0; i < twirlCount; i++) {
        movePupilToLocation(UP, delayms);
        movePupilToLocation(UP_RIGHT, delayms);
        movePupilToLocation(RIGHT, delayms);
        movePupilToLocation(DOWN_RIGHT, delayms);
        movePupilToLocation(DOWN, delayms);
        movePupilToLocation(DOWN_LEFT, delayms);
        movePupilToLocation(LEFT, delayms);
        movePupilToLocation(UP_LEFT, delayms);
    }

    movePupilToLocation(CENTER);
}




