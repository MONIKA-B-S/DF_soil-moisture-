# Soil Moisture Detection and Audio Feedback System

## Description

This project uses an **ESP32/ESP8266** board, a **DFPlayer Mini MP3 module**, and a **soil moisture sensor** to detect the moisture level of soil. The system provides an audio feedback based on the soil moisture condition:

- **Dry soil**: Plays the first audio file (sound 1).
- **Hydrated soil**: Plays the third audio file (sound 3).
- **Overwatered soil**: Plays the second audio file (sound 2).

### Key Features:
- **DFPlayer Mini MP3 Module** for audio playback.
- **Soil Moisture Sensor** to measure the moisture level in the soil.
- **Thresholds** for determining dry, hydrated, and overwatered soil.
- **Audio feedback** for each condition.

This project is suitable for applications like smart irrigation systems or plant monitoring systems.

---

## Hardware Requirements:

1. **ESP32 or ESP8266 Board** (any compatible board with at least one UART interface)
2. **DFPlayer Mini MP3 Module** (to play the audio files)
3. **Soil Moisture Sensor** (analog type)
4. **Speaker** (for audio output via DFPlayer)
5. **MicroSD Card** (with audio files stored)
6. **Jumper wires**
7. **Breadboard** (optional, for easy connections)

---

## Connections:

### Soil Moisture Sensor:
- **VCC** to **3.3V** (or 5V, depending on sensor)
- **GND** to **GND**
- **A0** to **GPIO34** (or any available analog pin on ESP32/ESP8266)

### DFPlayer Mini MP3 Module:
- **VCC** to **5V** (DFPlayer Mini typically works on 5V)
- **GND** to **GND**
- **TX** to **GPIO17** (or any available TX pin on ESP32/ESP8266)
- **RX** to **GPIO16** (or any available RX pin on ESP32/ESP8266)
- **SPK+ and SPK-** to the **speaker**

### ESP32 Pinout Example (can vary depending on the board):
- **GPIO34** → Soil Moisture Sensor (Analog Pin)
- **GPIO16** → DFPlayer Mini RX (pin)
- **GPIO17** → DFPlayer Mini TX (pin)

### SD Card:
- Insert the **microSD card** into the DFPlayer Mini with your audio files in the **root directory** of the SD card.

---

## Code Explanation:

### Libraries Used:
- `DFRobotDFPlayerMini`: Library to control the DFPlayer Mini MP3 module.

### Code Logic:

1. **Initialization**:
   - The code starts by initializing serial communication for both the ESP32/ESP8266 (`Serial` for debugging) and the DFPlayer Mini (`FPSerial` for controlling the DFPlayer).
   
2. **Sensor Reading**:
   - The soil moisture sensor value is read using `analogRead(soilSensorPin)` and is checked against predefined thresholds:
     - **Dry soil**: If the moisture value is greater than the `dryThreshold`, it plays the first audio.
     - **Hydrated soil**: If the moisture value is between `dryThreshold` and `overWateredThreshold`, it plays the third audio.
     - **Overwatered soil**: If the moisture value is less than the `overWateredThreshold`, it plays the second audio.

3. **Flags**:
   - Flags (`isDryPlayed`, `isWateredPlayed`, `isOverWateredPlayed`) are used to ensure the correct audio is played only once when the soil enters a new state.
   
4. **DFPlayer Audio Playback**:
   - The `playSound()` function is used to play a specific sound file based on the sensor reading. The audio files should be named `1.mp3`, `2.mp3`, and `3.mp3` on the SD card.

5. **Serial Debugging**:
   - The `Serial.println()` statements print the soil moisture value for debugging purposes, which can be monitored via the Arduino IDE's Serial Monitor.

---

## Required Libraries:

To use the `DFRobotDFPlayerMini` library, you'll need to install it from the Arduino Library Manager:

1. Open the **Arduino IDE**.
2. Go to **Sketch** → **Include Library** → **Manage Libraries**.
3. Search for **DFRobotDFPlayerMini** and install it.

---

## Project Structure:
/src /components Soil_Moisture_Sensor.h DFPlayer.h /audio 1.mp3 (audio file for dry soil) 2.mp3 (audio file for overwatered soil) 3.mp3 (audio file for properly watered soil) main.ino (Arduino sketch)


---

## How to Use:

1. **Hardware Setup:**
   - Connect the components according to the pin definitions mentioned above.
   - Insert the SD card with the audio files in the correct folder and ensure it's correctly formatted (FAT32).

2. **Upload Code:**
   - Upload the provided code to your **ESP32/ESP8266** board using the Arduino IDE.
   - Open the Serial Monitor (set to `115200` baud rate) to view the moisture value readings.

3. **Operation:**
   - When the soil moisture is **too dry**, the first audio file will play.
   - When the soil is **hydrated**, the third audio file will play.
   - When the soil is **overwatered**, the second audio file will play.
   - The system ensures that each audio file plays only once for each condition change.

---

## Future Improvements:

- Add **multiple thresholds** for more granular control over the soil moisture conditions.
- Implement a **visual display** (e.g., LED indicators) to show the soil condition.
- Add **automatic watering** functionality using a water pump triggered by the soil moisture level.

---

## License:

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

### Contributions:
Feel free to fork this repository, make changes, and submit a pull request. Contributions are always welcome!

---

### Acknowledgements:
This project uses the **DFRobot DFPlayer Mini** module and the **Arduino** platform. Thanks to DFRobot and the open-source community for their amazing libraries and contributions.

---

This **README.md** file provides a complete overview of the project, hardware setup, and instructions for uploading the code and using the system. You can copy this and paste it into your GitHub repository. Let me know if you'd like any modifications!

