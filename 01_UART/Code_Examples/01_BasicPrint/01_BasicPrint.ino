/* 
  01_BasicPrint

  This example will send the string Hello World! from microcontroller to computer, 
  Serial.println() function. Data will be sent every second.
  Serial.println(): prints the content to the Serial Monitor, and adds a new line
  
  https://github.com/bekirr12/embedded-communication-protocols

  September 9, 2025
  Bekir Sami Karatas
*/

void setup(){
  Serial.begin(9600); // initialize serial communication at a 9600 baud rate
}

void loop(){
  Serial.println("Hello World!");
  delay(1000);
}