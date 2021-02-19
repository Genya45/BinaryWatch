#define BTN_PIN 4 // pin 1000 4
#define LED_PIN0 3 // pin 1000 3
#define LED_PIN1 0 // pin 1000 0 
#define LED_PIN2 1 // pin 1000 1 
#define LED_PIN3 2 // pin 0001 2
uint32_t realTime = 0; //время системы
uint32_t timeLED = 0; // вренмя переключения полоски светодиодов
uint32_t viewTimeLED = 0; // вренмя переключения светодиода
uint32_t nextModeTime = 0; // вренмя переключения следующего режима
uint8_t mode = 0;
uint16_t randCoef = 0;
uint16_t speedCoef = 10;
boolean flag = false;

boolean flag0 = false;
boolean flag1 = false;
boolean flag2 = false;
boolean flag3 = false;
uint8_t time0 = 0;
uint8_t time1 = 4;
uint8_t time2 = 3;
uint8_t time3 = 2;


void turnON();
void viewTime();
void binaryRevert(uint8_t timer);
void timeFlow();
void turnLed(boolean timer0, boolean timer1, boolean timer2, boolean timer3);
void loopLED(int timeNextLED);
void randomLED(int timeNextLED);


void setup() {
  pinMode(LED_PIN0, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  //Serial.begin(9600);
  digitalWrite(LED_PIN0, 0);
  digitalWrite(LED_PIN1, 0);
  digitalWrite(LED_PIN2, 0);
  digitalWrite(LED_PIN3, 0);

}

void loop() {

  if ((millis() - realTime) > 60000) {
    realTime = millis();
    timeFlow();
    //    Serial.print(time3);
    //    Serial.print(time2);
    //    Serial.print(":");
    //    Serial.print(time1);
    //    Serial.print(time0);
    //    Serial.println();
  }




  if (digitalRead(BTN_PIN) == false) {

    if (flag == false && millis() - nextModeTime < 500 && millis() - nextModeTime > 50) {
      mode ++;
      timeLED = 0;
      viewTimeLED = 0;
    }
    if (flag == false) {
      speedCoef += speedCoef;
      //Serial.print("rsefanGSKgnefklsbdgrnsan");
    }
    if (mode == 3) {
      mode = 0;
    }
    if (speedCoef > 1000) {
      speedCoef = 10;
    }

    timeLED = millis();
    viewTimeLED = millis();
    nextModeTime = millis();

    flag = true;
  }
  else {
    flag = false;
  }






  switch (mode) {
    case 0:
      turnON();
      viewTime();
      //Serial.println("q");
      break;
    case 1:
      loopLED(speedCoef);
      //Serial.println("w");
      break;
    case 2:
      randomLED(speedCoef);
      //Serial.println("r");
      break;

  }

}

void turnON() {
  if (millis() - timeLED > 0 && millis() - timeLED < 20) {
    turnLed(1, 0, 0, 0);
  }
  if (millis() - timeLED > 20 && millis() - timeLED < 40) {
    turnLed(0, 1, 0, 0);
  }
  if (millis() - timeLED > 40 && millis() - timeLED < 60) {
    turnLed(0, 0, 1, 0);
  }
  if (millis() - timeLED > 60 && millis() - timeLED < 80) {
    turnLed(0, 0, 0, 1);
  }
}


void timeFlow() {
  time0++;
  if (time0 == 10) {
    time0 = 0;
    time1++;
  }
  if (time1 == 6) {
    time1 = 0;
    time2++;
  }
  if (time2 == 10) {
    time2 = 0;
    time3++;
  }
  if (time3 == 2 && time2 == 4) {
    time3 = 0;
    time2 = 0;
  }
}


void viewTime() {
  if (millis() - viewTimeLED > 90 && millis() - viewTimeLED < 1000) {
    binaryRevert(time3);
  }
  if (millis() - viewTimeLED > 1000 && millis() - viewTimeLED < 1005) {
    timeLED = millis();
  }
  if (millis() - viewTimeLED > 1090 && millis() - viewTimeLED < 2000) {
    binaryRevert(time2);
  }
  if (millis() - viewTimeLED > 2000 && millis() - viewTimeLED < 2005) {
    timeLED = millis();
  }
  if (millis() - viewTimeLED > 2090 && millis() - viewTimeLED < 3000) {
    binaryRevert(time1);
  }
  if (millis() - viewTimeLED > 3000 && millis() - viewTimeLED < 3005) {
    timeLED = millis();
  }
  if (millis() - viewTimeLED > 3090 && millis() - viewTimeLED < 4000) {
    binaryRevert(time0);
  }
  if (millis() - viewTimeLED > 4000 && millis() - viewTimeLED < 4005) {
    timeLED = millis();
  }
  if (millis() - viewTimeLED > 4090) {
    binaryRevert(0);
  }
}

void binaryRevert(uint8_t timer) {
  switch (timer) {
    case 0:
      turnLed(0, 0, 0, 0);
      break;
    case 1:
      turnLed(0, 0, 0, 1);
      break;
    case 2:
      turnLed(0, 0, 1, 0);
      break;
    case 3:
      turnLed(0, 0, 1, 1);
      break;
    case 4:
      turnLed(0, 1, 0, 0);
      break;
    case 5:
      turnLed(0, 1, 0, 1);
      break;
    case 6:
      turnLed(0, 1, 1, 0);
      break;
    case 7:
      turnLed(0, 1, 1, 1);
      break;
    case 8:
      turnLed(1, 0, 0, 0);
      break;
    case 9:
      turnLed(1, 0, 0, 1);
      break;
  }
}

void turnLed(boolean timer0, boolean timer1, boolean timer2, boolean timer3) {
  digitalWrite(LED_PIN0, timer0);
  digitalWrite(LED_PIN1, timer1);
  digitalWrite(LED_PIN2, timer2);
  digitalWrite(LED_PIN3, timer3);
}

void loopLED(int timeNextLED) {
  if (millis() - timeLED > timeNextLED * 0 && millis() - timeLED < timeNextLED * 1) {
    turnLed(1, 0, 0, 0);
  }
  if (millis() - timeLED > timeNextLED * 1 && millis() - timeLED < timeNextLED * 2) {
    turnLed(0, 1, 0, 0);
  }
  if (millis() - timeLED > timeNextLED * 2 && millis() - timeLED < timeNextLED * 3) {
    turnLed(0, 0, 1, 0);
  }
  if (millis() - timeLED > timeNextLED * 3 && millis() - timeLED < timeNextLED * 4) {
    turnLed(0, 0, 0, 1);
  }
  if (millis() - timeLED > timeNextLED * 4 && millis() - timeLED < timeNextLED * 5) {
    turnLed(0, 0, 0, 0);
  }
  if (millis() - timeLED > timeNextLED * 5 && millis() - timeLED < timeNextLED * 6) {
    turnLed(0, 0, 0, 1);
  }
  if (millis() - timeLED > timeNextLED * 6 && millis() - timeLED < timeNextLED * 7) {
    turnLed(0, 0, 1, 0);
  }
  if (millis() - timeLED > timeNextLED * 7 && millis() - timeLED < timeNextLED * 8) {
    turnLed(0, 1, 0, 0);
  }
  if (millis() - timeLED > timeNextLED * 8 && millis() - timeLED < timeNextLED * 9) {
    turnLed(1, 0, 0, 0);
  }
  if (millis() - timeLED > timeNextLED * 9 && millis() - timeLED < timeNextLED * 10) {
    turnLed(0, 0, 0, 0);
  }
  if (millis() - timeLED > timeNextLED * 10 ) {
    timeLED = millis();
  }
}

void randomLED(int timeNextLED) {

  turnLed(flag0, flag1, flag2, flag3);
  if (millis() - timeLED > randCoef ) {
    randCoef = random(timeNextLED * 10);
    timeLED = millis();
    byte randMode = random(4);
    switch (randMode) {
      case 0:
        flag0 = !flag0;
        break;
      case 1:
        flag1 = !flag1;
        break;
      case 2:
        flag2 = !flag2;
        break;
      case 3:
        flag3 = !flag3;
        break;
    }
  }
}
