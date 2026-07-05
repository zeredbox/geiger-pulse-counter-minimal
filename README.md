# geiger-pulse-counter-minimal

An ultra-lightweight and non-blocking Arduino/ESP32 framework to interface with a Geiger-Müller radiation counter tube.
This code serves as a clean hardware-abstracted foundation for more advanced projects like Radiation Monitors (CPM/µSv/h) or True Random Number Generators (TRNG).

## 🚀 Features
* **Interrupt-driven (ISR):** Captures pulses instantly without delaying the main loop execution.
* **Ultra-minimalist:** Zero bloatware, low memory footprint.
* **Multi-platform:** Arduino Uno, Nano, and ESP32.
* **Sequential logging:** Outputs data via Serial at `115200` baud.

## 🛠️ Hardware Setup

| Geiger Module Pin | Arduino Pin | Role / Notes |
| :--- | :--- | :--- |
| **VCC** | 5V (or 3.3V) | Positive power supply |
| **GND** | GND | Common ground |
| **INT / PULSE** | Digital Pin 3 | Interrupt signal (Triggers on `FALLING` edge) |

> ⚠️ **Technical Note:** Pin 3 (D3) is mandatory on Arduino Uno/Nano because it natively supports external hardware interrupts.

## 💻 Output Example
When a radioactive particle is detected, the Serial Monitor will display:
```text
Geiger pulse counter ready...
detection 1
detection 2
detection 3
