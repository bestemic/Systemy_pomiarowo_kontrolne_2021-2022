#include <LiquidCrystal.h> // adding LCD display library

long int k = 0;
int odczyt = 0;

LiquidCrystal lcd(5, 4, 3, 2, 1, 0); // LCD display initialization

void setup()
{
    DDRC = 0b00000001; // setting port to output

    TCNT0 = 0;  // timer initialization
    OCR0 = 100; // setting comparable

    TCCR0 = (1 << WGM01) | (1 << CS01);  // prescaler settings
    TIMSK = (1 << OCIE0) | (1 << TOIE0); // allowing interuptions

    SREG |= 128;

    lcd.begin(16, 2);   // LCD initialization
    Serial.begin(9600); // serial port initialization
}

void loop()
{
    // empty loop (program using interruptions only)
}

// overflow interruptions
ISR(TIMER0_COMP_vect)
{
    k++;

    if (k > 2000)
    {
        TCNT0 = 0; // timer restart
        k = 0;
        odczyt = analogRead(7);           // reading from analog
        double wynik = konwersja(odczyt); // converting int number to volts
        lcd.clear();                      // clearing LCD
        PORTC = ~PORTC;                   // blinking diode
        lcd.print(wynik);                 // writing to LCD
        Serial.println(wynik);            // writing to serial port
    }
}

// function converting numbers to volts
double konwersja(int odczyt)
{
    return odczyt * (5.0 / 1023.0);
}
