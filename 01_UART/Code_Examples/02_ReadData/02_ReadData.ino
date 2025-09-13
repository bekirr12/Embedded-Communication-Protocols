/* 
  02_ReadData

  This example shows how to read incoming data from serial monitor. We can use 
  Serial.available() and Serial.read() functions. First, we check if there's any data available, 
  and if so, we read it and print it out.
  available() - checks if serial data is available (if you send a command from the Serial Monitor).
  read() - reads data from the serial port.

  https://github.com/bekirr12/embedded-communication-protocols

  September 9, 2025
  Bekir Sami Karatas
*/

int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(115200); // initialize the Serial monitor with 115200 baud rate
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    incomingByte = Serial.read(); // read the incoming data

    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}