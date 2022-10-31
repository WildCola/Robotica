const int greenPedPin = 12;
const int redPedPin = 11;
const int greenCarPin = 10;
const int yellowCarPin = 9;
const int redCarPin = 8;
const int buzzerPin = 7;
const int buttonPin = 2;

const unsigned int stage1 = 8000;
const unsigned int stage2 = 11000;
const unsigned int stage3 = 19000;
const unsigned int stage4 = 23000; 

volatile unsigned long lastDebounceTime = 0;
volatile const unsigned int debounceDelay = 50;

volatile unsigned long timerStart = 0;

const unsigned int buzzerTone = 300;
const unsigned int buzzerDuration = 500;
const unsigned int buzzerInterval = 1000;
unsigned long buzzerTimer = 0;

const unsigned greenPedBlinkInterval = 200;
unsigned long greenPedBlinkTimer = 0;
byte greenPedState = 0;

const unsigned int greenPedBuzzDuration = 200;
const unsigned int greenPedBuzzInterval = 400;


void setup() {
  pinMode(greenPedPin, OUTPUT);
  pinMode(redPedPin, OUTPUT);
  pinMode(greenCarPin, OUTPUT);
  pinMode(yellowCarPin, OUTPUT);
  pinMode(redCarPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), crosswalk, FALLING);

  digitalWrite(redPedPin, HIGH);
  digitalWrite(greenPedPin, LOW);
  digitalWrite(redCarPin, LOW);
  digitalWrite(yellowCarPin, LOW);
  digitalWrite(greenCarPin, HIGH);

  Serial.begin(9600);
}

void loop() 
{
  if (timerStart != 0)
  {
    if ((millis() - timerStart) > stage1 && (millis() - timerStart) <= stage2)
    {
      digitalWrite(greenCarPin, LOW);
      digitalWrite(yellowCarPin, HIGH);
    }
    else if ((millis() - timerStart) > stage2 && (millis() - timerStart) <= stage3)
    {
      if((millis() - buzzerTimer) > buzzerInterval)
      {
        buzzerTimer = millis();
        tone(buzzerPin, buzzerTone, buzzerDuration);
      }
      digitalWrite(yellowCarPin, LOW);
      digitalWrite(redCarPin, HIGH);
      digitalWrite(redPedPin, LOW);
      digitalWrite(greenPedPin, HIGH);
    }
    else if ((millis() - timerStart) > stage3 && (millis() - timerStart) <= stage4)
    {
      if((millis() - greenPedBlinkTimer) > greenPedBlinkInterval)
      {      
          greenPedBlinkTimer = millis();
          greenPedState = !greenPedState;
          digitalWrite(greenPedPin, greenPedState);
      }
      if((millis() - buzzerTimer) > greenPedBuzzInterval)
      {
        buzzerTimer = millis();
        tone(buzzerPin, buzzerTone, greenPedBuzzDuration);
      }      
    }
    else if ((millis() - timerStart) > stage4)
    {
      timerStart = 0;
      buzzerTimer = 0;
      greenPedBlinkTimer = 0;
      greenPedState = 0;

      digitalWrite(redPedPin, HIGH);
      digitalWrite(greenPedPin, LOW);
      digitalWrite(redCarPin, LOW);
      digitalWrite(yellowCarPin, LOW);
      digitalWrite(greenCarPin, HIGH);      
    }
  }
  
}

void crosswalk()
{
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (timerStart == 0)
    {
      timerStart = millis();
      Serial.println(timerStart);
    }
  }

  lastDebounceTime = millis();
}
