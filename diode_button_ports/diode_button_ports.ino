// maybe some values can be reversed on board in labolatory

void setup() {
  // set port B as input
  DDRB = DDRB & 0b11111011;   // set only specyfic bit to zero
  PORTB = 0b00000100;         // enable inputt_pullup on pin 0

  // set port C as output
  DDRC |= 0b00001000;         // set only specyfic bit to zero
}

void loop() {
  // read button state
  int dane = PINB & 0b00000100;   // read only from specyfic port

  // check what state is
  if (dane == 0b00000100) {
    PORTC = 0b00001000;       // turn on lights when not pressed
  }
  else {
    PORTC = 0b11110111;       // turn off lights when pressed
  }
}
