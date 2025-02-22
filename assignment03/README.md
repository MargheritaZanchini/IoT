# IoT Temperature Monitoring and Control System

### 3rd Project for the IoT University Course (2024-2025) @ unibo, Cesena

This project implements an IoT system for temperature monitoring and window control with multiple interconnected (http, mqtt and serial) components.

## System Components

- **Temperature Monitoring System**: ESP32 temperature monitoring subsystem
- **Window Controller**: Arduino-based window controller subsystem 
- **Dashboard**: JavaFX frontend application for system monitoring and control
- **Control Unit**: Backend service that coordinates communication between subsystems

## Getting Started

To properly run the system, the subsystems need to be started in the following order:

1. Start the **Temperature Monitoring System** ESP32 device
   - Connect to computer / power supply
   - Upload the code to the ESP32

2. Start the **Window Controller** Arduino device
   - Connect to computer / power supply  
   - Upload the code to the Arduino board

3. Launch the **Dashboard** application

4. Finally, start the **Control Unit** backend service

5. Enjoy the project! **:)**

### Made with love by Marco Marrelli, Sofia Caberletti and Margherita Zanchini