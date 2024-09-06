# Obstacle Avoidance Robot

### Project Description
The obstacle avoidance robot was built as a DIY project, implementing obstacle avoidance algorithms using HC-SR04 ultrasonic sensor. The robot moves autonomously, analyzing its surroundings and making decisions to change direction when obstacles are detected. The project uses an ATmega328PU microcontroller and a custom-designed, hand-etched PCB. The robot moves thanks to two DC motors driving the rear wheels and measures distances to make decisions about direction changes. 


### Components:
#### ATmega328PU Microcontroller: 
Manages all the robot's logic, processing data from sensors and controlling movement.
#### 16 MHz Crystal Oscillator: 
Provides precise timing for the microcontroller.
#### HC-SR04 Ultrasonic Sensor: 
Responsible for detecting obstacles and measuring distances.
#### SG-90 Micro Servo: 
Allows the sensor to rotate left and right, expanding the robot's field of view.
#### L293D Motor Driver (H-Bridge): 
Controls two DC motors that drive the robot's rear wheels.
#### L7805CV Voltage Regulator: 
Converts 9V to 5V, supplying power to the entire system.
#### LED: 
Indicates obstacle detection by the sensor.
#### Power Supply: 
Six AA batteries provide a common power source for both the mechanical and logical systems.
#### USB UART Converter: 
The outputs of the appropriate USB UART converter pins have been routed from the circuit, enabling communication between the microcontroller and a computer, displaying results on the screen, and making code adjustments.


![DF2069E8-E1ED-483F-A445-7B14EE55139C_1_105_c](https://github.com/user-attachments/assets/8a0dca5f-e525-43ab-a758-a70ad53ba8a1)


