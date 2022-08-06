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
  int bottomFloatSwitch = digitalRead(bottomFloatSwitchPin);
  int topFloatSwitch = digitalRead(topFloatSwitchPin);
  int redButton = digitalRead(redSwitchPin);
  int greenButton = digitalRead(greenSwitchPin);

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

  if (manualMode == 1 && greenButton == 1 && pumping == 0)
  {
    StartPumping();
  }
  else if (manualMode == 1 && greenButton == 0 && pumping == 1)
  {
    StopPumping();
  }

  if (manualMode == 0 && pumping == 0 && topFloatSwitch == 1 && bottomFloatSwitch == 1)
  {
    StartPumping();
  }

  if (manualMode == 0 && pumping == 1 && topFloatSwitch == 0 && bottomFloatSwitch == 0)
  {
    StopPumping();
  }
}

void EnableManualMode() {
  manualMode = 1;
  digitalWrite(redLEDPin, HIGH);
}

void DisableManualMode() {
  manualMode = 0;
  digitalWrite(redLEDPin, LOW);
}

void StartPumping() {
  pumping = 1;
  digitalWrite(relayPin, HIGH);
  digitalWrite(greenLEDPin, HIGH);
}

void StopPumping() {
  pumping = 0;
  digitalWrite(relayPin, LOW);
  digitalWrite(greenLEDPin, LOW);
}
