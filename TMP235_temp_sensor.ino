#include <Arduino.h>

const int TMP235_PIN = A0;
const int numSamples = 100;

void setup() {
  Serial.begin(115200);
  //analogReference(EXTERNAL); // Set the reference voltage to EXTERNAL (typically 3.3V or 5V)
}

void loop() {
  float sumVoltage = 0.0;

  // Take 100 samples and accumulate the voltage values
  for(int i = 0; i < numSamples; ++i) {
    int sensorValue = analogRead(TMP235_PIN);
    float voltage = sensorValue * (4.82 / 1024.0); // Convert sensor value to voltage
    sumVoltage += voltage;
    delay(10);  // Small delay between readings
  }

  // Calculate average voltage
  float averageVoltage = sumVoltage / numSamples;

  // Calculate temperature based on the average voltage
  float temperatureC = (averageVoltage - 0.5) * 100.0;

  Serial.print("Average Voltage: ");
  Serial.println(averageVoltage, 4); // Print voltage with 4 decimal places
  Serial.print("Average Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(1000);  // Delay for 1 second before taking the next set of readings
}
