/*!
 * @file geiger_pulse_counter_minimal.ino
 * @brief Minimalist base code that counts and logs Geiger hardware pulses.
 * @see https://github.com/zeredbox/geiger-pulse-counter-minimal
 * 
 * @section Program_Description Program Description
 * This program is an ultra-minimalist framework for interfacing 
 * a Geiger-Müller counter tube with an Arduino or ESP32. 
 * 
 * @section License
 * This is free and unencumbered software released into the public domain (The Unlicense).
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this 
 * software for any purpose, commercial or non-commercial.
 * 
 * HOW IT WORKS:
 * 1. Hardware Interrupt (ISR): Every time a radioactive particle hits the Geiger tube, 
 *    the module generates a brief voltage drop. This triggers the `geigerISR()` function 
 *    instantly via external hardware interrupts, bypassing the slower main loop.
 * 2. Non-blocking Flag: The ISR does not process data or print to Serial (which would 
 *    crash the micro-controller). It simply sets `pulseDetected` to true.
 * 3. Main Loop Processing: The `loop()` handles the display and increments a 32-bit 
 *    counter (`pulseCount`) to log each event sequentially ("detection 1", "detection 2", etc.).
 * 
 * FUTURE PROJECTS EXTENSIONS:
 * This code can easily be upgraded into:
 * - A Radiation Monitor: Add a timer (`millis()`) to count pulses over 60 seconds to calculate CPM (Counts Per Minute) and µSv/h.
 * - A Quantum TRNG (True Random Number Generator): Measure the time interval between pulses using `micros()` to extract unpredictable random bits.
 */

/*!
 * @section Hardware_Setup Wiring Description
 * +------------------------+-------------------+----------------------------+
 * | Geiger Module Pin      | Arduino Pin       | Role / Notes               |
 * +------------------------+-------------------+----------------------------+
 * | VCC                    | 5V (or 3.3V)      | Positive power supply      |
 * | GND                    | GND               | Common ground              |
 * | INT / PULSE / VIN      | Digital Pin 3     | Interrupt signal (ISR)     |
 * +------------------------+-------------------+----------------------------+
 */

#if defined(ESP32)
#define DETECT_PIN D3
#else
#define DETECT_PIN 3
#endif

// Volatile flag to signal pulse detection from ISR to main loop
volatile bool pulseDetected = false;

// Counter for the total number of detections (up to 4,294,967,295)
unsigned long pulseCount = 0;

/**
 * @brief Hardware Interrupt Service Routine (ISR)
 * Executed instantly on every radiation impact.
 */
void geigerISR() {
  pulseDetected = true;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(DETECT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(DETECT_PIN), geigerISR, FALLING);
  
  Serial.println("Geiger pulse Counter ready...");
}

void loop() {
  // Check if a pulse was captured by the interrupt
  if (pulseDetected) {
    pulseDetected = false; // Reset the flag
    pulseCount++;          // Increment the detection counter

    // Print detection with its incrementing number
    Serial.print("detection ");
    Serial.println(pulseCount); 
  }
}
