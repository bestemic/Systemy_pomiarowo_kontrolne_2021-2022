#include <LiquidCrystal.h>

long int k = 0;
int pomiar = 0;

LiquidCrystal lcd(0, 1, 2, 3, 4, 5); // LCD display initialization

void setup()
{
    pinMode(16, OUTPUT);       // initialize pin as output for trigger
    pinMode(17, INPUT_PULLUP); // initialize pin as input for echo
    pinMode(6, INPUT_PULLUP);  // initialize pin as input for switch
    pinMode(7, OUTPUT);        // initialize pin as output for diode
    digitalWrite(7, HIGH);     // switch off diode

    TCNT1H = 255; // timer initialization
    TCNT1L = 198; // timer initialization

    TCCR1A = 0;
    TCCRIB = 0;                           // turning off timer
    TIMSK = (1 << TICIE1) | (1 << TOIE1); // allowing interuptions

    SREG |= 128;

    Serial.begin(9600); // serial port initialization
    lcd.begin(16, 2);   // LCD initialization
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pomiar ");
    lcd.setCursor(7, 1);
    lcd.print(pomiar);
}

void loop()
{
    if (digitalRead(6) == 0) // if button pressed
    {
        while (digitalRead(6) == 0)
        {
            // empty loop (program wait for button relase)
        }

        pomiar++;
        TCNT1H = 255; // timer reset
        TCNT1L = 198; // timer reset

        digitalWrite(7, LOW); // turn off diode

        digitalWrite(16, HIGH); // enabling signal
        delayMicroseconds(10);
        digitalWrite(16, LOW); // closing signal

        k = 0;

        while (digitalRead(17) == 0)
        {
            // waiting for response signal
        }
        TCCR1B = 1; // turning on timer
        while (digitalRead(17) == 1)
        {
            // waiting for end of response signal
        }
        TCCR1B = 0; // turning off timer

        lcd.clear();
        lcd.setCursor(0, 0);
        float wynik = float(k * 0.0034 * 0.5); // converting time for distance

        if (wynik < 4.00 && wynik > 0.02)
        {
            lcd.print(wynik);
            lcd.setCursor(6, 0);
            lcd.print("m");
            Serial.print(wynik);
            Serial.println("m");
        }
        else
        {
            lcd.print("Out of range");
            Serial.println("Out of range");
        }

        lcd.setCursor(0, 1);
        lcd.print("Pomiar ");
        lcd.setCursor(7, 1);
        lcd.print(pomiar);

        delay(1000);
    }
    digitalWrite(7, HIGH); // switch off diode
}

// overflow interruptions
ISR(TIMER1_OVF_vect)
{
    k++;
    TCNT1H = 255; // timer reset
    TCNT1L = 198; // timer reset
}
