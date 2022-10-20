const int ledG = 9;
const int ledR = 10;
const int ledB = 11;

const int potG = A0;
const int potR = A1;
const int potB = A2;

float potValueR = 0;
float potValueG = 0;
float potValueB = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValueR = analogRead(potR);
  potValueG = analogRead(potG);
  potValueB = analogRead(potB);

  analogWrite(ledR, potValueR/4);
  analogWrite(ledG, potValueG/4);
  analogWrite(ledB, potValueB/4);
}
