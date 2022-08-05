// Adafruit ItsyBitsy 32u4 - 5V 16MHz

const int bottomFloatSwitchPin = 0;
const int topFloatSwitchPin = 1;
const int redSwitchPin = 2;
const int greenSwitchPin = 3;
const int greenLEDPin = 5;
const int redLEDPin = 7;
const int 120vRelayPin = 9;
const int BuiltInLED = 9;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(bottomFloatSwitchPin, INPUT); // reads input from lower float switch
  pinMode(topFloatSwitchPin, INPUT); // reads input from upper float switch
  pinMode(redSwitchPin, INPUT); // reads input from red stop button
  pinMode(greenSwitchPin, INPUT); // reads input from green manual-on button
  pinMode(greenLEDPin, OUTPUT); // controls green ring LED around button
  pinMode(redLEDPin, OUTPUT); // controls red ring LED around button
  pinMode(120vRelayPin, OUTPUT); // controls 120v relay for pump control, High = on
  pinMode(BuiltInLED, OUTPUT); // onboard LED
}

// the loop function runs over and over again forever
void loop() {
  int floatSwitch0 = digitalRead(0);
  int floatSwitch1 = digitalRead(1);
  delay(100);
  if (floatSwitch0 != 0)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
  if (floatSwitch1 != 0)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
}
