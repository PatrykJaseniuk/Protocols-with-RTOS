#include <Arduino.h>

void uartMasterSetup()
{
    Serial.begin(9600); // Inicjalizacja UART z prędkością 9600 bps
};

void uartMaster(void *pvParameters)
{
    Serial.println("Hello from Master UART!"); // Wysyłanie wiadomości do Slave
    delay(1000);                               // Odczekaj 1 sekundę
};

void uartSlaveSetup()
{
    Serial.begin(9600); // Inicjalizacja UART z prędkością 9600 bps
};

void uartSlave(void *pvParameters)
{
    String receivedData = ""; // Bufor na odebrane dane

    for (;;)
    {
        // Sprawdzamy, czy przychodzą dane na UART
        while (Serial.available() > 0)
        {
            char receivedChar = Serial.read(); // Odczytaj znak
            if (receivedChar == '\n')
            { // Koniec wiadomości
                Serial.print("UART Slave received: ");
                Serial.println(receivedData); // Wyświetl odebraną wiadomość
                receivedData = "";            // Wyczyść bufor
            }
            else
            {
                receivedData += receivedChar; // Dodaj znak do bufora
            }
        }
    }
};