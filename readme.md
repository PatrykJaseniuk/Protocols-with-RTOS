
# Arduino Uno Communication Protocols with RTOS

This repository demonstrates the implementation of three communication protocols (**UART**, **I2C**, and **SPI**) between two Arduino Uno boards. Using RTOS for running all protocols simultaneously.
## Overview
This project demonstrates inter-communication between two Arduino Uno boards using three common communication protocols:

- **UART**: Asynchronous serial communication for text-based data transfer.
- **I2C**: Two-wire communication suitable for connecting multiple devices.
- **SPI**: High-speed, synchronous, full-duplex communication.

Each protocol is implemented with a clear separation of master and slave roles, enabling learning and experimentation.

## Protocols Implemented

### UART
UART communication is implemented using the Arduino's built-in `Serial` library. The master sends text-based messages to the slave, and the slave prints the received data on the serial monitor.

### I2C
I2C is implemented using the `Wire` library. The master sends a sequence of bytes, and the slave receives and processes the data. 

### SPI
SPI is implemented using the `SPI` library. The master initiates communication and sends data, while the slave responds or logs the received data.

## Hardware Connections

| Protocol | Master Pinouts         | Slave Pinouts          | Notes                                   |
|----------|------------------------|------------------------|-----------------------------------------|
| UART     | TX (D1) to RX (D0)     | RX (D0) to TX (D1)     | Connect GND of both boards.            |
| I2C      | A4 (SDA), A5 (SCL)     | A4 (SDA), A5 (SCL)     | Use pull-up resistors (4.7k\u03a9) if necessary. |
| SPI      | D10 (SS), D11 (MOSI), D12 (MISO), D13 (SCK) | D10 (SS), D11 (MOSI), D12 (MISO), D13 (SCK) | Connect GND of both boards.            |

## How to run 🚀

To streamline development and simplify dependency management, we use PlatformIO. Below are the steps to configure and run the project:

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/arduino-communication.git
   ```
2. Ensure you have PlatformIO installed.
3. connect Arduino Unos to usb. If necessary update 'upload_port' in 'platformio.ini':
4. Build and upload to both devices simultaneously: 
```
pio run -t upload
```
6. Use the serial monitor to see what is sended:
   - For Master: `pio device monitor -e master`
   - For Slave: `pio device monitor -e slave`