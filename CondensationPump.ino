// Written for Adafruit ItsyBitsy 32u4 - 5V 16MHz
// Author: Dan Partington
// Created: 2022/08/08
// Last Updated: 2022/08/10

const int bottomFloatSwitchPin = 0;
const int topFloatSwitchPin = 1;
const int redSwitchPin = 2;
const int greenSwitchPin = 3;
const int greenLEDPin = 5;
const int redLEDPin = 7;
const int relayPin = 9;

int manualMode = 0;
int pumping = 0;
unsigned long pumpStartTime = 0;
int errorMode = 0;
int redLED = 0;

// This whole manualModePressCompleted exists to prevent rapid toggling between
// manual mode on/off while the button is pressed
int manualModePressCompleted = 1; 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(bottomFloatSwitchPin, INPUT); // reads input from lower float switch
  pinMode(topFloatSwitchPin, INPUT); // reads input from upper float switch
  pinMode(redSwitchPin, INPUT); // reads input from red stop button
  pinMode(greenSwitchPin, INPUT); // reads input from green manual-on button
  pinMode(greenLEDPin, OUTPUT); // controls green ring LED around button
  pinMode(redLEDPin, OUTPUT); // controls red ring LED around button
  pinMode(relayPin, OUTPUT); // controls 120v relay for pump control, High = on
}

// the loop function runs over and over again forever
void loop() {
  delay(10);
  int bottomFloatSwitch = digitalRead(bottomFloatSwitchPin); // 0 == floating
  int topFloatSwitch = digitalRead(topFloatSwitchPin); // 0 == floating
  int redButton = digitalRead(redSwitchPin);
  int greenButton = digitalRead(greenSwitchPin);
  unsigned long currentMillis = millis();
  unsigned long secondsPumpHasBeenRunning = (currentMillis-pumpStartTime)/1000;

  // If clock has looped just count from zero instead of recorded start time
  if (currentMillis < pumpStartTime) {
    secondsPumpHasBeenRunning = currentMillis / 1000;
  }

  if (manualMode == 0 && pumping == 1 && errorMode == 0 && secondsPumpHasBeenRunning > 20) {
    EnableErrorMode();
  }

  if (manualModePressCompleted == 0 && redButton == 0) {
    manualModePressCompleted = 1;
  }

  // First check if manual mode is being activated or deactivated
  if (redButton == 1 && manualMode == 1 && manualModePressCompleted == 1) {
    DisableManualMode();
    manualModePressCompleted = 0;
  }
  else if (redButton == 1 && manualMode == 0 && manualModePressCompleted == 1) {
    EnableManualMode();
    manualModePressCompleted = 0;
  }

  if (errorMode == 1) {
    FlashRedLED(currentMillis);
    return;
  }

  if (manualMode == 1 && greenButton == 1 && pumping == 0) {
    StartPumping();
  }
  else if (manualMode == 1 && greenButton == 0 && pumping == 1) {
    StopPumping();
  }

  if (manualMode == 0 && pumping == 0 && topFloatSwitch == 0 
      && bottomFloatSwitch == 0) {
    StartPumping();
  }

  if (manualMode == 0 && pumping == 1 && topFloatSwitch == 1 
      && bottomFloatSwitch == 1) {
    StopPumping();
  }
}

void EnableManualMode() {
  manualMode = 1;
  errorMode = 0; // clear errors
  digitalWrite(redLEDPin, HIGH);
  redLED = 1;
}

void DisableManualMode() {
  manualMode = 0;
  digitalWrite(redLEDPin, LOW);
  redLED = 0;
}

void StartPumping() {
  pumping = 1;
  pumpStartTime = millis();
  digitalWrite(relayPin, HIGH);
  digitalWrite(greenLEDPin, HIGH);
}

void StopPumping() {
  pumping = 0;
  digitalWrite(relayPin, LOW);
  digitalWrite(greenLEDPin, LOW);
}

void EnableErrorMode() {
  errorMode = 1;
  StopPumping();
}

void FlashRedLED(unsigned long currentMillis) {
  // Check the current clock time, turn red LED on in the first half of any 
  // given second, turn red LED off in the second half of the second.
  int currentSecondRemainderInMillis = currentMillis % 1000;
  if (currentSecondRemainderInMillis < 500 && redLED == 0) {
    digitalWrite(redLEDPin, HIGH);
    redLED = 1;
  }
  else if (currentSecondRemainderInMillis >= 500 && redLED == 1) {
    digitalWrite(redLEDPin, LOW);
    redLED = 0;
  }
}
