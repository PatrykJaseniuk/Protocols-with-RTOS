#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

#include "i2c.h"
#include "spi.h"
#include "uart.h"

void setup()
{
    // Inicjalizacja komunikacji szeregowej

    i2cSlaveSetup();
    spiSlaveSetup();
    uartSlaveSetup();

    // Tworzenie zadania w FreeRTOS
    xTaskCreate(
        i2cSlave,    // Funkcja, która ma być wykonana jako zadanie
        "i2c Slave", // Nazwa zadania
        128,         // Rozmiar stosu dla zadania
        NULL,        // Parametry przekazywane do zadania
        1,           // Priorytet zadania
        NULL         // Uchwyt zadania
    );
    xTaskCreate(
        spiSlave,    // Funkcja, która ma być wykonana jako zadanie
        "spi Slave", // Nazwa zadania
        128,         // Rozmiar stosu dla zadania
        NULL,        // Parametry przekazywane do zadania
        1,           // Priorytet zadania
        NULL         // Uchwyt zadania
    );
    xTaskCreate(
        uartSlave,    // Funkcja, która ma być wykonana jako zadanie
        "uart Slave", // Nazwa zadania
        128,          // Rozmiar stosu dla zadania
        NULL,         // Parametry przekazywane do zadania
        1,            // Priorytet zadania
        NULL          // Uchwyt zadania
    );

    // Uruchomienie schedulera - od tego momentu zarządzanie przejmuje FreeRTOS
    vTaskStartScheduler();
}

void loop()
{
    // Pusta pętla - wszystko zarządzane jest przez zadania FreeRTOS
}
