#include <Wire.h>

#define MCP4725_ADDR 0x62  // MCP4725 default I2C address (7-bit)

void setup() {
  Wire.begin();  // Initialize I2C
  Serial.begin(115200);  // Initialize serial communication for debugging
}

void loop() {
  uint16_t dac_value = 2048;  // Example: mid-scale value for 12-bit (0 to 4095)
  
  MCP4725_SetOutput(dac_value);  // Set DAC output
  
  delay(1000);  // Wait for 1 second before setting new value
}

// Function to set the DAC output value (12-bit)
void MCP4725_SetOutput(uint16_t dac_value) {
  Wire.beginTransmission(MCP4725_ADDR);  // Start communication with MCP4725
  
  // Send command byte (fast mode, no EEPROM write)
  Wire.write(0x40);  
  
  // Send the 12-bit DAC value (2 bytes)
  Wire.write(dac_value >> 4);          // Upper 8 bits
  Wire.write((dac_value << 4) & 0xF0); // Lower 4 bits

  Wire.endTransmission();  // End communication
  
  Serial.print("DAC Value Set: ");
  Serial.println(dac_value);  // Print the value to Serial Monitor for debugging
}
