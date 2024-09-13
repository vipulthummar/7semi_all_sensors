#include <Wire.h>

#define ADS7830_ADDRESS 0x48  // I2C address of ADS7830

void setup() {
  Serial.begin(115200);
  Wire.begin();  // Initialize I2C communication
}

void loop() {
  int adcValue = readADC(0);  // Read channel 0

  // Check if ADC value is valid
  if (adcValue < 0) {
    Serial.println("Error reading from ADC");
    return;
  }

  // Convert the ADC value to voltage (using 2.5V reference)
  float voltage = adcValue * (2.5 / 255);  

  Serial.print("ADC Value: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage, 3);  // Print voltage with 3 decimal places

  delay(1000);  // Read every second
}

// Function to read a specific ADC channel
int readADC(uint8_t channel) {
  Wire.beginTransmission(ADS7830_ADDRESS);
  Wire.write(0x84 | (channel << 4));  // Control byte for single-ended channel
  if (Wire.endTransmission() != 0) {   // Check for I2C communication error
    Serial.println("I2C communication failed!");
    return -1;
  }

  Wire.requestFrom(ADS7830_ADDRESS, 1);  // Request 1 byte from ADS7830
  if (Wire.available()) {
    return Wire.read();  // Return the 8-bit ADC result
  } else {
    Serial.println("No data received from ADS7830!");
    return -1;  // Return -1 if no data is available
  }
}
