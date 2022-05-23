#include <OneWire.h> // adding thermometer library

// ambient temperature: 24.31 degree
// heating temperatore: 31.56 degree

float dane[30];
int index = 0;
int len = 0;

OneWire ds(0); // thermometer initialization

void setup(void)
{
    Serial.begin(9600); // serial port initialization
    pinMode(1, OUTPUT); // setting output for heating
}

void loop(void)
{
    // OneWire magic start
    byte i;
    byte present = 0;
    byte type_s = 0;
    byte data[12];
    byte addr[8];
    float celsius;

    if (!ds.search(addr))
    {
        ds.reset_search();
        delay(250);
        return;
    }

    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);
    delay(1000); // maybe 750ms is enough, maybe not

    present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);

    for (i = 0; i < 9; i++)
    {
        data[i] = ds.read();
    }

    int16_t raw = (data[1] << 8) | data[0];
    if (type_s)
    {
        raw = raw << 3;
        if (data[7] == 0x10)
        {
            raw = (raw & 0xFFF0) + 12 - data[6];
        }
    }
    else
    {
        byte cfg = (data[4] & 0x60);
        if (cfg == 0x00)
            raw = raw & ~7;
        else if (cfg == 0x20)
            raw = raw & ~3;
        else if (cfg == 0x40)
            raw = raw & ~1;
    }

    // OneWire magic end

    celsius = (float)raw / 16.0; // converting to temperature
    dane[index] = celsius;       // saving last 30 measurements
    len = max(index + 1, len);
    index = (index + 1) % 30;

    if (celsius < 28)
    {
        digitalWrite(0, HIGH); // turning on heating
    }
    else if (celsius > 28)
    {
        digitalWrite(0, LOW); // turning off heating
    }

    Serial.println("Oczekiwana: 30 Celcjusza ");
    Serial.print("Aktualna: ");
    Serial.println(celsius);
    Serial.print("Srednia tmp: ");
    Serial.println(srednia(dane, len));

    Serial.println();
    Serial.println();
}

// function counting average temperature
float srednia(float *dane, int len)
{
    double sum = 0;
    for (int i = 0; i < len; i++)
        sum += array[i];
    return ((float)sum) / len;
}
