# Arduino Motion Detection System

## Overview
This project uses an Arduino Uno and a PIR motion sensor to detect movement and also displays the last detected motion time on a 16×2 I²C LCD.

## Acknowledgements
The original PIR motion detection example was inspired by a tutorial from Circuit Magic on YouTube:
https://www.youtube.com/watch?v=FxaTDvs34mM

This project extends the original example through the integration of the following:
- Buzzer (auditory indicator)
- LCD 
- User-configurable time input
- Motion timestamp display

## Purpose 
The circuit serves as a simple security system, detecting motion and alarming users through both visual and sound indicators. It also utilizes a user-based time reference to display the time of the most recent detected motion on an LCD. 

## Features
- PIR motion detection
- LCD display
- User-entered reference time
- Calculates motion detection time using `millis()`
- LED indicator
- Buzzer

## Components
- Arduino Uno
- HC-SR501 PIR sensor
- 5V Buzzer
- LED
- 16×2 I²C LCD
- Breadboard
- Jumper wires

## How it works
1. Arduino calibrates the PIR sensor.
2. User enters the current time.
3. The system tracks elapsed time using `millis()`.
4. When motion is detected, the LCD shows the calculated detection time, and simultaneously, the LED and buzzer go off.

## How to Use
1. Upload the sketch to the Arduino using the Arduino IDE.
2. Wait approximately **30 seconds** while the PIR sensor calibrates.
3. Open **Tools → Serial Monitor** and set the baud rate to **9600**.
4. Enter the current time in the format `HH MM SS` (e.g., `14 30 00`) and press **Send**.
5. Once the time has been entered, the system will begin monitoring for motion. When motion is detected, the LCD will display the time of the last detected motion.

## Notes
- The circuit diagram uses a piezo buzzer symbol because Tinkercad does not have a dedicated 5 V active buzzer component.
