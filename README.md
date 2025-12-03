# ⚡ DC Microgrid Integration with Battery Storage Systems

A Smart Embedded System for Real-Time Monitoring and Source Selection

## 📌 Project Overview

This project implements a **DC Microgrid** using an **ESP32** microcontroller to monitor real-time voltages from **solar**, **wind**, and **battery** energy sources.
Based on the sensed voltages, the system **automatically switches** between power sources using a **relay module** to ensure uninterrupted supply.

The system also features:

* **LCD Display** for live voltage monitoring
* **Blynk IoT App** for remote monitoring
* **Cloud dashboard** for alerts & history tracking
* Efficient embedded logic for intelligent source selection

---

## 🎯 Objectives

* Monitor voltages from renewable energy sources in real-time
* Perform automatic source switching via relay
* Enable remote IoT monitoring using Blynk
* Provide an LCD interface for on-site visualization
* Build a reliable microgrid control prototype

---

## 🛠️ Hardware Components

* **ESP32 Development Board**
* **Relay Module (4-channel)**
* **Solar Panel (DC output)**
* **Wind Turbine Generator (DC output)**
* **Battery Storage (DC)**
* **Voltage Sensors** (0–25V or similar)
* **16x2 LCD Display** (with I2C module)
* Connecting wires, breadboard, power supply

---

## 🧰 Software & Tools

* **Arduino IDE**
* **Blynk IoT Platform**
* **ESP32 Board Manager**
* **Embedded C / Arduino C**
* **LCD I2C Library**
* **Blynk Library**

---

## 🔌 System Architecture

```
Solar Voltage Sensor ----\
                           --> ESP32 --> Relay Control --> Load
Wind Voltage Sensor  -----/
Battery Voltage Sensor ----/

ESP32 --> LCD (I2C)
ESP32 --> Blynk Cloud --> Mobile Dashboard
```

---

## 📡 Features

✔ Real-time measurement of Solar, Wind & Battery voltages
✔ Automatic relay switching based on voltage thresholds
✔ Local LCD display for real-time values
✔ Blynk app dashboard for remote monitoring
✔ Highly scalable — more sources can be added
✔ Low-cost and practical for microgrid learning

---

## 🧠 Working Principle

1. ESP32 continuously reads analog voltages from three sensors.
2. Code compares the voltage levels with predefined cut-off thresholds:

   * Highest available voltage is prioritized
   * Solar > Wind > Battery fallback logic
3. Relay switches automatically to select the best power source.
4. LCD shows current voltages & active source.
5. Blynk displays data remotely on smartphone.

---

## 📱 Blynk Dashboard

* Live voltage graph
* Current active power source
* System status notifications
* Cloud history logging

---

## 📷 Block Diagram

*(Add your own circuit diagram image here for more clarity)*

---

## 📂 Repository Structure

```
DC-Microgrid-Project/
│
├── README.md                         # Project overview, documentation
├── code.ino                          # Main ESP32 firmware (microgrid logic)
│
├── B_8.mp4                           # Demo video of DC microgrid
├── B_8.pdf                           # Presentation / explanation document
│
├── EEE_R21_UG_Project_Report_JYOTSHNA.docx   # Full project report (editable)
└── EEE_R21_UG_Project_Report_JYOTSHNA.pdf    # Final report (PDF version)


---

## 🚀 How to Run

1. Install ESP32 board in Arduino IDE
2. Install required libraries:

   * LiquidCrystal_I2C
   * Blynk
3. Configure Blynk Template ID & Auth Token
4. Upload the code to ESP32
5. Make connections as per schematic
6. Power up the system — live values appear on LCD & Blynk

---

## 🔧 Future Improvements

* Add **MPPT (Maximum Power Point Tracking)** algorithm
* Integrate **current sensors** for power calculation
* Battery SOC (State of Charge) estimation
* Implement **over-voltage & under-voltage protection**
* Add **Wi-Fi + Bluetooth fallback communication**
* Create a proper PCB for the system
* Integrate AI-based load prediction / source optimization

---

## 📜 License

This project is released under the **MIT License**.
Feel free to use and share.

---

## 🙌 Acknowledgements

This project was developed as part of an embedded systems learning initiative using **ESP32**, IoT, and renewable energy concepts.

---



