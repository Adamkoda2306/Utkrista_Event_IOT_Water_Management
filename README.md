<div align="center">

<h1>💧 IoT Water Quality Monitoring & Management System</h1>
<h3>Real-Time IoT Solution for Water Safety — From Sensor to Smartphone</h3>

<br/>

🥈 **Runner-Up — Project Competition** 🥈

<br/>

[![Platform](https://img.shields.io/badge/Hardware-Arduino%20%2B%20NodeMCU-teal?style=for-the-badge&logo=arduino)](https://www.arduino.cc/)
[![Firebase](https://img.shields.io/badge/Cloud-Firebase%20Realtime%20DB-orange?style=for-the-badge&logo=firebase)](https://firebase.google.com/)
[![Flutter](https://img.shields.io/badge/Mobile-Flutter-blue?style=for-the-badge&logo=flutter)](https://flutter.dev/)
[![Web](https://img.shields.io/badge/Web-GitHub%20Pages-black?style=for-the-badge&logo=github)](https://pages.github.com/)
[![IoT](https://img.shields.io/badge/Type-IoT%20Solution-green?style=for-the-badge)](https://en.wikipedia.org/wiki/Internet_of_things)
[![License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)](LICENSE)

<br/>

> **An end-to-end IoT pipeline that transforms raw sensor readings into life-saving water safety decisions —**  
> monitoring pH, turbidity, dissolved oxygen, temperature, and conductivity  
> in real time, from any location, on any device.

<br/>

---

</div>

## 📌 Table of Contents

- [🏆 Award](#-award)
- [🌊 Overview](#-overview)
- [❗ Problem Statement](#-problem-statement)
- [🎯 Objectives](#-objectives)
- [🏗 System Architecture](#-system-architecture)
- [⚙️ Working Principle](#️-working-principle)
- [📡 Parameters Monitored](#-parameters-monitored)
- [📂 Project Structure](#-project-structure)
- [🔬 Water Quality Classification](#-water-quality-classification)
- [📱 Flutter Mobile App](#-flutter-mobile-app)
- [🌐 Web Dashboard](#-web-dashboard)
- [✨ Key Features](#-key-features)
- [🛠 Technical Stack](#-technical-stack)
- [🗂 Firebase Data Structure](#-firebase-data-structure)
- [🚀 Getting Started](#-getting-started)
- [🌍 Applications](#-applications)
- [📜 License](#-license)

---

## 🏆 Award

<div align="center">

| 🥈 Runner-Up — Project Competition |
|:---:|
| *Recognized for innovation in real-time IoT-based environmental monitoring* |

</div>

---

## 🌊 Overview

The **Smart Water Quality Monitoring and Management System** is a fully integrated IoT solution that continuously monitors water quality across multiple locations and delivers real-time insights to users — anywhere, anytime.

The system combines **embedded hardware** (Arduino + NodeMCU), **cloud infrastructure** (Firebase), and **cross-platform frontends** (Flutter + Web) into a seamless pipeline that eliminates the need for costly manual water testing.

```
  Sensors ──▶ Arduino ──▶ NodeMCU ──▶ Firebase ──▶ Flutter App
                                               └──▶ Web Dashboard
```

Water quality is automatically classified as **🟢 Safe**, **🟡 Warning**, or **🔴 Unsafe** based on WHO-aligned sensor thresholds — enabling instant action when contamination is detected.

---

## ❗ Problem Statement

Traditional water quality testing is:

| Challenge | Impact |
|-----------|--------|
| 🧪 Manual sample collection | Time-consuming, labor-intensive |
| 🔬 Laboratory analysis | Expensive, not scalable |
| ⏳ Delayed results | Contamination spreads before detection |
| 📍 Location-bound | No remote monitoring capability |
| 🔁 Not continuous | Gaps between tests create risk windows |

> **This project solves all of the above** — providing automated, real-time, cost-effective, and remotely accessible water quality monitoring, 24/7.

---

## 🎯 Objectives

- ✅ Monitor water quality **in real time** without manual intervention
- ✅ Measure **5 critical water parameters** simultaneously
- ✅ Store all sensor data securely on the **cloud**
- ✅ Provide remote monitoring via **mobile and web** applications
- ✅ **Classify water quality automatically** using threshold-based logic
- ✅ Reduce manual inspection efforts and operational costs
- ✅ Enable **data-driven decision making** for water management authorities

---

## 🏗 System Architecture

```
┌──────────────────────────────────────────────────────────────────────┐
│                         SENSOR LAYER                                 │
│                                                                      │
│  ┌──────────┐ ┌───────────┐ ┌──────┐ ┌──────────┐ ┌─────────────┐    │
│  │pH Sensor │ │Turbidity  │ │  DO  │ │   Temp   │ │Conductivity │    │
│  │          │ │  Sensor   │ │Sensor│ │  Sensor  │ │   Sensor    │    │
│  └────┬─────┘ └─────┬─────┘ └──┬───┘ └────┬─────┘ └──────┬──────┘    │
└───────┴─────────────┴──────────┴──────────┴──────────────┴───────────┘
                                  │
                                  ▼
┌─────────────────────────────────────────────────────────────────────┐
│                       PROCESSING LAYER                              │
│                                                                     │
│               ┌──────────────────────────┐                          │
│               │       Arduino Uno        │                          │
│               │  · Reads all sensors     │                          │
│               │  · Serial communication  │                          │
│               └────────────┬─────────────┘                          │
│                            │                                        │
│               ┌────────────▼─────────────┐                          │
│               │     NodeMCU ESP8266      │                          │
│               │  · Wi-Fi connectivity    │                          │
│               │  · Firebase uplink       │                          │
│               └────────────┬─────────────┘                          │
└────────────────────────────┼────────────────────────────────────────┘
                             │  Wi-Fi
                             ▼
┌────────────────────────────────────────────────────────────────────┐
│                        CLOUD LAYER                                 │
│                                                                    │
│               ┌────────────────────────────┐                       │
│               │  Firebase Realtime Database│                       │
│               │  Utkrista_IOT/             │                       │
│               │    Devices/                │                       │
│               │      Device_ID/            │                       │
│               │        AreaName            │                       │
│               │        SensorValues        │                       │
│               └────────────┬───────────────┘                       │
└────────────────────────────┼───────────────────────────────────────┘
                             │
              ┌──────────────┴──────────────┐
              ▼                             ▼
┌─────────────────────┐         ┌───────────────────────┐
│   Flutter Mobile    │         │    Web Dashboard      │
│   Application       │         │  (GitHub Pages)       │
│                     │         │                       │
│  · Live readings    │         │  · Live readings      │
│  · Status colors    │         │  · Status indicators  │
│  · Multi-device     │         │  · Area-wise view     │
└─────────────────────┘         └───────────────────────┘
```

---

## ⚙️ Working Principle

### Step 1 — 📡 Data Acquisition
Sensors connected to Arduino continuously measure 5 water quality parameters from the water source.

### Step 2 — 🧮 Data Processing
Arduino reads analog/digital sensor values, processes them, and forwards structured data to the NodeMCU via serial communication.

### Step 3 — ☁️ Cloud Communication
NodeMCU connects to Wi-Fi and uploads sensor readings to **Firebase Realtime Database** in near real-time.

### Step 4 — 🗄 Data Storage
Firebase organizes data hierarchically for multi-device, multi-location management:

```
Utkrista_IOT
  └── Devices
        └── Device_ID
              ├── AreaName        ← Location label
              └── SensorValues
                    ├── pH
                    ├── Turbidity
                    ├── DO
                    ├── Temperature
                    └── Conductivity
```

### Step 5 — 📊 Visualization
Both the Flutter app and web dashboard fetch live data from Firebase and display readings with automatic quality classification.

---

## 📂 Project Structure

```
Utkrista_Event_IOT_Water_Management/
│
├── app.js                           # Web dashboard logic and Firebase integration
├── index.html                       # Web dashboard interface
├── style.css                        # Dashboard styling
├── README.md                        # Project documentation
│
├── Utkrista_IOT_Event_Water_Management_FIrebase/
│   └── Utkrista_IOT_Event_Water_Management_FIrebase.ino
│       # Arduino + NodeMCU firmware for sensor acquisition and Firebase upload
│
├── Utkrista_IOT_WMS/
│   └── utkrista_iot_wms/
│       │
│       ├── lib/
│       │   ├── main.dart            # Flutter application entry point
│       │   ├── model/
│       │   │   └── devices.dart     # Device data model
│       │   └── pages/
│       │       ├── homepage.dart    # Dashboard screen
│       │       └── secondpage.dart  # Device details screen
│       │
│       ├── assets/
│       │   └── images/
│       │       └── water.png        # Application assets
│       │
│       ├── android/                 # Android platform configuration
│       ├── ios/                     # iOS platform configuration
│       ├── test/                    # Flutter test files
│       ├── pubspec.yaml             # Flutter dependencies
│       └── README.md                # Mobile application documentation
│
└── Firebase Realtime Database
    └── Utkrista_IOT/
        └── Devices/
            └── Device_ID/
                ├── AreaName
                └── SensorValues/
                    ├── pH
                    ├── Turbidity
                    ├── DO
                    ├── Temperature
                    └── Conductivity

```

---

## 📡 Parameters Monitored

| # | Parameter | Unit | Purpose |
|---|-----------|------|---------|
| 1 | **pH Level** | pH units | Measures water acidity or alkalinity |
| 2 | **Turbidity** | NTU | Measures water clarity and suspended particles |
| 3 | **Dissolved Oxygen (DO)** | mg/L | Indicates oxygen availability for aquatic life |
| 4 | **Temperature** | °C | Affects chemical reactions and DO levels |
| 5 | **Conductivity** | µS/cm | Indicates dissolved salts and mineral content |

---

## 🔬 Water Quality Classification

The system evaluates all parameters simultaneously against WHO-aligned thresholds and assigns one of three status levels:

```
┌───────────────────────────────────────────────────────────────┐
│                   CLASSIFICATION LOGIC                        │
├──────────────┬────────────────────────────────────────────────┤
│  🟢 SAFE     │  ALL parameters within safe limits             │
│              │  pH: 6.5–8.5                                   │
│              │  Turbidity: < 5 NTU                            │
│              │  DO: > 6 mg/L                                  │
│              │  Temperature: 5°C – 25°C                       │
│              │  Conductivity: < 1500 µS/cm                    │
├──────────────┼────────────────────────────────────────────────┤
│  🟡 WARNING  │  One or more values approaching unsafe limits  │
│              │  Early alert — action recommended              │
├──────────────┼────────────────────────────────────────────────┤
│  🔴 UNSAFE   │  One or more parameters exceed safe limits     │
│              │  Immediate action required                     │
└──────────────┴────────────────────────────────────────────────┘
```

---

## 📱 Flutter Mobile App

<div align="center">

| Feature | Description |
|---------|-------------|
| 🔴🟡🟢 **Color-Coded Status** | Instant visual feedback on water safety |
| 📊 **Live Dashboard** | Real-time sensor readings per device |
| 📍 **Area Name Display** | Location-tagged monitoring |
| 🔄 **Auto-Update** | Firebase listener for live data sync |
| 🗺 **Multi-Device Support** | Switch between all connected monitoring stations |
| 🎨 **Modern UI** | Clean, responsive design with easy navigation |

</div>

### App Display Per Device

```
┌────────────────────────────────┐
│  📍 Area: River Zone North     │
│  Status: 🟢 SAFE               │
│ ────────────────────────────── │
│  pH           │  7.2           │
│  Turbidity    │  3.1 NTU       │
│  DO           │  7.5 mg/L      │
│  Temperature  │  22°C          │
│  Conductivity │  820 µS/cm     │
└────────────────────────────────┘
```

---

## 🌐 Web Dashboard

Deployed on **GitHub Pages** for public access — no installation required.

### Features

- 🔴🟡🟢 Color-coded status indicators per monitoring station
- 📡 Direct Firebase Realtime Database synchronization
- 📍 Area-wise display with all 5 sensor values
- 🌍 Accessible from any browser, anywhere in the world
- 📱 Responsive layout for both desktop and mobile browsers

---

## ✨ Key Features

| Feature | Details |
|---------|---------|
| ⏱ **Real-Time Monitoring** | Continuous sensing, no manual collection |
| ☁️ **Cloud Storage** | Centralized Firebase database |
| 📱 **Mobile Access** | Flutter app for Android & iOS |
| 🌐 **Web Access** | GitHub Pages dashboard |
| 🤖 **Auto Classification** | Instant Safe / Warning / Unsafe assessment |
| 📍 **Multi-Location** | Monitor multiple water sources simultaneously |
| 📈 **Scalable** | Easily add more devices and locations |
| 💰 **Cost-Effective** | Arduino + NodeMCU vs. expensive monitoring equipment |

---

## 🛠 Technical Stack

<div align="center">

| Layer | Technology |
|-------|-----------|
| **Microcontroller** | Arduino Uno |
| **Wi-Fi Module** | NodeMCU ESP8266 |
| **Sensors** | pH, Turbidity, DO, Temperature, Conductivity |
| **Cloud Database** | Firebase Realtime Database |
| **Mobile App** | Flutter (Dart) |
| **Web Dashboard** | HTML, CSS, JavaScript |
| **Web Hosting** | GitHub Pages |
| **Backend** | Node.js |
| **Version Control** | Git & GitHub |

</div>

---

## 🗂 Firebase Data Structure

```json
{
  "Utkrista_IOT": {
    "Devices": {
      "Device_001": {
        "AreaName": "River Zone North",
        "SensorValues": {
          "pH": 7.2,
          "Turbidity": 3.1,
          "DO": 7.5,
          "Temperature": 22.0,
          "Conductivity": 820
        }
      },
      "Device_002": {
        "AreaName": "Lake Zone East",
        "SensorValues": {
          "pH": 6.1,
          "Turbidity": 12.4,
          "DO": 4.2,
          "Temperature": 28.0,
          "Conductivity": 1800
        }
      }
    }
  }
}
```

---

## 🚀 Getting Started

### Prerequisites

#### Hardware Required
- Arduino Uno
- NodeMCU ESP8266
- pH Sensor Module
- Turbidity Sensor Module
- Dissolved Oxygen (DO) Sensor
- DS18B20 Temperature Sensor
- Conductivity Sensor
- Power Supply Unit
- Jumper wires & breadboard

#### Software Required
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Flutter SDK](https://flutter.dev/docs/get-started/install)
- [Node.js](https://nodejs.org/)
- Firebase Account

---

### Step 1 — Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Create a new project
3. Enable **Realtime Database**
4. Set database rules:
```json
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```
5. Copy your Firebase config credentials

---

### Step 2 — Arduino + NodeMCU Setup

1. Open Arduino IDE
2. Install required libraries:
   - `ESP8266WiFi`
   - `FirebaseESP8266`
   - `OneWire`, `DallasTemperature` (for temperature sensor)
3. Flash the firmware to NodeMCU with your Wi-Fi credentials and Firebase URL:
```cpp
#define WIFI_SSID     "Your_WiFi_SSID"
#define WIFI_PASSWORD "Your_WiFi_Password"
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret"
```
4. Connect sensors to Arduino as per the circuit diagram
5. Upload the sketch and power on the device

---

### Step 3 — Flutter Mobile App

```bash
# Clone the repository
git clone https://github.com/Adamkoda2306/Utkrista_Event_IOT_Water_Management.git
cd Utkrista_Event_IOT_Water_Management/Utkrista_IOT_WMS

# Install dependencies
flutter pub get

# Add Firebase configuration
# Place google-services.json in android/app/
# Place GoogleService-Info.plist in ios/Runner/

# Run the app
flutter run
```

---

### Step 4 — Web Dashboard

The web dashboard is deployed on GitHub Pages and can be accessed directly.

To run locally:
```bash
# Open index.html in your browser
# Or use a local server:
npx serve .
```

Update your Firebase config in `index.html`:
```javascript
const firebaseConfig = {
  apiKey: "YOUR_API_KEY",
  authDomain: "YOUR_PROJECT.firebaseapp.com",
  databaseURL: "https://YOUR_PROJECT.firebaseio.com",
  projectId: "YOUR_PROJECT_ID"
};
```

---

## 🌍 Applications

| Domain | Use Case |
|--------|----------|
| 🏙 **Smart Cities** | Municipal water supply monitoring |
| 🚰 **Drinking Water** | Safe water verification at treatment plants |
| 🌾 **Agriculture** | Irrigation water quality management |
| 🐟 **Aquaculture** | Fish farming pond monitoring |
| 🏭 **Industrial** | Effluent and process water monitoring |
| 🌿 **Environmental** | River, lake, and reservoir health tracking |
| 💧 **Water Treatment** | Real-time process optimization |

---

## 🏅 Achievements

- 🥈 **Runner-Up** at project competition — recognized for end-to-end IoT innovation
- 🔗 Integrated 5 sensor types with Arduino + NodeMCU seamlessly
- ☁️ Implemented scalable Firebase cloud architecture for multi-device management
- 📱 Built a production-ready Flutter mobile application
- 🌐 Deployed a responsive web dashboard via GitHub Pages
- 🤖 Automated water quality classification without manual intervention
- 🌍 Enabled remote, real-time monitoring from any location globally

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

<div align="center">

**Clean water. Smarter monitoring. Healthier planet.**

*IoT · Firebase · Flutter · Arduino · NodeMCU · Real-Time · Open Source*

<br/>

⭐ *Star this repo if you found it useful!* ⭐

</div>

---
