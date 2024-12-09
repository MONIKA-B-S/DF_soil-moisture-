#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#define FPSerial Serial2 // Use Serial for boards like Arduino Uno or Serial2 for ESP32/ESP8266
DFRobotDFPlayerMini myDFPlayer;

// Pin Definitions
const int soilSensorPin = 34;  // Pin connected to the soil moisture sensor

// Moisture thresholds
int dryThreshold = 4000;         // Above this is considered dry
int hydratedThreshold = 2000;    // Between dryThreshold and this is hydrated
int overWateredThreshold = 1600; // Below this is considered overwatered

// Flags to check if audio has already been played
bool isDryPlayed = false;
bool isWateredPlayed = false;
bool isOverWateredPlayed = false;

void printDetail(uint8_t type, int value) {
  // Handle messages from DFPlayer (optional)
}

// Function to play a specific sound file with a given duration
void playSound(int soundNumber, int duration) {
  myDFPlayer.play(soundNumber);  // Play the specific sound file
  delay(duration * 1000);        // Wait for the specified duration (in seconds)
}

void setup() {
  FPSerial.begin(9600);          // Start DFPlayer serial communication
  Serial.begin(115200);          // Start Serial communication for debugging

  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(FPSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1. Please recheck the connection!"));
    Serial.println(F("2. Please insert the SD card!"));
    while (true) {
      delay(0); // ESP32 watchdog compatibility
    }
  }

  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);  // Set volume from 0 to 30
}

void loop() {
  // Read soil moisture sensor value
  int soilMoistureValue = analogRead(soilSensorPin);
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);  // Print the sensor value for debugging

  // Soil moisture conditions
  if (soilMoistureValue > dryThreshold) {
    if (!isDryPlayed) {
      playSound(1, 5);  // Play the 1st audio file for dry soil
      isDryPlayed = true;  // Set the flag to avoid repeating the dry audio
      isWateredPlayed = false; // Reset watered and overwatered flags when it’s dry
      isOverWateredPlayed = false;
    }
  } else if (soilMoistureValue <= dryThreshold && soilMoistureValue > overWateredThreshold) {
    if (!isWateredPlayed) {
      playSound(3, 5);  // Play the 3rd audio file for properly watered soil
      isWateredPlayed = true;  // Set the flag to avoid repeating the watered audio
      isDryPlayed = false;     // Reset dry flag
      isOverWateredPlayed = false; // Reset overwatered flag
    }
  } else if (soilMoistureValue <= overWateredThreshold) {
    if (!isOverWateredPlayed) {
      playSound(2, 5);  // Play the 2nd audio file for overwatered soil
      isOverWateredPlayed = true;  // Set the flag to avoid repeating the overwatered audio
      isDryPlayed = false; // Reset dry flag
      isWateredPlayed = false; // Reset watered flag
    }
  }

  delay(5000);  // Delay between each sensor check (5 seconds)
}
