#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "i2c.h"
#include "spi.h"
#include "uart.h"

void setup()
{
    // Inicjalizacja komunikacji szeregowej

    i2cMasterSetup();
    spiMasterSetup();
    uartMasterSetup();

    // Tworzenie zadania w FreeRTOS
    xTaskCreate(
        i2cMaster,    // Funkcja, która ma być wykonana jako zadanie
        "i2c Master", // Nazwa zadania
        128,          // Rozmiar stosu dla zadania
        NULL,         // Parametry przekazywane do zadania
        1,            // Priorytet zadania
        NULL          // Uchwyt zadania
    );
    xTaskCreate(
        spiMaster,    // Funkcja, która ma być wykonana jako zadanie
        "spi master", // Nazwa zadania
        128,          // Rozmiar stosu dla zadania
        NULL,         // Parametry przekazywane do zadania
        1,            // Priorytet zadania
        NULL          // Uchwyt zadania
    );
    xTaskCreate(
        uartMaster,    // Funkcja, która ma być wykonana jako zadanie
        "uart master", // Nazwa zadania
        128,           // Rozmiar stosu dla zadania
        NULL,          // Parametry przekazywane do zadania
        1,             // Priorytet zadania
        NULL           // Uchwyt zadania
    );

    // Uruchomienie schedulera - od tego momentu zarządzanie przejmuje FreeRTOS
    vTaskStartScheduler();
}

void loop()
{
}