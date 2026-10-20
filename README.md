# 📈 Vibration Monitoring System | Arduino → STM32 Custom PCB

A real-time vibration monitoring system built around the **MPU6050 accelerometer**, originally developed using an Arduino UNO and Python, and subsequently redesigned around an **STM32F103 microcontroller on a custom-designed PCB**.

The project explores embedded systems, sensor interfacing, digital signal processing, PCB design, and hardware debugging.

The original Arduino prototype successfully demonstrated vibration detection, signal filtering, threshold-based LED indication, and real-time Python visualization. The STM32 redesign aims to improve sampling consistency, timing control, and overall system flexibility while providing practical experience developing and validating custom embedded hardware.

**Current Status: Custom PCB manufactured, assembled, powered, and successfully programmed. Hardware bring-up completed; STM32 firmware development in progress.**

---

## 🎯 Project Overview

The project began as an experiment in vibration analysis using an Arduino UNO and MPU6050 accelerometer.

The initial implementation acquired accelerometer measurements, processed vibration data, applied filtering, and communicated results to a Python application for real-time visualization and data logging.

Although the prototype worked, I encountered limitations involving sampling consistency, timing accuracy, and flexibility in controlling the underlying hardware.

To address these limitations, I redesigned the system around an STM32F103C8T6 microcontroller and developed my first custom PCB using KiCad.

A major objective throughout this redesign was to learn directly from technical documentation rather than relying heavily on tutorials. This involved studying component datasheets, application notes, and the STM32 reference manual to understand peripheral configuration, clock circuitry, power distribution, communication interfaces, and PCB layout.

---

## 🚀 Project Development Status

| Stage | Status |
|---|---|
| Arduino + MPU6050 prototype | ✅ Complete |
| Vibration detection and filtering | ✅ Complete on Arduino |
| Python visualization and CSV logging | ✅ Complete on Arduino |
| STM32 schematic design | ✅ Complete |
| Custom PCB layout and design-rule verification | ✅ Complete |
| PCB manufacturing and assembly | ✅ Complete |
| Power rail verification | ✅ Complete |
| SWD communication and MCU identification | ✅ Complete |
| STM32 programming and debugging | ✅ Complete |
| Bare-metal GPIO configuration and LED blinking | ✅ Complete |
| External MPU6050 integration | 🔄 Upcoming |
| STM32 I²C firmware | 🔄 Upcoming |
| STM32 vibration acquisition and processing | 🔄 Planned |
| STM32-to-Python communication | 🔄 Planned |
| Physical board demonstration videos | 🔄 Coming soon |

---

## 🧠 Original Arduino Prototype

The first version of the system was developed using an Arduino UNO, MPU6050 sensor module, and Python.

### Features

- Real-time vibration measurements using the MPU6050 three-axis accelerometer
- High-pass filtering to reduce unwanted low-frequency components
- RMS smoothing for more stable vibration measurements
- Threshold-based LED indication
- Serial communication between Arduino and Python
- Real-time plotting of vibration magnitude and RMS values
- Timestamped CSV logging for further analysis
- Initial experimentation with FFT-based vibration analysis

### Hardware

- Arduino UNO
- MPU6050 accelerometer module
- Breadboard and jumper wires
- LED with current-limiting resistor
- USB connection for serial communication

### Arduino Connections

| Arduino Pin | Connection |
|---|---|
| 5V | MPU6050 module VCC |
| GND | MPU6050 GND |
| A4 | MPU6050 SDA |
| A5 | MPU6050 SCL |
| D8 | LED output |

### Software

**Arduino:** Acquires acceleration measurements, performs vibration-related calculations, applies filtering, and activates the LED when the configured vibration threshold is exceeded.

**Python:** Receives serial measurements, plots vibration magnitude and RMS values in real time, and saves measurement data for later analysis.

### Original Prototype Demonstration

[Watch the Arduino vibration monitoring demo](Demo/VibrationsMonitorDemo.mp4)

The demonstration uses a massage gun to introduce controlled vibrations at different intensity levels.

At lower vibration levels, the LED remains off. At higher vibration levels, the measured vibration exceeds the threshold and activates the LED.

The Python visualization displays the corresponding changes in vibration magnitude and RMS measurements.

---

## 🔧 STM32 Custom PCB Redesign

