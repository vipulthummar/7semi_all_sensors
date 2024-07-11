#include<SoftwareSerial.h>
SoftwareSerial uartMux(2, 3); //Rx, Tx

void setup()
{
Serial.begin(9600);
uartMux.begin(9600);
}

void loop()
{
if(Serial.available() > 0)
{
String data = Serial.readString();
//Serial.println(data);
uartMux.println(data);
}
if(uartMux.available() > 0)
{
String data = uartMux.readString();
Serial.println(data);
}
}