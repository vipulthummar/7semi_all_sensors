#define ACS772_pin A0  // change the pin number accordingly
float current = 0;
float currentraw = 0;
float sensitivity = 40.00;  // for sensitivity, refer to the datasheet
const int numSamples = 50;  // number of samples to average for stabilization

void setup() {
  Serial.begin(9600);
  pinMode(ACS772_pin, INPUT);
  Serial.println("Hello!");
  Serial.println("Evelta Electronics 7SEMI Labs");
}

void loop() {
  float totalRaw = 0;
  for (int i = 0; i < numSamples; i++) {
    float sample = analogRead(ACS772_pin);
    if (sample >= 0 && sample <= 1023) {  // Error handling for valid ADC range
      totalRaw += sample;
    } else {
      Serial.println("Error: Invalid ADC value");
      return;  // Exit the loop if an invalid value is read
    }
    delay(50);  // Short delay between samples
  }

  currentraw = totalRaw / numSamples;
  current = ((currentraw - 512) * 5.10 / sensitivity);
  Serial.print("Average ADC Value: ");
  Serial.println(currentraw);
  Serial.print("Current: ");
  Serial.println(current );
  delay(1000);
}
