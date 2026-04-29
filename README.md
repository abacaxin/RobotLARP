# RobotLARP

![Demo](docs/demo.gif)

RobotLARP is a real-time controlled robot built using an ESP32 and a Bluetooth controller.  
The project focuses on responsive motor control using simple, accessible hardware, with an emphasis on practical testing and iteration.

This repository documents the current working state of the system.

---

## Current State

The robot is fully controllable via a Bluetooth controller, with real-time input translated directly into motor movement.

At this stage, the system includes:

- ESP32 handling Bluetooth communication  
- Controller input mapped to motor commands  
- Dual DC motors driven through an H-bridge  
- Continuous real-time response to input  

The project is still under active development, but the core control loop and hardware setup are already functional and stable.

---

## Hardware Setup

- ESP32  
- 2x DC gear motors  
- H-bridge motor driver (L298N or compatible mini driver)  
- External power supply (battery)  
- Bluetooth controller (PS4 or compatible)

The motors are powered externally, while the ESP32 handles control logic and signal output.

---

## Wiring

The system follows a straightforward layout:

- ESP32 GPIOs → motor driver input pins  
- Motor driver output → motors  
- External power → motor driver  
- Common ground between ESP32 and motor driver  

A proper wiring diagram will be added to this repository to reflect the exact connections used.

---

## Control System

The ESP32 connects to the controller via Bluetooth and continuously reads input values.

These inputs are processed in real time and converted into motor control signals, allowing:

- Direction control  
- Speed variation (via PWM)  
- Immediate response to user input  

The focus is on minimizing delay and keeping control behavior predictable.

---

## Code Structure

The code is organized to keep responsibilities separated:

- Input handling (controller communication)  
- Control logic (mapping inputs to actions)  
- Motor control (GPIO + PWM output)  

This makes it easier to adjust behavior without rewriting the entire system.

---

## 3D Structure

The robot uses a simple physical structure designed for quick assembly and testing.

3D models and structural components will be included in this repository, representing the exact build used in the current version.

---

## Getting Started

Clone the repository:

```bash
git clone https://github.com/abacaxin/RobotLARP
```

Open it in Arduino IDE or PlatformIO, install the required libraries, and upload the code to the ESP32.

Make sure the hardware is correctly wired before powering the system.

---

## Notes on Libraries

This project relies on Bluetooth controller communication libraries compatible with the ESP32.

If you are unfamiliar with how controller pairing and input handling works, refer to the library documentation for deeper understanding, especially regarding connection behavior and input mapping.

---

## Development Status

This is an active project.  
The current version reflects a working control system, and updates will continue as testing evolves.

---

## Author

abacaxin
