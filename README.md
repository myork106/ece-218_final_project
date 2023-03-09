# Smart Bedroom System
# Jonathan Fischman and Michael York

Date submitted for review: 3/9/23

Summary of behavior:
The system initializes, then runs through its main loop.
This loop conatins the userInterfaceUpdate function, which is resonsible for most of the functions of the system. In the userInterfaceUpdate function, the ldr sensor is checked. If it detects darkness and the shades are in automatic mode, then the blinds will close.
