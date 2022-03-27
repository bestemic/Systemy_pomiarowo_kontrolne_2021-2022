// on board in labolatory HIGH means OFF

void setup() {
  // initialize pin 24 as output
  pinMode(8, OUTPUT);

  // initialize pin 1 as input
  pinMode(1, INPUT);
}

void loop() {
  // check the button is pressed
  if (digitalRead(1) == HIGH) {
    digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  }
}
