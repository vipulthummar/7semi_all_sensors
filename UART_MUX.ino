void setup() {
  // Start the Serial communication to send data to the computer
  Serial.begin(9600);  // 9600 is the baud rate
}

void loop() {
  // Send a simple string message
  Serial.println("Hello, UART!");
  
  // Wait for 1 second before sending the next message
  delay(1000);
}
