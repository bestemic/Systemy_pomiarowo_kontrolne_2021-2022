// on board in labolatory HIGH means OFF

void setup() {
  // set pins as input and turn off LED
  for (int i = 24; i <= 31; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  // set pins as input
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);

}

int licznik = 31;
boolean dir = 0;

void loop() {

  if (digitalRead(1) == LOW) {
    dir = 1;
  }

  if (digitalRead(0) == LOW) {
    dir = 0;
  }

  digitalWrite(licznik, LOW);
  delay(500);
  digitalWrite(licznik, HIGH);

  // checking direction
  if (dir == 0) {
    if (licznik != 24) {
      licznik--;
    }
    else {
      licznik = 31;
    }
  }
  else {
    if (licznik != 31) {
      licznik++;

    }
    else {
      licznik = 24;
    }
  }


}
