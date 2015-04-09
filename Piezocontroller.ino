const int sensorPinA=A0;
const int sensorPinB=A1;
const int sensorPinC=A2;
const int sensorPinD=A3;
const int sensorPinE=8;
const int sensorPinF=9;

const int threshold = 50;

const int debounceDelay = 100;
const int debounceThreshold = 6;

long lastReadoutMillis = 0; 

int piezoAValue = 0;
int piezoBValue = 0;
int piezoCValue = 0;
int piezoDValue = 0;
int piezoEValue = 0;
int piezoFValue = 0;

void setup()
{
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
  //5 mal hintereinander = 1 SONST 0
  int piezoA = analogRead(sensorPinA) >= threshold;
  int piezoB = analogRead(sensorPinB) >= threshold;
  int piezoC = analogRead(sensorPinC) >= threshold;
  int piezoD = analogRead(sensorPinD) >= threshold;
  int piezoE = false;//analogRead(sensorPinE) >= threshold;
  int piezoF = analogRead(sensorPinF) >= threshold;
  
  if (piezoA) piezoAValue += 1;
  if (piezoB) piezoBValue += 1;
  if (piezoC) piezoCValue += 1;
  if (piezoD) piezoDValue += 1;
  if (piezoE) piezoEValue += 1;
  if (piezoF) piezoFValue += 1;
  
  if (millis() - lastReadoutMillis > debounceDelay)
  {
    Keyboard.releaseAll();
    
    piezoA = piezoAValue > debounceThreshold;
    piezoB = piezoBValue > debounceThreshold;
    piezoC = piezoCValue > debounceThreshold;
    piezoD = piezoDValue > debounceThreshold;
    piezoE = piezoEValue > debounceThreshold;
    piezoF = piezoFValue > debounceThreshold;
    
    if (piezoA || piezoB || piezoC || piezoD || piezoE || piezoF)
    {
      Serial.println("X-Times: : " + String(piezoCValue) + "");
      
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
    }

    
    piezoAValue = 0;
    piezoBValue = 0;
    piezoCValue = 0;
    piezoDValue = 0;
    piezoEValue = 0;
    piezoFValue = 0;
    lastReadoutMillis = millis();
  }
} 
