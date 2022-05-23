#include <LiquidCrystal.h> // adding LCD display library

long int k = 0;
int odczyt = 0;

LiquidCrystal lcd(5, 4, 3, 2, 1, 0); // LCD display initialization

void setup()
{
    DDRC = 0b00000001; // setting port to output

    TCCR1A = 0;
    TCCR1B = (1 << CS11);                 // prescaler settings
    TIMSK = (1 << TICIE1) | (1 << TOIE1); // allowing interuptions

    TCNT1H = 0b11111111; // timer initialization
    TCNT1L = 0b10011100; // timer initialization

    SREG |= 128;

    lcd.begin(16, 2);   // LCD initialization
    Serial.begin(9600); // serial port initialization
}

void loop()
{
    // empty loop (program using interruptions only)
}

// overflow interruptions
ISR(TIMER1_OVF_vect)
{
    TCNT1H = 0b11111111; // timer reset
    TCNT1L = 0b10011100; // timer reset
    k++;

    if (k > 2000)
    {
        k = 0;
        odczyt = analogRead(7);           // reading from analog
        double wynik = konwersja(odczyt); // converting int number to volts
        lcd.clear();                      // clearing LCD
        PORTC = ~PORTC;                   // blinking diode
        lcd.print(wynik);                 // writing to LCD
        Serial.println(wynik);            // writing to serial por
    }
}

// function converting numbers to volts
double konwersja(int odczyt)
{
    return odczyt * (5.0 / 1023.0);
}