The second iteration replaces the Arduino development board with a custom PCB designed around the **STM32F103C8T6 ARM Cortex-M3 microcontroller**.

This redesign provides greater control over the hardware and creates a foundation for implementing more consistent sampling, hardware timers, sensor communication, and embedded signal processing.

### Hardware Features

| Component / Interface | Purpose |
|---|---|
| STM32F103C8T6 | Main ARM Cortex-M3 microcontroller |
| TPS7A2033 LDO | Regulated 3.3V power supply |
| 8 MHz external crystal | External clock source |
| USB Micro-B connector | USB connectivity and power input |
| USB ESD protection | Protection for USB data lines |
| SWD header | Programming and hardware debugging |
| UART header | Serial communication and debugging |
| I²C header | External MPU6050 sensor connection |
| Analog supply filtering | Filtering for the MCU analog power domain |
| BOOT0 selection switch | Boot mode configuration |
| Reset circuitry | MCU reset control |
| Status LEDs | Power indication and firmware-controlled output |

### Power Distribution

The PCB uses a dedicated 3.3V low-dropout regulator to supply the STM32 and associated circuitry.

The design includes local decoupling capacitors near the microcontroller power pins, bulk capacitance for supply stability, and filtering for the analog supply domain.

### Clock Circuitry

An 8 MHz external crystal and its supporting capacitors are included to provide an external clock option.

The STM32 can also operate using its internal oscillator, allowing firmware development and initial bring-up without requiring the external crystal to be configured.

### Programming and Debugging

A dedicated SWD header exposes the STM32 programming and debugging signals.

Using an ST-Link programmer and STM32CubeIDE, the microcontroller can be programmed, halted, inspected, and debugged directly on the custom PCB.

### Sensor Interface

The PCB includes an I²C header for connecting an external MPU6050 module.

This allows the sensor interface to be developed and tested independently before integrating vibration processing into the STM32 firmware.

---

## 🛠️ PCB Design and Manufacturing

The schematic and PCB layout were developed in **KiCad**.

The design process involved:

- Studying STM32 datasheets and reference documentation
- Selecting components and verifying footprints
- Designing the power distribution and decoupling networks
- Implementing clock, reset, boot, USB, and debugging circuitry
- Routing a two-layer PCB
- Considering return paths, trace routing, and placement of decoupling components
- Running electrical rule checks (ERC) and design rule checks (DRC)
- Preparing manufacturing files and a bill of materials
- Ordering and assembling the physical PCB

The boards were manufactured through **JLCPCB**, with additional manual soldering and hardware bring-up performed after delivery.

### PCB Design Files

The KiCad project files are available in the [`KiCad/`](KiCad/) directory.

These include:

- `.kicad_pro` — KiCad project configuration
- `.kicad_sch` — Complete electrical schematic
- `.kicad_pcb` — PCB layout and routing

The directory also contains PCB renders and schematic images for convenient viewing without KiCad.

---

## ⚡ Hardware Bring-Up and Validation

After receiving the manufactured PCB, I began testing the board before developing the full application firmware.

### Power Verification

Using a digital multimeter, I verified the board's power connections and regulated 3.3V supply.

The onboard power indicator LED also confirmed the presence of the regulated supply.

### SWD and Microcontroller Verification

Using an ST-Link programmer and STM32CubeProgrammer, I successfully established communication with the STM32F103.

The debugger identified the target microcontroller and was able to access its internal flash memory.

This confirmed that the microcontroller was powered, responsive, and accessible through the custom SWD interface.

### Hardware Debugging

During initial bring-up, the debugger could not establish communication with the microcontroller.

Investigation of the reset circuitry revealed an issue with the physical reset pushbutton footprint and its pin mapping, which caused the NRST signal to remain asserted.

After identifying and removing the problematic switch, SWD communication was successfully restored.

This was a valuable practical lesson in component footprint verification, PCB assembly, and systematic hardware fault isolation.

The board can currently be reset through the debugging interface or by power cycling.

### First Successful Firmware Test

After confirming SWD communication, I created a bare-metal STM32 project in STM32CubeIDE.

Rather than relying on automatically generated GPIO initialization code, I configured the necessary registers directly using the STM32 reference manual.

This involved:

- Enabling the GPIOC peripheral clock through the RCC register
- Configuring PC13 as a general-purpose output
- Accessing memory-mapped peripheral registers using C pointers
- Using bitwise operations to configure and control GPIO
- Implementing a software delay loop
- Flashing and executing the program through ST-Link

