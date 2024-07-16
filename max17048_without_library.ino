#include <Wire.h>

#define MAX17048_ADDRESS 0x36 // I2C address for MAX17048

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!initMAX17048()) {
    Serial.println("Failed to initialize MAX17048. Check connections.");
    while (1);
  }
}

void loop() {
  float voltage = readVoltage();
  float soc = readSOC();

  Serial.print("Battery Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("State of Charge: ");
  Serial.print(soc);
  Serial.println(" %");

  delay(2000); // Wait 1 second before the next reading
  Serial.println("------------------------------");
}

bool initMAX17048() {
  Wire.beginTransmission(MAX17048_ADDRESS);
  Wire.write(0x06); // Send reset command (optional)
  Wire.endTransmission();

  delay(100); // Allow some time for the sensor to initialize

  return true; // Assuming initialization is always successful
}

float readVoltage() {
  Wire.beginTransmission(MAX17048_ADDRESS);
  Wire.write(0x02); // Voltage register address
  Wire.endTransmission(false);

  Wire.requestFrom(MAX17048_ADDRESS, 2);
  if (Wire.available() == 2) {
    uint16_t rawVoltage = (Wire.read() << 8) | Wire.read();
    return rawVoltage * 0.078125 / 1000; // Convert to volts
  }

  return -1; // Error in reading
}

float readSOC() {
  Wire.beginTransmission(MAX17048_ADDRESS);
  Wire.write(0x04); // SOC register address
  Wire.endTransmission(false);

  Wire.requestFrom(MAX17048_ADDRESS, 2);
  if (Wire.available() == 2) {
    uint16_t rawSOC = (Wire.read() << 8) | Wire.read();
    return rawSOC / 256.0; // Convert to percentage
  }

  return -1; // Error in reading
}
