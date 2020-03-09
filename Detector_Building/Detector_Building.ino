// Cole Delong
// 12/26/2019

// Included pckages
#include <LiquidCrystal.h>

// LCD initialization
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Pin constants
const int bluePin = 5;
const int greenPin = 4;
const int redPin = 3;
const int tempPin = 0;
const int contrastPin = 6;
const int buttonPin = 7;

// Temperature ranges
const int redUpper = 30;
const int redLower = 20;
const int greenUpper = 20;
const int greenLower = 10;
const int blueUpper = 10;
const int blueLower = 0;

// ughhh average temp for more consistency
const int resetNum = 400;
float volts[resetNum];
int cycles = 0;

// jus button tings
bool output = true;
bool curButton;
bool prevButton = false;

void setup() {

  // Initialize the LED pins
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  // Initialize the button pin
  pinMode(buttonPin, INPUT);
  // Initialize the LCD screen
  analogWrite(6, 75);
  lcd.begin(16, 2);

  // Start a serial port
  Serial.begin(9600);

}

void loop() {

  // The vars for the voltage and degrees
  float voltage, tempC, tempF;

  // Find the voltage the tempPin is receiving
  voltage = getVoltage();

  // only do calculations every 100 cycles with the average of the cycles
  //Serial.println(cycles); 
  volts[cycles] = voltage;
  //Serial.println(volts[cycles]);
  
  if (cycles >= resetNum - 1) {

    // Reset the counter
    cycles = 0;

    // Use the average of the voltages as the voltage
    float sum = 0;
    for (int i = 0; i < resetNum; i++) {
      sum += volts[i];
    }
    voltage = sum/resetNum;

    // Use power equation derived from data to determine the degrees celcius based off of the voltage
    tempC = 137.632 * pow(0.679972, voltage) - 48.2687;

    // Use the calculated celcius to determine the temp feihrenheaeiiit because this is America
    tempF = (tempC * 9/5) + 32;
  
    // If the output is set to on, output the data
    if (output) {
      // Print both of these values to the serial port and to the LCD screen
      Serial.print("voltage: ");
      Serial.print(voltage, 5);
      Serial.print("  temp C: ");
      Serial.print(tempC);
      Serial.print("  temp F: ");
      Serial.println(tempF);
      lcd.setCursor(0, 0);
      lcd.print("Voltage: "); 
      lcd.print(voltage, 5);
      lcd.setCursor(0,1);
      lcd.print("Deg C: ");
      lcd.print(tempC);
      
  
      // Turn on the correct LED for the temperature range
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      if (tempC <= redUpper && tempC >= redLower) digitalWrite(redPin, HIGH);
      if (tempC <= greenUpper && tempC >= greenLower) digitalWrite(greenPin, HIGH);
      if (tempC <= blueUpper && tempC >= blueLower) digitalWrite(bluePin, HIGH);
      
    }
  }

  // Pause the screen if the button is pressed
  curButton = digitalRead(buttonPin);
  if (curButton != prevButton) toggleOutput();
  prevButton = curButton;


  // increment the cycle count
  cycles += 1;

  // Give it a break, it's been working hard.
  delay(2);

}

float getVoltage() {

  // Calculate the voltage by changing it from a range of 0 to 1023 to a range of 0 to 5. Return the result.
  return (analogRead(tempPin) * (5.0 / 1024.0));
  
}

void toggleOutput() {

  // toggle the toggleOutput var
  if (output) output = false;
  else output = true;

}
