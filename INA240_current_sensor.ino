// Pin assignment
const int sensorPin = A0; // Analog input pin that the INA240 output is connected to

// Constants for calculation
const float referenceVoltage = 4.55; // Reference voltage for the Arduino ADC (Using multimeter measure between +5V and GND)
const float shuntResistorValue = 0.01; // Value of the shunt resistor in ohms (10 milliohm)
const float gain = 50.0; // Gain of the INA240, it can be A1=20, A2=50, A3=100, A4=200
const int numSamples = 100; // Number of samples for averaging
const float error = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  //analogReference(EXTERNAL);
}

void loop() {
  long sensorValueSum = 0;
  
  // Take multiple samples for averaging
  for (int i = 0; i < numSamples; i++) {
    sensorValueSum += analogRead(sensorPin);
    delay(10); // Short delay between samples
  }
  
  // Calculate the average sensor value
  float sensorValueAvg = sensorValueSum / numSamples;
  
  // Convert the average sensor value to voltage
  float voltage = sensorValueAvg * (referenceVoltage / 1024.0);
  
  // Calculate the current using the voltage, gain, and shunt resistor value
  float shuntVoltage = voltage / gain; 
  float current = shuntVoltage / shuntResistorValue;
  
  // Print the results to the serial monit
  Serial.print("Sensor Value: ");
  Serial.print(sensorValueAvg);
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 5);
  Serial.print(" V\tShunt Voltage: ");
  Serial.print(shuntVoltage, 5);
  Serial.print(" V\tCurrent: ");
  Serial.print(current, 5);
  Serial.println(" A");
  Serial.println("--------------------------------------------------------------------------------------------------");
  // Wait for a bit before the next loop
  delay(1500);
}
