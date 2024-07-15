#include<SoftwareSerial.h>
SoftwareSerial myUART(2, 3); //Rx, Tx

int i;
void setup() {
  Serial.begin(9600);  
  myUART.begin(9600);
  delay(5000);
  for(i = 1; i < 6; i++)
  {                
  myUART.println((String)"Hello, UART! "+i);
  delay(500);
  }
  myUART.println("----------------");
}

void loop() {
if(myUART.available() > 0)
{
String data = myUART.readString();
Serial.println(data);
}
  delay(100);
}
