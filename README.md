# Arduino IR Chronograph with OLED Display, Buzzer & Mode Selector

This project is a DIY optical chronograph built with Arduino, using four infrared sensors to measure the time it takes for an object to travel a fixed distance (4 cm by default).

With a built-in OLED display, a buzzer for feedback, and a button-based mode selector, you can easily measure speed in multiple units — all in a compact, portable device.

# Features

1. Four IR beam sensors to detect start and stop

2. OLED display for clear readouts

3. Audible feedback via buzzer 

4. Button-controlled mode selection:
   - m/s (meters per second)
   - ft/s (feet per second)
(More units can be added easily!)

5. Auto-reset ready for the next measurement

# Hardware Required
Component |	Quantity
- Arduino  Nano	1
- IR Emitter 4
- IR Receiver	4
- OLED Display (SSD1306, I2C)	1
- Push button	1
- Buzzer (active or passive)	1
- Jumper wires & breadboard	as needed

# How It Works
Object breaks the first IR beam → Arduino records the start time.

Object breaks the second IR beam → Arduino records the stop time.

The program calculates:

Elapsed time between sensors

Speed based on the known distance (default: 4 cm)

The results are displayed on the OLED, with speed in the selected unit.

Press the button to switch units or to return to the unit selection menu for the next measurement.
