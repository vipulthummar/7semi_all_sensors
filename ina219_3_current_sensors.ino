#include <Wire.h>
#include <Adafruit_INA219.h>

// Create instances for three INA219 sensors
Adafruit_INA219 ina219_1(0x40);
Adafruit_INA219 ina219_2(0x41);
Adafruit_INA219 ina219_3(0x42);

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
      // wait for serial port to open
      delay(1);
  }

  // Initialize the INA219 instances
  if (!ina219_1.begin()) {
    Serial.println("Failed to find INA219_1 chip");
    while (1) { delay(10); }
  }
  if (!ina219_2.begin()) {
    Serial.println("Failed to find INA219_2 chip");
    while (1) { delay(10); }
  }
  if (!ina219_3.begin()) {
    Serial.println("Failed to find INA219_3 chip");
    while (1) { delay(10); }
  }

  // Calibrate INA219 sensors
  ina219_1.setCalibration_32V_2A();  // For 0.1 ohm shunt resistor, max 2A
  ina219_2.setCalibration_32V_2A();
  ina219_3.setCalibration_32V_2A();
}

void loop(void) {
  float shuntvoltage1 = 0;
  float busvoltage1 = 0;
  float current_mA1 = 0;
  float power_mW1 = 0;

  float shuntvoltage2 = 0;
  float busvoltage2 = 0;
  float current_mA2 = 0;
  float power_mW2 = 0;

  float shuntvoltage3 = 0;
  float busvoltage3 = 0;
  float current_mA3 = 0;
  float power_mW3 = 0;

  // Read from INA219_1
  shuntvoltage1 = ina219_1.getShuntVoltage_mV();
  busvoltage1 = ina219_1.getBusVoltage_V();
  current_mA1 = ina219_1.getCurrent_mA();
  power_mW1 = ina219_1.getPower_mW();

  // Read from INA219_2
  shuntvoltage2 = ina219_2.getShuntVoltage_mV();
  busvoltage2 = ina219_2.getBusVoltage_V();
  current_mA2 = ina219_2.getCurrent_mA();
  power_mW2 = ina219_2.getPower_mW();

  // Read from INA219_3
  shuntvoltage3 = ina219_3.getShuntVoltage_mV();
  busvoltage3 = ina219_3.getBusVoltage_V();
  current_mA3 = ina219_3.getCurrent_mA();
  power_mW3 = ina219_3.getPower_mW();

  // Print the results
  Serial.print("INA219_1: ");
  Serial.print("Bus Voltage: "); Serial.print(busvoltage1); Serial.print(" V ");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage1); Serial.print(" mV ");
  Serial.print("Current: "); Serial.print(current_mA1); Serial.print(" mA ");
  Serial.print("Power: "); Serial.print(power_mW1); Serial.println(" mW");
  Serial.println("----------------------------------------------------------------------------------------------");
  Serial.print("INA219_2: ");
  Serial.print("Bus Voltage: "); Serial.print(busvoltage2); Serial.print(" V ");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage2); Serial.print(" mV ");
  Serial.print("Current: "); Serial.print(current_mA2); Serial.print(" mA ");
  Serial.print("Power: "); Serial.print(power_mW2); Serial.println(" mW");
  Serial.println("----------------------------------------------------------------------------------------------");
  Serial.print("INA219_3: ");
  Serial.print("Bus Voltage: "); Serial.print(busvoltage3); Serial.print(" V ");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage3); Serial.print(" mV ");
  Serial.print("Current: "); Serial.print(current_mA3); Serial.print(" mA ");
  Serial.print("Power: "); Serial.print(power_mW3); Serial.println(" mW");
  Serial.println("----------------------------------------------------------------------------------------------");

  delay(2000);
}
