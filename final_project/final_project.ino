
void setup()
{
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

    // set output pins for LED
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    // turn off LED
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);

    // set input pins for buttons
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
}

long int sec = 43200; // initial time

int busy = 0;
int seth = 0;
int setm = 0;
int i = 0;

void loop()
{

    // turning on hours programming
    if (digitalRead(12) == LOW && busy == 0)
    {
        while (digitalRead(12) == LOW)
        {
        }
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        busy = 1;
        seth = 1;
    }

    // turning on minutes programming
    if (digitalRead(11) == LOW && busy == 0)
    {
        while (digitalRead(11) == LOW)
        {
        }
        digitalWrite(10, HIGH);
        digitalWrite(8, LOW);
        busy = 1;
        setm = 1;
    }

    // turning off hours programming
    if (digitalRead(12) == LOW && busy == 1 && seth == 1)
    {
        while (digitalRead(12) == LOW)
        {
        }
        digitalWrite(9, HIGH);
        busy = 0;
        seth = 0;
    }

    // turning off hours programming
    if (digitalRead(11) == LOW && busy == 1 && setm == 1)
    {
        while (digitalRead(11) == LOW)
        {
        }
        digitalWrite(8, HIGH);
        busy = 0;
        setm = 0;
    }

    // time increasing
    if (digitalRead(14) == LOW && busy == 1)
    {
        while (digitalRead(14) == LOW)
        {
        }
        if (seth)
        {
            sec = sec + 3600;
        }

        if (setm)
        {
            sec = sec + 60;
        }
    }

    // time reducing
    if (digitalRead(13) == LOW && busy == 1)
    {
        while (digitalRead(13) == LOW)
        {
        }
        if (seth)
        {
            sec = sec - 3600;
        }

        if (setm)
        {
            sec = sec - 60;
        }
    }

    // turning on LED
    if (sec % 2 == 0 && busy == 0)
    {
        digitalWrite(10, LOW);
    }
    if (sec % 2 == 1 && busy == 0)
    {
        digitalWrite(10, HIGH);
    }

    // time counting
    sec = sec % 86400;
    int hours = sec / 3600;
    int minu = sec - hours * 3600;
    minu = sec / 60;
    minu = minu % 60;

    // turn first number
    digitalWrite(24, LOW);
    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    cyfra(minu % 10);
    delay(1);

    minu = minu / 10;

    // turn second number
    digitalWrite(24, HIGH);
    digitalWrite(25, LOW);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    cyfra(minu % 10);
    delay(1);

    // turn third number
    digitalWrite(24, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
    cyfra(hours % 10);
    delay(1);
    hours = hours / 10;

    // turn fourth number
    digitalWrite(24, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    cyfra(hours % 10);
    delay(1);
    i++;

    // seconds measuring
    if (busy == 0 && i == 250)
    {
        sec = sec + 1;
        i = 0;
    }

    if (busy == 1)
    {
        i = 0;
    }
}

// function to number display
void cyfra(int cyfra)
{
    clean();
    digitalWrite(7, HIGH);

    // choosing and displaying number
    switch (cyfra)
    {
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
void clean()
{
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
}