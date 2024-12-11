#include <spi.h>
#include <SPI.h>
#include <Arduino_FreeRTOS.h>
#include <CircularBuffer.h>

// -----Master-----
void spiMasterSetup()
{
    Serial.begin(9600);                  // Sets pin 7 as Output
    SPI.begin();                         // Begins the SPI commnuication
    SPI.setClockDivider(SPI_CLOCK_DIV8); // Sets clock for SPI communication at 8 (16/8=2Mhz)
    digitalWrite(SS, HIGH);              // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
}

void spiMaster(void *pvParameters)
{
    const char msg[] = "Witam Państwa!";
    for (;;)
    {
        digitalWrite(SS, LOW); // Starts communication with Slave connected to master
        for (int i = 0; i < sizeof(msg); i++)
        {
            SPI.transfer(msg[i]);
            delay(10); // 1. bez tego występują problemy. Zamiast delay mogę spowolnić zegar SPI (zwiększyć dzielnik)
        }
        // Serial.print("SPI master send: ");
        // Serial.println(msg);
        delay(100);
    }
}

// -----Slave-----
CircularBuffer<char, 100> buffer; // nie może byc volatile
volatile bool isbuforReadyForRead = false;

ISR(SPI_STC_vect) // Inerrrput routine function
{
    char c = SPDR;
    buffer.push(c);
    if (c == '\0')
    {
        isbuforReadyForRead = true;
    }
    // Serial.print(c);
    // Sets received as True
}

void spiSlaveSetup()
{
    Serial.begin(9600);
    pinMode(MISO, OUTPUT); // Sets MISO as OUTPUT (Have to Send data to Master IN
    SPCR |= _BV(SPE);      // Turn on SPI in Slave Mode
    SPI.attachInterrupt(); // Interuupt ON is set for SPI commnucation
}

void spiSlave(void *pvParameters)
{
    for (;;)
    {
        Serial.print(""); // bez tego nie wypisuje na konsoli. Dlaczego ?
        // Serial.println(isbuforReadyForRead);
        if (isbuforReadyForRead)
        {
            Serial.print("SPI slave received: ");

            while (!buffer.isEmpty())
            {
                noInterrupts();              // bez noIterups powstaja błędy.
                char kasek = buffer.shift(); // buffer powinien być volatile
                interrupts();

                if (kasek != '\0')
                {
                    Serial.print(kasek);
                }
                else
                {
                    isbuforReadyForRead = false;
                    Serial.println();
                }
            }
        }
    }
}
