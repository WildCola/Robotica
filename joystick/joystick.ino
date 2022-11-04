const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

byte programState = 1;
int currentSeg = 0;

const int segSize = 8;
const int noOfCooridnates = 4;

bool commonAnode = false;
byte state = HIGH;
byte dpState = LOW;

int reading;
byte swState = LOW;
byte lastReadState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTimeX = 0;
unsigned long lastDebounceTimeY = 0;
unsigned int debounceDelay = 50;

int xValue = 0;
int yValue = 0;
int lastXValue = 512;
int lastYValue = 512;
bool joyMovedX = false;
bool joyMovedY = false;
int digit = 0;
int minThreshold = 300;
int maxThreshold = 700;

long lastBlink = 0;
int blinkInterval = 500;
byte segState = LOW;

long pressStart = 0;
int longPressTime = 1000;
bool justReseted = 0;



int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte litSegments[segSize] = {0, 0, 0, 0, 0, 0, 0, 0};

const unsigned int neighbours[segSize][noOfCooridnates] = {
// U  D  L  R
  {0, 6, 5, 1},   // a
  {0, 6, 5, 1},   // b
  {6, 3, 4, 7},   // c
  {6, 3, 4, 2},   // d
  {6, 3, 4, 2},   // e
  {0, 6, 5, 1},   // f
  {0, 3, 6, 6},   // g 
  {7, 7, 2, 7}    // DP
};
const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

void setup() {
  for (int i = 0; i < segSize; ++i){
    pinMode(segments[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);

  if (commonAnode == true){
    state = !state;
  }

  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  reading = digitalRead(pinSW);
  Serial.println(programState);

  if (programState == 1) {
    state1();
  }
  else {
    state2();
  }
}

void blink() {
  if(millis() - lastBlink > blinkInterval) {
    segState = !segState;
    digitalWrite(segments[currentSeg], segState);
    lastBlink = millis();
  }
}

void changeSegment() {

  if (xValue != lastXValue) {
    lastDebounceTimeX = millis();
  }
  if (millis() - lastDebounceTimeX > debounceDelay) {
    if (xValue > maxThreshold && joyMovedX == false) {
    digitalWrite(segments[currentSeg], litSegments[currentSeg]);
    currentSeg = neighbours[currentSeg][up];
    joyMovedX = true;
    }
    if (xValue < minThreshold && joyMovedX == false) {
      digitalWrite(segments[currentSeg], litSegments[currentSeg]);
      currentSeg = neighbours[currentSeg][down];
      joyMovedX = true;
    }
    if (xValue > minThreshold && xValue < maxThreshold) {
      joyMovedX = false;
    }
  }

  lastXValue = xValue;
  
  if (yValue != lastYValue) {
    lastDebounceTimeY = millis();
  }
  if (millis() - lastDebounceTimeY > debounceDelay) {
    if (yValue > maxThreshold && joyMovedY == false) {
      digitalWrite(segments[currentSeg], litSegments[currentSeg]);
      currentSeg = neighbours[currentSeg][right];
      joyMovedY = true;      
    }

    if (yValue < minThreshold && joyMovedY == false) {
      digitalWrite(segments[currentSeg], litSegments[currentSeg]);
      currentSeg = neighbours[currentSeg][left];
      joyMovedY = true;      
    }

    if (yValue > minThreshold && yValue < maxThreshold) {
      joyMovedY = false;
    }
  }

  lastYValue = yValue;
}

void state1() {
  blink();

  if (reading != lastReadState) {         
    if (reading == 0){
      lastDebounceTime = millis();  
      pressStart = millis();
    }
    else {
      if (millis() - pressStart < longPressTime && justReseted == 0 && millis() - lastDebounceTime > debounceDelay) {
        litSegments[currentSeg] = segState;
        pressStart = 0;  
        programState = !programState;
      }
      justReseted = 0;      
    }
  }
    
  if (reading == 0 && millis() - pressStart >= longPressTime && pressStart > 0) {
    for (int i = 0; i < segSize; ++i){
      litSegments[i] = LOW;
      digitalWrite(segments[i], LOW);
    }
    currentSeg = 7;  
    pressStart = 0;
    reading = 1;
    justReseted = 1;
  }

  lastReadState = reading; 
  
  changeSegment();
}

void state2() {
  digitalWrite(segments[currentSeg], litSegments[currentSeg]);
  
  if (reading != lastReadState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != swState) {
      swState = reading;

      if (swState == LOW) {
        programState = !programState;
      }
    }
  }  

  lastReadState = reading;  

  if (xValue != lastXValue) {
    lastDebounceTimeX = millis();
  }
  if (millis() - lastDebounceTimeX > debounceDelay) {
    if (xValue > maxThreshold && joyMovedX == false) {
      litSegments[currentSeg] = !litSegments[currentSeg];
      joyMovedX = true;
    }

    if (xValue < minThreshold && joyMovedX == false) {
      litSegments[currentSeg] = !litSegments[currentSeg];
      joyMovedX = true;
    }

    if (xValue > minThreshold && xValue < maxThreshold) {
      joyMovedX = false;
    }  
  }
  lastXValue = xValue;
}
