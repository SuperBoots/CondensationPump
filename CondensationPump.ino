// Adafruit ItsyBitsy 32u4 - 5V 16MHz

const int bottomFloatSwitchPin = 0;
const int topFloatSwitchPin = 1;
const int redSwitchPin = 2;
const int greenSwitchPin = 3;
const int greenLEDPin = 5;
const int redLEDPin = 7;
const int relayPin = 9;
const int BuiltInLEDPin = 13;

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
  int bottomFloatSwitch = digitalRead(bottomFloatSwitchPin);
  int topFloatSwitch = digitalRead(topFloatSwitchPin);
  int redButton = digitalRead(redSwitchPin);
  int greenButton = digitalRead(greenSwitchPin);
  delay(100);
  if (bottomFloatSwitch != 0)
  {
    digitalWrite(greenLEDPin, HIGH);
  }
  else
  {
    digitalWrite(greenLEDPin, LOW);
  }
  
  if (topFloatSwitch != 0)
  {
    digitalWrite(redLEDPin, HIGH);
  }
  else
  {
    digitalWrite(redLEDPin, LOW);
  }
  
  if (redButton != 0)
  {
    digitalWrite(BuiltInLEDPin, HIGH);
  }
  else
  {
    digitalWrite(BuiltInLEDPin, LOW);
  }

  if (greenButton != 0)
  {
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }
}
