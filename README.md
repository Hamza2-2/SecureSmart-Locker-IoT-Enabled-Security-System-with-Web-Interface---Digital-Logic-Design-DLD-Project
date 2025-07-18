# SecureSmart-Locker-IoT-Enabled-Security-System-with-Web-Interface-Digital-Logic-Design-DLD-Project
# 🔒 SecureSmart Locker - DLD Project

![Project Banner](https://via.placeholder.com/1200x400/2D3748/FFFFFF?text=SecureSmart+Locker+Prototype)

## 📌 Table of Contents
- [Features](#-features)
- [Hardware](#-hardware)
- [Schematic Diagram](#-Schematic-diagram)
- [Arduino Flow-Chart](#-Arduino_Flow-Chart)
- [Esp Flow-Chart](#-Esp_Flow-Chart)
- [Truth-Table](#-Truth-Table)
- [K-Map](#-K-Map)
- [Installation](#-installation)
- [Usage](#-usage)
- [Code Structure](#-code-structure)

## ✨ Features
- **Dual Authentication**  
  - Physical keypad (4-digit code)
  - Web interface (ESP8266)
- **Proximity Detection**  
  - HC-SR04 Ultrasonic sensor (<30 inches)
- **Security Alarms**  
  - 3-strike limit before buzzer activation
  - Master password override
- **Remote Control**  
  - Open/close via web browser
  - Alarm system management

## 🛠️ Hardware
| Component | Quantity | Connection |
|-----------|----------|------------|
| Arduino UNO | 1 | Main Controller |
| ESP8266 | 1 | WiFi Module |
| SG90 Servo | 1 | D10 (Lock Mechanism) |
| 4×4 Keypad | 1 | Rows: D6-D9, Cols: D2-D5 |
| HC-SR04 | 1 | Trig:D11, Echo:D12 |
| Piezo Buzzer | 1 | D13 |
| LED (Red/Green) | 2 | D14, D15 |

## 🔌 Schematic Diagram
<img width="758" height="282" alt="image" src="https://github.com/user-attachments/assets/cd093757-d4d6-458f-8110-acb665b35bc4" />

## Arduino_Flow-Chart
<img width="457" height="780" alt="image" src="https://github.com/user-attachments/assets/65175d44-a6d4-442d-a399-9b2fef769b6e" />

## Esp_Flow-Chart
<img width="570" height="762" alt="image" src="https://github.com/user-attachments/assets/0016209f-d2e0-4621-9f25-3b41301c31c2" />

## Truth-Table
<img width="658" height="146" alt="image" src="https://github.com/user-attachments/assets/61c7266a-6bd7-45e7-a93a-aa2b092ea49e" />
<img width="635" height="231" alt="image" src="https://github.com/user-attachments/assets/ddf008d8-bd70-430c-9d2f-a2ba26cbd643" />
<img width="648" height="142" alt="image" src="https://github.com/user-attachments/assets/37fd0aa0-394b-4474-b567-eec5af224bc1" />
<img width="651" height="102" alt="image" src="https://github.com/user-attachments/assets/c18989b6-7a4c-432f-8d2c-be579923229f" />
<img width="631" height="22" alt="image" src="https://github.com/user-attachments/assets/d57cdd59-a9fb-4b9c-8822-36281b95839e" />


## K-Map 
<img width="595" height="197" alt="image" src="https://github.com/user-attachments/assets/1b049bc8-e087-46b9-b6cf-dbc1ad92e614" />
<img width="592" height="152" alt="image" src="https://github.com/user-attachments/assets/c9319fc8-c8ba-4534-82fc-fac77682d7a9" />
<img width="586" height="156" alt="image" src="https://github.com/user-attachments/assets/792e78ee-1898-45e4-91ad-ceb8d5d0942e" />
<img width="582" height="73" alt="image" src="https://github.com/user-attachments/assets/f56793b8-3cec-4a93-b1f6-a9f1123757d0" />
<img width="595" height="77" alt="image" src="https://github.com/user-attachments/assets/12887c73-348f-4fe7-8de2-9708c0adef13" />


## ⚡ Installation
1. **Required Libraries**:
   ```bash
   # Arduino IDE
   Keypad.h
   Servo.h
   ESP8266WiFi.h


## Upload Code
# Arduino (Security Core)
SecurityLocker.ino

# ESP8266 (Web Interface)
WebInterface.ino

## Network Setup

🖥️ Usage


```markdown
# 1. Physical Access:
- Enter 4-digit code on keypad

- Press '#' to confirm

- '*' to cancel

# 2. Web Interface:

# Default Credentials
- URL: http://<ESP_IP>/
- Username: Naruto
- Password: 1234

```

## 💻 Code Structure
```markdown
# Arduino (Security Core)

void loop() {
  distance = getUltrasonicDistance();
  key = keypad.getKey();
  
  if (key == '#') {
    if (enteredPassword == correctPassword && distance < 30) {
      unlockLocker();
    } else {
      failedAttempts++;
      if (failedAttempts >= 3) triggerAlarm();
    }
  }

}

```
```markdown
# ESP8266 (Web Server)
void handleOpen() {
  if (authenticated) {
    digitalWrite(buzzerPin, HIGH);
    servo.write(90); // Unlock
    delay(500);
    digitalWrite(buzzerPin, LOW);
    server.send(200, "text/plain", "Locker Opened");
  }
}
```
