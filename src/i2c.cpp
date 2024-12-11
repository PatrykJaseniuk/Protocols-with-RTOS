#include "i2c.h"
#include <Wire.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

const int adres = 8;

void i2cMasterSetup()
{
    Wire.begin(); // Rozpocznij działanie jako master
    Serial.begin(9600);
}
void receiveEvent(int howMany);
void i2cSlaveSetup()
{
    Wire.begin(adres);            // Rozpocznij działanie jako slave z adresem 8
    Wire.onReceive(receiveEvent); // Rejestracja funkcji obsługi zdarzenia odbioru
    Serial.begin(9600);
}

void i2cMaster(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        const char message[] = "Hello form Master!";

        Wire.beginTransmission(adres);
        Wire.write(message); // Poprawna metoda wysyłania danych
        Wire.endTransmission();
        // Serial.print("I2C master send: ");
        // Serial.println(message);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Odczekaj 1000 ms
    }
};

void i2cSlave(void *pvParameters)
{
    // jezeli zadanie jest puste powstają błędy przy wypisywaniu na konsolę

    vTaskDelete(NULL);

    // for (;;)
    // {
    //     // Serial.print("witam");
    //     vTaskDelay(pdMS_TO_TICKS(1000)); // Odczekaj 1000 ms
    // }
}

void receiveEvent(int howMany)
{
    Serial.print("I2C slave received: ");
    while (Wire.available())
    {                         // Odbierz wszystkie bajty
        char c = Wire.read(); // Odczytaj bajt
        Serial.print(c);      // Wydrukuj na konsoli szeregowej
    }
    Serial.println();
}