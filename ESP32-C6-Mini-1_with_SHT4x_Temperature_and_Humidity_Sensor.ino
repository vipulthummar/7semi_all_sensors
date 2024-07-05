#include <Preferences.h>
#include "Adafruit_SHT4x.h"

Adafruit_SHT4x sht4 = Adafruit_SHT4x();
Preferences preferences;
int dataCount = 0;  // To keep track of the number of data entries

unsigned long previousMillis = 0;   // Store last time data was displayed
const long interval = 600000;        // Interval at which to display stored data (10 seconds)

void setup() {
    Serial.begin(115200);

    while (!Serial) {
        delay(10000);  // Wait for serial port to connect
    }

    Serial.println("Adafruit SHT4x test");

    preferences.begin("sht4x-data", false);

    if (!sht4.begin()) {
        Serial.println("Couldn't find SHT4x");
        while (1) delay(1);
    }
    Serial.println("Found SHT4x sensor");
    Serial.print("Serial number 0x");
    Serial.println(sht4.readSerial(), HEX);

    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    switch (sht4.getPrecision()) {
       case SHT4X_HIGH_PRECISION: 
           Serial.println("High precision");
           break;
       case SHT4X_MED_PRECISION: 
           Serial.println("Med precision");
           break;
       case SHT4X_LOW_PRECISION: 
           Serial.println("Low precision");
           break;
    }

    sht4.setHeater(SHT4X_NO_HEATER);
    switch (sht4.getHeater()) {
       case SHT4X_NO_HEATER: 
           Serial.println("No heater");
           break;
       case SHT4X_HIGH_HEATER_1S: 
           Serial.println("High heat for 1 second");
           break;
       case SHT4X_HIGH_HEATER_100MS: 
           Serial.println("High heat for 0.1 second");
           break;
       case SHT4X_MED_HEATER_1S: 
           Serial.println("Medium heat for 1 second");
           break;
       case SHT4X_MED_HEATER_100MS: 
           Serial.println("Medium heat for 0.1 second");
           break;
       case SHT4X_LOW_HEATER_1S: 
           Serial.println("Low heat for 1 second");
           break;
       case SHT4X_LOW_HEATER_100MS: 
           Serial.println("Low heat for 0.1 second");
           break;
    }
}

void loop() {
    sensors_event_t humidity, temp;
    
    uint32_t timestamp = millis();
    sht4.getEvent(&humidity, &temp);  // Populate temp and humidity objects with fresh data
    timestamp = millis() - timestamp;

    // Print to serial monitor
    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
    Serial.print("Read duration (ms): "); Serial.println(timestamp);

    // Store data in Preferences
    preferences.putFloat(("temp" + String(dataCount)).c_str(), temp.temperature);
    preferences.putFloat(("humidity" + String(dataCount)).c_str(), humidity.relative_humidity);
    preferences.putUInt(("timestamp" + String(dataCount)).c_str(), timestamp);
    dataCount++;
    preferences.putInt("dataCount", dataCount);

    // Check if it's time to display stored data
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        displayStoredData();
    }

    delay(10000);  // Store data every second
}

void displayStoredData() {
    int storedDataCount = preferences.getInt("dataCount", 0);
    Serial.println("Stored Data:");

    for (int i = 0; i < storedDataCount; i++) {
        float temp = preferences.getFloat(("temp" + String(i)).c_str(), 0.0);
        float humidity = preferences.getFloat(("humidity" + String(i)).c_str(), 0.0);
        uint32_t timestamp = preferences.getUInt(("timestamp" + String(i)).c_str(), 0);

        Serial.print("Stored Temperature: "); Serial.print(temp); Serial.println(" degrees C");
        Serial.print("Stored Humidity: "); Serial.print(humidity); Serial.println("% rH");
        Serial.print("Read duration (ms): "); Serial.println(timestamp);
    }
}
