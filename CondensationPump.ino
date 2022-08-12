// Written for Adafruit ItsyBitsy 32u4 - 5V 16MHz
// Author: Dan Partington
// Created: 2022/08/08
// Last Updated: 2022/08/12

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
int autoPumpCount = 0;
int greenLED = 0;

// This whole manualModePressCompleted exists to prevent rapid toggling between manual mode on/off while the button is pressed
int manualModePressCompleted = 1; 

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(bottomFloatSwitchPin, INPUT); // reads input from lower float switch, 0 == floating
  pinMode(topFloatSwitchPin, INPUT); // reads input from upper float switch, 0 == floating
  pinMode(redSwitchPin, INPUT); // reads input from red stop button
  pinMode(greenSwitchPin, INPUT); // reads input from green manual-on button
  pinMode(greenLEDPin, OUTPUT); // controls green ring LED around button
  pinMode(redLEDPin, OUTPUT); // controls red ring LED around button
  pinMode(relayPin, OUTPUT); // controls 120v relay for pump control, High = on
}

// the loop function runs over and over again forever
void loop() {
  delay(10); // check state 100 times per second

  //---------------------------------------------------------------------------
  // Read current state of buttons, sensors, etc.
  int bottomFloatSwitch = digitalRead(bottomFloatSwitchPin); // 0 == floating
  int topFloatSwitch = digitalRead(topFloatSwitchPin); // 0 == floating
  int redButton = digitalRead(redSwitchPin);
  int greenButton = digitalRead(greenSwitchPin);
  unsigned long currentMillis = millis();
  unsigned long secondsPumpRunning = (currentMillis-pumpStartTime)/1000;
  // If clock has looped just count from zero instead of recorded start time
  if (currentMillis < pumpStartTime) {
    secondsPumpRunning = currentMillis / 1000;
  }

  //---------------------------------------------------------------------------
  // Manual Mode Button Logic
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
  
  //---------------------------------------------------------------------------
  // Error Mode Logic 
  if (manualMode == 0 && pumping == 1 && errorMode == 0 && secondsPumpRunning > 20) {
    EnableErrorMode();
  }
  if (errorMode == 1) {
    FlashRedLED(currentMillis);
    return;
  }

  //---------------------------------------------------------------------------
  // Manual pumping logic
  if (manualMode == 1 && greenButton == 1 && pumping == 0) {
    StartPumping();
  }
  else if (manualMode == 1 && greenButton == 0 && pumping == 1) {
    StopPumping();
  }
  
  //---------------------------------------------------------------------------
  // Auto pumping logic
  if (manualMode == 0 && pumping == 0 && topFloatSwitch == 0 && bottomFloatSwitch == 0) {
    StartPumping();
    autoPumpCount++;
  }
  if (manualMode == 0 && pumping == 1 && topFloatSwitch == 1 && bottomFloatSwitch == 1) {
    StopPumping();
  }

  //---------------------------------------------------------------------------
  // Flash green LED to indicate number of auto pump cycles since powered on
  if (manualMode == 0 && pumping == 0 && autoPumpCount > 0) {
    FlashGreenAutoPumpCount(currentMillis);
  }
}

void EnableManualMode() {
  manualMode = 1;
  errorMode = 0; // clear errors
  digitalWrite(redLEDPin, HIGH);
  redLED = 1;
  digitalWrite(greenLEDPin, LOW);
  greenLED = 0;
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
  unsigned long currentSecondRemainderInMillis = currentMillis % 1000;
  if (currentSecondRemainderInMillis < 500 && redLED == 0) {
    digitalWrite(redLEDPin, HIGH);
    redLED = 1;
  }
  else if (currentSecondRemainderInMillis >= 500 && redLED == 1) {
    digitalWrite(redLEDPin, LOW);
    redLED = 0;
  }
}

void FlashGreenAutoPumpCount(unsigned long currentMillis) {
  // Flash the green LED the same number of times as the autoPumpCount then
  // wait a period of time and repeat.
  
  // individualFlashTimeMillis is the milliseconds the LED will be lit for, then it 
  // will wait the same amount of time before lighting again. For example a value of 
  // 500 will result in a cycle of light for 1/2 a second, off for 1/2 second.
  // totalCycleTimeMillis is ten seconds longer than the time required to flash
  // out the auto pump count.
  unsigned long individualFlashTimeMillis = 500;
  unsigned long totalCycleTimeMillis = individualFlashTimeMillis * 2 * autoPumpCount + 10000;
  unsigned long currentFlashRemainderInMillis = currentMillis % (individualFlashTimeMillis * 2);
  unsigned long currentCycleRemainderInMillis = currentMillis % totalCycleTimeMillis;
  int stillFlashing = 0;
  if (currentCycleRemainderInMillis < (individualFlashTimeMillis * 2 * autoPumpCount)) {
    stillFlashing = 1;
  }
  if (stillFlashing == 0) {
     return;
  }
  if (currentFlashRemainderInMillis < individualFlashTimeMillis && greenLED == 0) {
    digitalWrite(greenLEDPin, HIGH);
    greenLED = 1;
  }
  else if (currentFlashRemainderInMillis >= individualFlashTimeMillis && greenLED == 1) {
    digitalWrite(greenLEDPin, LOW);
    greenLED = 0;
  }
}
