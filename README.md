# 🧭 Vibration Monitoring System (Arduino + MPU6050)

A real-time vibration detection system built using an **MPU6050 accelerometer**, **Arduino**, and **Python visualization**.  
The project measures vibration intensity, filters noise, and triggers an **LED indicator** when the vibration level crosses a set threshold.  
Designed, tested, and documented with full schematic and PCB layout in **KiCad**.

---

## 🧠 Features
- **Real-time vibration detection** using MPU6050 (3-axis accelerometer & gyroscope)  
- **High-pass filtering** and **RMS smoothing** for stable readings  
- **Threshold-based LED trigger** to indicate excessive vibration  
- **Python live plotting** with CSV logging for post-analysis  
- **Custom PCB design** created in KiCad  

---

## ⚙️ Hardware Setup
**Components Used:**
- Arduino UNO  
- MPU6050 sensor module  
- Breadboard + jumper wires  
- 1 LED + 220 Ω resistor  
- USB cable for serial communication  

**Connections:**
| Arduino Pin | MPU6050 Pin |
|--------------|-------------|
| 5V           | VCC         |
| GND          | GND         |
| A4           | SDA         |
| A5           | SCL         |
| D8           | LED Output  |

---

## 🧩 Repository Structure
VibrationMonitor-MPU6050/
│
├── Arduino/ → Arduino sketch (.ino)
├── Python/ → Python plotting script
├── KiCad/ → Schematic + PCB design files
│ ├── ArduinoVibrationsMonitor.kicad_sch
│ ├── ArduinoVibrationsMonitor.kicad_pcb
│ └── renders/ → PDF & image exports
│ ├── PCB_3D.png
│ ├── PCB_TopView.pdf
│ └── PCB_Silkscreen.pdf
│
├── Demo/ → Demo media
│ ├── demo_video.mp4
│ └── breadboard.jpg
│
└── README.md

---

## 🖥 Arduino & Python Integration
### Arduino
The Arduino reads accelerometer data and applies filtering to detect vibration magnitude.  
If the RMS value exceeds the threshold, the LED turns on.

### Python
The Python script reads serial data via USB, plots the **magnitude** and **RMS** values live,  
and saves the readings to a timestamped CSV file and PNG chart.

```bash
python mpu6050_live_plot.py
```

🎥 Demo

https://github.com/AnooshZ/VibrationMonitor-MPU6050/blob/main/Demo/VibrationsMonitorDemo.mp4

This demo shows the MPU6050 vibration monitoring system in action:

Massage gun at Level 1: Minor vibrations; LED remains off (below threshold).

Massage gun at Level 6: Intense vibrations; LED lights up as threshold is exceeded.

The Python graph displays live magnitude and RMS spikes in real time.

Breadboard Setup:


📐 KiCad Design

Schematic:
View PDF

Top View (F_Cu):
View PDF

Silkscreen View:
View PDF

3D PCB Render:


🧾 Data Logging Example
Time (ms)	mag (g)	rms (g)
1248	0.021	0.009
1312	0.035	0.011
1376	0.821	0.805
🧰 Tools & Technologies

Arduino IDE

KiCad 7

Python 3 (matplotlib, pyserial)

GitHub for version control and documentation

👨‍💻 Author

Anoosh Zaidi
3rd Year Computer Engineering – Toronto Metropolitan University
🔗 GitHub
 | LinkedIn

📜 License

This project is released under the MIT License.
You are free to use, modify, and distribute with proper attribution.

“Hardware speaks louder than code.”
– Practical Embedded Design Project by Anoosh Zaidi
