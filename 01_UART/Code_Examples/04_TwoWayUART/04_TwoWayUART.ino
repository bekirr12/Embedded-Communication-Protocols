/*
  04_TwoWayUART

  Two Twin Coding Modules (ATmega32u4) were used in this project.
  The same code will be loaded onto both boards.
  This code allows two boards to communicate with each other over
  their hardware serial port (Serial1 on Pins 0 and 1).
  
  What you type in the Serial Monitor of one will appear on the 
  Serial Monitor of the other, and vice-versa.
  
  This demonstrates the module's ability to use both the USB Serial (`Serial`)
  and the hardware UART (`Serial1`) simultaneously and independently.

   +------------------+         +------------------+
   |  Twin Coding A   |         |  Twin Coding B   |
   |                  |         |                  |
   |      GND o-------|---------|-------o GND      |
   |                  |         |                  |
   |      TX  o-------|---------|-------o RX       |
   |                  |         |                  |
   |      RX  o-------|---------|-------o TX       |
   |                  |         |                  |
   +------------------+         +------------------+
  
  https://github.com/bekirr12/embedded-communication-protocols

  September 13, 2025
  Bekir Sami Karatas
*/

void setup() {
  Serial.begin(9600); // Start the USB serial port for communication with the computer
  Serial1.begin(9600);  // Start the hardware serial port for communication with the other Leonardo
}

void loop() {
  // Check for data coming from the computer via USB Serial
  if (Serial.available()) {
    // Read the byte from the computer
    char dataFromPC = Serial.read();
    // Send it to the other Leonardo via hardware Serial1
    Serial1.write(dataFromPC);
  }

  // Check for data coming from the other Leonardo via hardware Serial1
  if (Serial1.available()) {
    // Read the byte from the other Leonardo
    char dataFromLeonardo = Serial1.read();
    // Send it to the computer's Serial Monitor via USB Serial
    Serial.write(dataFromLeonardo);
  }
}