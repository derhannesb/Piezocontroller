const int sensorPinA=A0;
const int sensorPinB=A1;
const int sensorPinC=A2;
const int sensorPinD=A3;
const int sensorPinE=8;
const int sensorPinF=9;

const int ledPin = 10;
const int threshold = 50;

void setup()
{
  pinMode(ledPin, OUTPUT);
  
  pinMode(sensorPinA, INPUT);
  pinMode(sensorPinB, INPUT);
  pinMode(sensorPinC, INPUT);
  pinMode(sensorPinD, INPUT);
  pinMode(sensorPinE, INPUT);
  pinMode(sensorPinF, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop()
{
  int piezoA = analogRead(sensorPinA) >= threshold;
  int piezoB = analogRead(sensorPinB) >= threshold;
  int piezoC = analogRead(sensorPinC) >= threshold;
  int piezoD = analogRead(sensorPinD) >= threshold;
  int piezoE = false;//analogRead(sensorPinE) >= threshold;
  int piezoF = analogRead(sensorPinF) >= threshold;
  /*
  piezoA = false;
  piezoB = false;
  piezoC = false;
  piezoD = false;
  piezoE = false;
  piezoF = false;
  */
  if (piezoA || piezoB || piezoC || piezoD || piezoE || piezoF)
  {
    Serial.print("A: " + String(piezoA) + ", ");
    Serial.print("B: " + String(piezoB) + ", ");
    Serial.print("C: " + String(piezoC) + ", ");
    Serial.print("D: " + String(piezoD) + ", ");
    Serial.print("E: " + String(piezoE) + ", ");
    Serial.println("F: " + String(piezoF) + "");
    if (piezoA) Keyboard.press(KEY_LEFT_ARROW);
    if (piezoB) Keyboard.press(KEY_RIGHT_ARROW);
    if (piezoC) Keyboard.press(KEY_UP_ARROW);
    if (piezoD) Keyboard.press(KEY_DOWN_ARROW);
    if (piezoE) Keyboard.press(',');
    if (piezoF) Keyboard.press('.');
    
    
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    Keyboard.releaseAll();
  }
} 