**Result: The onboard LED successfully blinks under firmware control.**

This verified the complete development path from writing and compiling firmware to programming and executing code on the custom STM32 PCB.

---

## 💻 STM32 Firmware Development

The STM32 firmware is currently under active development.

The initial milestone was establishing reliable programming and GPIO control, which has now been achieved.

The next stage is integrating the MPU6050 accelerometer through the external I²C header.

### Planned Firmware Milestones

1. Configure STM32 I²C communication.
2. Detect and initialize the MPU6050.
3. Read raw three-axis acceleration measurements.
4. Implement consistent sensor sampling using hardware timers.
5. Process acceleration measurements to calculate vibration magnitude and RMS values.
6. Reimplement threshold-based vibration detection.
7. Transmit measurements to a host computer for Python visualization.
8. Investigate FFT-based frequency-domain vibration analysis.

The objective is to progressively replace the functionality of the original Arduino prototype with firmware developed specifically for the STM32 platform.

### Development Approach

I am currently focusing on register-level programming to develop a deeper understanding of the STM32 peripherals, memory-mapped I/O, peripheral clock control, and embedded C.

This approach provides direct experience with the underlying microcontroller hardware before introducing higher-level abstraction libraries where appropriate.

---

## 📹 Physical PCB Demonstrations — Coming Soon

The custom PCB has completed its initial hardware bring-up, and the STM32 has been successfully programmed and tested with a blinking LED.

I am currently working on the firmware and preparing to integrate the external MPU6050 sensor.

**Videos demonstrating the physical PCB, successful firmware execution, sensor communication, and eventually real-time vibration monitoring will be uploaded as development progresses.**

These demonstrations will document the transition from the original Arduino prototype to the working custom STM32-based system.

---

## 📁 Repository Structure

```text
VibrationMonitor-MPU6050/
│
├── Arduino/
│   └── Original Arduino prototype firmware
│
├── Python/
│   └── Real-time plotting and data logging
│
├── KiCad/
│   ├── STM32_Vibrations_Monitor.kicad_pro
│   ├── STM32_Vibrations_Monitor.kicad_sch
│   ├── STM32_Vibrations_Monitor.kicad_pcb
│   └── KiCad Images/
│       ├── PCB_3D_Top_View.jpeg
│       ├── PCB_3D_Bottom_View.jpeg
│       ├── PCB_Design.jpeg
│       └── Schematic.jpeg
│
├── Demo/
│   └── Original Arduino demonstration
│
├── LICENSE
└── README.md
```

*STM32 firmware files and physical PCB demonstrations will be added as development continues.*

---

## 🧰 Tools and Technologies

**Hardware and PCB Design**
- KiCad
- STM32F103C8T6
- MPU6050 accelerometer
- JLCPCB manufacturing and assembly
- Digital multimeter and soldering equipment

**Embedded Development**
- Embedded C
- STM32CubeIDE
- STM32CubeProgrammer
- ST-Link / SWD
- Register-level peripheral configuration
- I²C, UART, and GPIO

**Software and Data Processing**
- Arduino IDE
- Python 3
- Matplotlib
- PySerial
- Digital filtering and RMS calculations
- FFT-based signal analysis

**Documentation and Version Control**
- GitHub
- STM32 reference manual and datasheets
- Component datasheets and application notes

---

## 📚 Key Learning Outcomes

This project has provided practical experience across both hardware and firmware development.

Some of the most valuable learning experiences have included:

- Designing a complete STM32-based embedded PCB from component documentation
- Understanding microcontroller power, reset, clock, and boot requirements
- Developing and verifying a PCB layout for manufacturing
- Performing first-time hardware bring-up and electrical measurements
- Diagnosing a physical PCB assembly and footprint issue
- Establishing reliable SWD communication
- Programming a custom STM32 board using ST-Link
- Writing bare-metal C firmware using memory-mapped peripheral registers
- Connecting hardware design decisions with actual firmware behavior

The next objective is to bring the complete vibration monitoring application onto the STM32 platform.

---

## 👨‍💻 Author

**Anoosh Zaidi**  
Computer Engineering Student  
Toronto Metropolitan University

This project is part of my ongoing exploration of embedded systems, PCB design, hardware debugging, and firmware development.

---

## 📜 License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.
