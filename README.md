# geiger-pulse-counter-minimal

An ultra-lightweight, optimized, and non-blocking Arduino/ESP32 framework to interface with a Geiger-Müller radiation counter tube. This code serves as a clean hardware-abstracted foundation for more advanced projects like True Random Number Generators (TRNG) or Radiation Monitors (CPM/µSv/h).

## 🚀 Features
* **Interrupt-driven (ISR):** Captures pulses instantly without delaying the main loop execution.
* **Zero bloatware:** Ultra-minimalist, extremely low memory footprint, no external libraries.
* **Multi-platform:** Out-of-the-box support for Arduino Uno, Nano, and ESP32.
* **Sequential logging:** Outputs data safely via Serial at `115200` baud.

## ⚙️ How It Works
1. **Hardware Interrupt (ISR):** Every time a radioactive particle hits the Geiger tube, the module generates a brief voltage drop. This triggers the `geigerISR()` function instantly via external hardware interrupts, bypassing the slower main loop.
2. **Non-blocking Flag:** The ISR does not process data or print to Serial (which would crash the micro-controller). It simply sets `pulseDetected` to true.
3. **Main Loop Processing:** The `loop()` handles the display and increments a 32-bit counter (`pulseCount`) to log each event sequentially (`detection 1`, `detection 2`, etc.).

## 🛠️ Hardware Setup

| Geiger Module Pin | Arduino Pin | Role / Notes |
| :--- | :--- | :--- |
| **VCC** | 5V (or 3.3V) | Positive power supply |
| **GND** | GND | Common ground |
| **INT / PULSE / VIN** | Digital Pin 3 | Interrupt signal (Triggers on `FALLING` edge) |

> ⚠️ **Technical Note:** Pin 3 (D3) is mandatory on Arduino Uno/Nano because it natively supports external hardware interrupts.

## 💻 Output Example
When a radioactive particle is detected, the Serial Monitor will display:
```text
Geiger Pulse Counter Ready...
detection 1
detection 2
detection 3
