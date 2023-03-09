# Smart Bedroom System
# Jonathan Fischman and Michael York

Date submitted for review: 3/9/23

Summary of behavior:
The system initializes, then runs through its main loop. This loop conatins the userInterfaceUpdate function, which is resonsible for most of the functions of the system. In the userInterfaceUpdate function, the ldr sensor is checked. It will display DAY or NIGHT on the LCD depending on the reading. If it detects darkness and the shades are in automatic mode, then the blinds will close. If it is light and the shades are in auto mode, the shades will open. The PIR sensor will sense motion. The display will show MOTION DETECTED or MOTION CEASED based on the reading. It will also turn on the lights when motion is detected, and turn them off when motion is no longer detected. The loop also checks if the shades and the lights are in manual or automatic mode based on the state of the SPDT switches. If in manual mode for either the lights or the shades, there are interrupt functions that will allow the lights or shades to be turned on and off with buttons.

Modules:
- display: initializes the display, allows strings to be written to the display. based on textbook code
- smart bedroom system: initializes the lights, servo, and user interface, updates the user interface. written based on textbook code with some modifications.
- servo: initializes the servo, opens and closes the shades. written based on lab exercise code.
- lights: initializes the lights, turns them on and off. written from scratch.
- user interface: implements the behaviors described above. written based on textbook code with some major modifications.
- ldr sensor: reads the sensor. written based on textbook code.
- motion sensor: initializes, reads, activates, and deactivates the sensor. based on textbook code.

Hardware and pins connected:
- servo: PF_8
- LED1: D10
- LED2: D11
- Switch 1: PE_3
- Switch 2: PF_7
- Button 1: PF_9
- Button 2: PG_1
- LDR sensor: A2
- PIR sensor: PG_0
- LCD Display: connected as shown in chapter 6 of textbook
- Potentiometer: connected to display, as shown in chapter 6 of textbook

Tests performed and results:
- covering the ldr sensor (while in automatic mode): shades close
- uncovering the ldr sensor (while in automatic mode): shades open
- moving in front of the pir sensor (while in automatic mode): lights turn on
- staying still in front of the pir sensor (while in automatic mode): lights turn off
- covering the ldr sensor (while in manual mode): nothing
- uncovering the ldr sensor (while in manual mode): nothing
- moving in front of the pir sensor (while in manual mode): nothing
- staying still in front of the pir sensor (while in manual mode): nothing
- switching the lights switch: changes from auto to manual mode or vice versa
- switching the shades switch: changes from auto to manual mode or vice versa
- pressing the lights button (while in manual mode): lights toggle between on/off
- pressing the lights button (while in auto mode): nothing
- pressing the shades button (while in manual mode): shades toggle between open/closed
- pressing the shades button (while in auto mode): nothing
