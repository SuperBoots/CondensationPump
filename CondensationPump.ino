// Adafruit ItsyBitsy 32u4 - 5V 16MHz

const int bottomFloatSwitchPin = 0;
const int topFloatSwitchPin = 1;
const int redSwitchPin = 2;
const int greenSwitchPin = 3;
const int greenLEDPin = 5;
const int redLEDPin = 7;
const int relayPin = 9;
const int BuiltInLEDPin = 13;

int manualMode = 0;
int manualModePressCompleted = 1;
int manualPumpRunning = 0;
int pumping = 0;
unsigned long pumpStartTime = 0;
int errorMode = 0;
int redLED = 0;

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
  pinMode(BuiltInLEDPin, OUTPUT); // onboard LED
}

// the loop function runs over and over again forever
void loop() {
  delay(10);
  int bottomFloatSwitch = digitalRead(bottomFloatSwitchPin); // 0 == floating
  int topFloatSwitch = digitalRead(topFloatSwitchPin); // 0 == floating
  int redButton = digitalRead(redSwitchPin);
  int greenButton = digitalRead(greenSwitchPin);
  unsigned long currentTime = millis();
  unsigned long secondsPumpHasBeenRunning = (currentTime - pumpStartTime) / 1000;

  // If clock has looped then just count from zero instead of the recorded start time
  if (currentTime < pumpStartTime)
  {
    secondsPumpHasBeenRunning = currentTime / 1000;
  }

  if (manualMode == 0 && pumping == 1 && errorMode == 0 && secondsPumpHasBeenRunning > 20)
  {
    EnableErrorMode();
  }

  if (manualModePressCompleted == 0 && redButton == 0)
  {
    manualModePressCompleted = 1;
  }

  // First check if manual mode is being activated or deactivated
  if (redButton == 1 && manualMode == 1 && manualModePressCompleted == 1)
  {
    DisableManualMode();
    manualModePressCompleted = 0;
  }
  else if (redButton == 1 && manualMode == 0 && manualModePressCompleted == 1)
  {
    EnableManualMode();
    manualModePressCompleted = 0;
  }

  if (errorMode == 1)
  {
    FlashRedLED(currentTime);
    return;
  }

  if (manualMode == 1 && greenButton == 1 && pumping == 0)
  {
    StartPumping();
  }
  else if (manualMode == 1 && greenButton == 0 && pumping == 1)
  {
    StopPumping();
  }

  if (manualMode == 0 && pumping == 0 && topFloatSwitch == 0 && bottomFloatSwitch == 0)
  {
    StartPumping();
  }

  if (manualMode == 0 && pumping == 1 && topFloatSwitch == 1 && bottomFloatSwitch == 1)
  {
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

void FlashRedLED(unsigned long currentTime) {
  int thing = currentTime % 1000;
  if (thing < 500 && redLED == 0)
  {
    digitalWrite(redLEDPin, HIGH);
    redLED = 1;
  }
  else if (thing >= 500 && redLED == 1)
  {
    digitalWrite(redLEDPin, LOW);
    redLED = 0;
  }
}
