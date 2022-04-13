// on board in labolatory HIGH means OFF

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

    // set input pins for buttons
    pinMode(29, INPUT_PULLUP);
    pinMode(30, INPUT_PULLUP);
    pinMode(31, INPUT_PULLUP);
}

int set = 0;
int start = 0;
int stops = 0;
int counter1 = 0;
int run = 0;
int czas = 150;
int running = 0;
int setted = 0;

void loop()
{
    // setting up time
    if (running == 0)
    {
        if (set == 0 && pressed(29) == 1)
        {
            counter1 = czas;
            set = 1;
            start = 0;
            setted = 1;
        }
        if (set == 1 && pressed(29) == 0)
        {
            set = 0;
        }

        if (setted == 1)
        {
            if (start == 0 && pressed(30) == 1)
            {
                run = 1;
                start = 1;
                stops = 0;
                running = 1;
            }
        }

        show(counter1);
    }

    // runing timer
    if (running == 1)
    {
        if (run == 1)
        {
            counter1--;
        }

        if (counter1 == 0)
        {
            run = 0;
        }

        int i = 0;
        for (i; i < 250; i++)
        {
            // stopping timer
            if (stops == 0 && pressed(31) == 1)
            {
                stops = 1;
                start = 0;
                counter1 = 0;
                running = 0;
                setted = 0;
                break;
            }
            show(counter1);
        }
    }
}

// function displaying numbers
void show(int counter1)
{
    int minu = counter1 / 60;
    int sec = counter1 % 60;

    // turn first number
    digitalWrite(24, LOW);
    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    cyfra(sec % 10);
    delay(1);

    sec = sec / 10;

    // turn second number
    digitalWrite(24, HIGH);
    digitalWrite(25, LOW);
    digitalWrite(26, HIGH);
    digitalWrite(27, HIGH);
    cyfra(sec);
    delay(1);

    // turn third number
    digitalWrite(24, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
    cyfra(minu % 10);
    delay(1);
    minu = minu / 10;

    // turn fourth number
    digitalWrite(24, HIGH);
    digitalWrite(25, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    cyfra(minu);
    delay(1);
}

// function detecting button pressed
int pressed(int pin)
{
    int press = 0;
    for (int i = 0; i < 100; i++)
    {
        if (digitalRead(pin) == 0)
        {
            press++;
        }
    }

    if (press == 100)
    {
        return 1;
    }
    else
    {
        return 0;
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
