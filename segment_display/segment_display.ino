// on board in labolatory HIGH means OFF

void setup() {
  // set outputs pins for 8 segments
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // set output pins for choosing number
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
}

void loop() {
  // turn first number
  digitalWrite(24, LOW);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  cyfra(9);
  delay(1);

  // turn second number
  digitalWrite(24, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  cyfra(3);
  delay(1);

  // turn third number
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  cyfra(2);
  delay(1);

  // turn fourth number
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  cyfra(1);
  delay(1);
}

// function to number display
void cyfra(int cyfra) {
  clean();
  digitalWrite(7, HIGH);

  // choosing and displaying number
  switch (cyfra) {
    case 0:
      digitalWrite(6, HIGH);
      break;

    case 1:
      digitalWrite(0, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      break;

    case 2:
      digitalWrite(2, HIGH);
      digitalWrite(5, HIGH);
      break;

    case 3:
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      break;

    case 4:
      digitalWrite(0, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      break;

    case 5:
      digitalWrite(1, HIGH);
      digitalWrite(4, HIGH);
      break;

    case 6:
      digitalWrite(1, HIGH);
      break;

    case 7:
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      break;

    case 8:
      break;

    case 9:
      digitalWrite(4, HIGH);
      break;
  }
}

// functtion to reset number
void clean() {
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
