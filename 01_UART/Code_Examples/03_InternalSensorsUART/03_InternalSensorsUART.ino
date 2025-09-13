/* 03_InternalSensorsUART

  This example shows how to send data from the ESP32's internal sensors 
  to the computer's Serial Monitor. It reads values from the built-in 
  the CPU temperature sensor, printing them out once per second.
  
  temperatureRead() - reads the internal CPU temperature in Fahrenheit.
  println()         - prints data to the serial port as human-readable text.

  https://github.com/bekirr12/embedded-communication-protocols

  September 11, 2025
  Bekir Sami Karatas
*/

void setup() {
  Serial.begin(115200); // initialize the Serial monitor with 115200 baud rate.
}

void loop() {
  float temp_f = temperatureRead(); // Read the internal CPU temperature.
  float temp_c = (temp_f - 32.0) / 1.8; // Convert Fahrenheit to Celsius for convenience.

  Serial.print("Chip Temperature Value: ");
  Serial.print(temp_c, 2);
  Serial.print(" C / ");
  Serial.print(temp_f, 2);
  Serial.print(" F / ");
  Serial.println();
  delay(1000);  // Wait for 1 second
}