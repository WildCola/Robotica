
//DS= [D]ata [S]torage - data
//STCP= [ST]orage [C]lock [P]in latch
//SHCP= [SH]ift register [C]lock [P]in clock

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const byte regSize = 8; // 1 byte aka 8 bits

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int encodingsNumber = 16;

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

int encodingArray[encodingsNumber][regSize] = {
  {1, 1, 1, 1, 1, 1, 0, 0},  // 0 B11111100
  {0, 1, 1, 0, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1, 0},  // 2
  {1, 1, 1, 1, 0, 0, 1, 0},  // 3
  {0, 1, 1, 0, 0, 1, 1, 0},  // 4
  {1, 0, 1, 1, 0, 1, 1, 0},  // 5
  {1, 0, 1, 1, 1, 1, 1, 0},  // 6
  {1, 1, 1, 0, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1, 0},  // 8
  {1, 1, 1, 1, 0, 1, 1, 0},  // 9
  {1, 1, 1, 0, 1, 1, 1, 0},  // A
  {0, 0, 1, 1, 1, 1, 1, 0},  // b
  {1, 0, 0, 1, 1, 1, 0, 0},  // C
  {0, 1, 1, 1, 1, 0, 1, 0},  // d
  {1, 0, 0, 1, 1, 1, 1, 0},  // E
  {1, 0, 0, 0, 1, 1, 1, 0},  // F
};

const int displayCount = 4;

int hexNumber[displayCount];

int registers[regSize];

const int dpBlinkRate = 500;
long lastBlink = 0;
const int refreshRate = 5;
long lastWrite = 0;

bool programState = 1;
bool dpState = 0;

int currentDisplay = 0;

int reading;
byte swState = LOW;
byte lastReadState = HIGH;

long pressStart = 0;
int longPressTime = 1000;
bool justReseted = 0;

unsigned int debounceDelay = 50;
unsigned long lastDebounceTime = 0;

int xValue = 0;
int yValue = 0;
int minThreshold = 412;
int maxThreshold = 612;
bool joyMovedX = false;
bool joyMovedY = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(pinSW, INPUT_PULLUP);
  

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
    hexNumber[i] = 0;
  }
  Serial.begin(9600);
}

void loop() {
  readJoyStick();
  writeNumber(hexNumber);

  if (programState == 1) {
    state1();
  }

  else {
    state2();
  }
}

void state1() {
  
  if (reading != lastReadState) {       
    if (reading == 0){
      lastDebounceTime = millis();  
      pressStart = millis();     
    }
    else {
      if (millis() - pressStart < longPressTime && justReseted == 0 && millis() - lastDebounceTime > debounceDelay) {
        pressStart = 0;  
        programState = !programState;
      }
      justReseted = 0;      
    }
  }

  if (reading == 0 && millis() - pressStart >= longPressTime && pressStart > 0) {
    for (int i = 0; i < displayCount; ++i){
      hexNumber[i] = 0;
    }
    currentDisplay = 0;
    pressStart = 0;
    reading = 1;
    justReseted = 1;
  }  

  lastReadState = reading;
  
  moveDisplay();  
}

void state2() {
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

  changeDigit();
}

void readJoyStick() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  reading = digitalRead(pinSW);
}

void moveDisplay() {

  if (yValue > maxThreshold && joyMovedY == false && currentDisplay > 0) {
    currentDisplay--;
    joyMovedY = true;    
  }

  if (yValue < minThreshold && joyMovedY == false && currentDisplay < 3) {
    currentDisplay++;
    joyMovedY = true;
  }

  if (yValue > minThreshold && yValue < maxThreshold) {
    joyMovedY = false;
  }
}

void changeDigit() {

  if (xValue > maxThreshold && joyMovedX == false && hexNumber[displayCount - currentDisplay - 1] < 15) {
    hexNumber[displayCount - currentDisplay - 1]++;
    joyMovedX = true;    
  }

  if (xValue < minThreshold && joyMovedX == false && hexNumber[displayCount - currentDisplay - 1] > 0) {
    hexNumber[displayCount - currentDisplay - 1]--;
    joyMovedX = true;
  }

  if (xValue > minThreshold && xValue < maxThreshold) {
    joyMovedX = false;
  }    
}

void activateDisplay(int digit) {
  for(int i=0; i<4; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }

  digitalWrite(displayDigits[digit], LOW);
}
void writeReg(int encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
  
}

void writeNumber(int number[]) {
  int displayIndex = 0;
  int currentDigit = 0;
  while (displayIndex < displayCount) {
    if (millis() - lastWrite > refreshRate) {
      currentDigit = byteEncodings[hexNumber[displayCount-displayIndex-1]];
      if (displayIndex == currentDisplay) {   
        if (millis() - lastBlink > dpBlinkRate) {
          dpState = !dpState;
          lastBlink = millis();
        }
        
        if (dpState == 1 || programState == 0) {
          currentDigit++;
        }       
      }
        
      writeReg(currentDigit);
      activateDisplay(displayIndex);
      displayIndex ++;
      lastWrite = millis();      
    }
  }
}


