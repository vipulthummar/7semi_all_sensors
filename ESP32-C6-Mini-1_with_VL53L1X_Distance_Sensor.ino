#include <Wire.h>
#include <Preferences.h>
#include "SparkFun_VL53L1X.h" // Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X

// Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

SFEVL53L1X distanceSensor;
// Uncomment the following line to use the optional shutdown and interrupt pins.
// SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

Preferences preferences;
const char* namespaceName = "distanceData"; // Namespace for preferences

const int maxSamples = 10; // Maximum number of samples to store

void setup(void) {
  Wire.begin();

  Serial.begin(115200);
  delay(10000);
  Serial.println("VL53L1X Qwiic Test");

  preferences.begin(namespaceName, false); // Open the preferences with read/write mode

  if (distanceSensor.begin() != 0) { // Begin returns 0 on a good init
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    while (1);
  }
  Serial.println("Sensor online!");

  // Display stored data on boot
  displayStoredData();
}

void loop(void) {
  distanceSensor.startRanging(); // Write configuration bytes to initiate measurement
  while (!distanceSensor.checkForDataReady()) {
    delay(600000);
  }
  int distance = distanceSensor.getDistance(); // Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();

  Serial.print("Distance(mm): ");
  Serial.print(distance);

  float distanceInches = distance * 0.0393701;
  float distanceFeet = distanceInches / 12.0;

  Serial.print("\tDistance(ft): ");
  Serial.print(distanceFeet, 2);
  Serial.println();

  // Store the data
  storeData(distance, distanceFeet);
  displayStoredData();

  delay(10000); // Delay to avoid flooding the serial monitor
}

void storeData(int distanceMM, float distanceFT) {
  int index = preferences.getInt("lastIndex", 0); // Retrieve the last index

  Serial.print("Storing data at index: ");
  Serial.println(index);

  // Save data to preferences
  preferences.putInt(String("distanceMM" + String(index)).c_str(), distanceMM);
  preferences.putFloat(String("distanceFT" + String(index)).c_str(), distanceFT);

  index++;
  // Wrap around the index if it exceeds maxSamples
  if (index >= maxSamples) {
    index = 0;
  }

  preferences.putInt("lastIndex", index); // Save the last index
}

void displayStoredData() {
  int lastIndex = preferences.getInt("lastIndex", 0); // Retrieve the last index

  Serial.print("Last index: ");
  Serial.println(lastIndex);

  Serial.println("Displaying stored data:");
  for (int i = 0; i < maxSamples; i++) {
    Serial.print("Checking index: ");
    Serial.println(i);

    int storedDistanceMM = preferences.getInt(String("distanceMM" + String(i)).c_str(), -1);
    float storedDistanceFT = preferences.getFloat(String("distanceFT" + String(i)).c_str(), -1.0);

    if (storedDistanceMM != -1 && storedDistanceFT != -1.0) {
      Serial.print("Index ");
      Serial.print(i);
      Serial.print(": Stored Distance(mm): ");
      Serial.print(storedDistanceMM);
      Serial.print("\tStored Distance(ft): ");
      Serial.println(storedDistanceFT, 2);
    } else {
      Serial.print("No valid data at index: ");
      Serial.println(i);
    }
  }
}
