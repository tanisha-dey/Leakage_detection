# Water Flow and Leakage Detection System

## Overview
This project implements a **Water Flow and Leakage Detection System** using an **Arduino microcontroller**, two **water flow sensors**, an **LCD display**, and an **alarm system** (buzzer & LED). The system continuously monitors water flow rates from two sensors and detects leakage based on differences in flow rate.

## Features
- **Water Flow Monitoring**: Displays real-time flow rates from two sensors on an LCD.
- **Leakage Detection**: Alerts the user via **LED and buzzer** when a leakage is detected.
- **LCD Display**: Shows real-time flow readings and leakage status.
- **Serial Monitoring**: Prints flow rates and leakage status for debugging.

## Components Required
- **Arduino Board**
- **2 Water Flow Sensors** (YF-S201 or similar)
- **16x2 LCD Display with I2C Module**
- **Buzzer**
- **LED**
- **Resistors & Wires**

## Circuit Connections
- **Water Flow Sensor 1** → **Digital Pin 2**
- **Water Flow Sensor 2** → **Digital Pin 3**
- **Buzzer** → **Digital Pin 10**
- **LED** → **Digital Pin 9**
- **LCD Display** → **I2C (SDA, SCL) Pins**

## Installation & Setup
1. **Connect the Components** as per the circuit diagram.
2. **Upload the Code** to your Arduino using the Arduino IDE.
3. **Monitor Flow Rates** on the LCD and Serial Monitor.
4. If leakage is detected, the buzzer and LED will turn on.

## Code Explanation
- **Interrupts** are used to count pulses from flow sensors.
- Flow rate is calculated using the formula:
  ```
  flowRate = (pulseCount / interval) * 1000 / 7.5;
  ```
  (where **7.5** is the pulse count per liter for the sensor)
- If the **flow rate difference exceeds 4 L/min**, leakage is detected.

## Future Enhancements
- Add a **wireless alert system** (via GSM or IoT integration).
- Store **historical data** for analysis.
- Implement **automatic valve shutoff** upon leakage detection.

