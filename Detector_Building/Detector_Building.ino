// Cole Delong
// 12/26/2019

// Variables
const int bluePin = 5;
const int greenPin = 4;
const int redPin = 3;
const int tempPin = 0;

void setup() {

  // Initialize the LED pins
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  // Start a serial port so we can see the temp
  Serial.begin(9600);

}

void loop() {

  // The vars for the voltage and degrees
  float voltage, degC, degF;

  // Find the voltage the tempPin is receiving
  voltage = getVoltage();

  // CALIBRATE!!! Use linear equation derived from data to determine the degrees celcius based off of the voltage
  degC = (voltage * 100) - 50;

  // Use the calculated celcius to determine the temp feihrenheaeiiit because this is America
  degF = degC * (9.0/5.0) + 32.0;

  // Print both of these values to the serial port. Eventually these will be displayed on an LCD screen.
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degC);
  Serial.print("  deg F: ");
  Serial.println(degF);

  // Delay so it doesn't go too crazy
  delay(500);

}

float getVoltage() {

  // Calculate the voltage by changing it from a range of 0 to 1023 to a range of 0 to 5. Return the result.
  return (analogRead(tempPin) * (5.0 / 1024.0));
  
}
