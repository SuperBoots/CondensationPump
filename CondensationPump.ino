// Adafruit ItsyBitsy 32u4 - 5V 16MHz

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(0, INPUT); // floatSwitch0
  pinMode(1, INPUT); // floatSwitch1
  pinMode(2, OUTPUT); // Red Button LED
  pinMode(3, OUTPUT); // 120v relay
  pinMode(13, OUTPUT); // onboard LED
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
