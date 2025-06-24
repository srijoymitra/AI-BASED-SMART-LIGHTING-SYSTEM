# AI-Based Smart Lighting System using ESP8266

This project is a smart and energy-efficient lighting system built using the ESP8266 microcontroller. It automatically controls light intensity based on environmental conditions, motion detection, and time of day. Designed to mimic intelligent behavior, the system demonstrates real-time responsiveness while remaining lightweight and scalable.

## 💡 Features

- Ambient light sensing using LDR
- Motion detection using PIR sensor
- Adaptive LED brightness using PWM
- Time-based lighting control using NTP (circadian lighting)
- Environmental monitoring (temperature, pressure) with BMP280
- Real-time feedback via OLED display
- Built on ESP8266 using Arduino (C++) with future support for AI/TinyML

## 🔧 Components Used

| Component           | Purpose                                 |
|---------------------|-----------------------------------------|
| ESP8266 (NodeMCU)   | Main controller with Wi-Fi              |
| LDR                 | Ambient light detection                 |
| PIR Sensor          | Motion detection                        |
| BMP280              | Temperature and pressure sensing        |
| OLED Display (SSD1306) | Real-time data display              |
| LED (PWM controlled)| Smart light output                      |
| Resistors (10k, 220Ω)| For LDR voltage divider and LED safety |


## 🧠 Intelligent Logic

- If **motion is detected** and **room is dark**, light turns ON.
- If **no motion for 1 minute** or **ambient light increases**, light turns OFF.
- LED brightness varies depending on:
  - **Ambient light (LDR)**
  - **Time of day** (fetched via NTP)
  - **Environmental conditions** (optional future expansion)
  
## 🕒 Time-Based Lighting Schedule

| Time Range      | LED Brightness |
|-----------------|----------------|
| 6 AM – 9 AM     | Soft (PWM 600) |
| 9 AM – 5 PM     | Bright (PWM 1023) |
| 5 PM – 10 PM    | Dim (PWM 512) |
| 10 PM – 6 AM    | Off (PWM 0) |

## ⚙️ Technologies Used

- C++ (Arduino style)
- Arduino IDE / VS Code + PlatformIO
- I²C protocol for OLED and BMP280
- PWM for LED dimming
- NTP client for real-time clock
- Serial Monitor for debugging

## 🚀 Future Improvements

- TinyML integration for predictive lighting
- Mobile app or cloud dashboard
- Voice or gesture-based control
- Adaptive energy optimization via AI


