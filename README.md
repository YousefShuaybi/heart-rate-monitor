# 💓 Heart Rate & SpO2 Monitoring System

A biomedical monitoring system using Arduino and MAX30100 sensor for heart rate (BPM) and SpO2 calculation, with a real-time Processing GUI for visualization and audio feedback.

## 🧠 Project Overview

This project demonstrates a simplified yet complete biomedical device pipeline:

- **Data Acquisition**: using MAX30100 pulse oximeter sensor
- **Signal Processing**: on Arduino using custom C++ algorithm
- **Data Transmission**: via serial connection to PC
- **Visualization**: real-time ECG-like animation using Processing
- **Sound Feedback**: audible beep on each heartbeat

## 🛠️ Technologies Used

- **Arduino IDE** – for embedded C++ firmware
- **C++** – for signal processing logic (`spo2_algorithm.cpp`)
- **Processing** – for real-time GUI + sound
- **Serial Communication** – between Arduino and PC
- *** CHECK THE SERIAL NUMBER THAT YOU'RE CONNECTING YOUR ARDUINO ON, YOU CAN CHANGE IT IN THE PROCESSING CODE.
## 📦 Project Structure

```plaintext
/
├── finalcode.ino              # Main Arduino code
├── spo2_algorithm.cpp         # Heart rate + SpO2 processing logic (mocked)
├── spo2_algorithm.h
├── ecg_visualizer.pde         # Processing GUI (see above)
├── README.md
