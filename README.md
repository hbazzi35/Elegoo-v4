# Elegoo-v4
This is a program written for an Arduino powered Elegoo-v4 car.
## Program Purpose
This program allows the vehicle to follow a black line around a race track using 3 infrared sensors attached to the bottom of the car.
### How it works
The program checks to see if the sensors are reading within the specified threshold and if only the middle sensor is within the threshold the car will drive forward. The left and right sensor are used for sway mitigation to keep the car aligned with the 7mm thick black line at all times. If all 3 sensors show that they are on the black line this means they have crossed the start/finish line and have completed the lap. The program times out after the car has completed three laps.
