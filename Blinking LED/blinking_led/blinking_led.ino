// Functions

int setInterval (bool y, bool g, bool r){
  return 75 * (y + g + r);
}


// Pin assignments
const int yellowButtonPin = 2;
const int greenButtonPin = 4;
const int redButtonPin = 7;
const int yellowLedPin = 13;
const int greenLedPin = 12;
const int redLedPin = 11;

int yellowButtonState;
int lastYellowButtonState = LOW;

int greenButtonState;
int lastGreenButtonState = LOW;

int redButtonState;
int lastRedButtonState = LOW;

unsigned long lastYellowDebounceTime = 0;
unsigned long lastGreenDebounceTime = 0;
unsigned long lastRedDebounceTime = 0;

unsigned long debounceDelay = 50; 

bool yellow = 1;
bool green = 1;
bool red = 1;

bool yellowBlink = 1;
bool greenBlink = 1;
bool redBlink = 1;

long interval = 225;
unsigned long previousMillis = 0;
unsigned long currentMillis;

int switcher = 0;

void setup() {
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  pinMode(yellowButtonPin, INPUT);
  pinMode(greenButtonPin, INPUT);
  pinMode(redButtonPin, INPUT);

  // Initial LED states
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);

  Serial.begin(9600);  // Start Serial Monitor
}

void loop() {
  // Read button states
  int readingYellow = digitalRead(yellowButtonPin);
  int readingGreen = digitalRead(greenButtonPin);
  int readingRed = digitalRead(redButtonPin);

  currentMillis = millis();


  if (readingYellow != lastYellowButtonState) {
    lastYellowDebounceTime = millis();
  }
  if (readingGreen != lastGreenButtonState) {
    lastGreenDebounceTime = millis();
  }
  if (readingRed != lastRedButtonState) {
    lastRedDebounceTime = millis();
  }

  if ((millis() - lastYellowDebounceTime) > debounceDelay) {
    if (readingYellow != yellowButtonState) {
      yellowButtonState = readingYellow;
      if (yellowButtonState == HIGH) {
        yellow = !yellow;
        interval = setInterval(yellow, green, red);
        return;
      }
    }
  }

  if ((millis() - lastGreenDebounceTime) > debounceDelay) {
    if (readingGreen != greenButtonState) {
      greenButtonState = readingGreen;
      if (greenButtonState == HIGH) {
        green = !green;
        interval = setInterval(yellow, green, red);
        return;
      }
    }
  }

  if ((millis() - lastRedDebounceTime) > debounceDelay) {
    if (readingRed != redButtonState) {
      redButtonState = readingRed;
      if (redButtonState == HIGH) {
        red = !red;
        interval = setInterval(yellow, green, red);
        return;
      }
    }
  }



  lastYellowButtonState = readingYellow;
  lastGreenButtonState = readingGreen;
  lastRedButtonState = readingRed;


  switch(switcher){
    case 0:
    if(yellow){
      if (yellowBlink){
        if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(yellowLedPin, HIGH);
        yellowBlink = !yellowBlink;
        }
      }
      else{
      if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          digitalWrite(yellowLedPin, LOW);
          switcher++;
          yellowBlink = !yellowBlink;
          }
      }
    }
    else{
      digitalWrite(yellowLedPin, LOW);
      switcher++;
    }
    break;
    case 1:
    if(green){
      if (greenBlink){
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          digitalWrite(greenLedPin, HIGH);
          greenBlink = !greenBlink;
        }
      }
      else{
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          digitalWrite(greenLedPin, LOW);
          switcher++;
          greenBlink = !greenBlink;
        }
      }
    }
    else {
      digitalWrite(greenLedPin, LOW);
      switcher++;
    }
    break;
    case 2:
    if(red){
      if (redBlink){
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          digitalWrite(redLedPin, HIGH);
          redBlink = !redBlink;
        }
      }
      else{
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          digitalWrite(redLedPin, LOW);
          switcher = switcher % 2;
          redBlink = !redBlink;
        }
      }
    }
    else {
      digitalWrite(redLedPin, LOW);
      switcher = switcher % 2;
    }
    break;
  }
  
  Serial.print("Yellow: "); Serial.print(yellow); Serial.print(" | ");
  Serial.print("Green: "); Serial.print(green); Serial.print(" | ");
  Serial.print("Red: "); Serial.print(red); Serial.print(" | ");
  Serial.print("Interval: "); Serial.println(interval);

}
