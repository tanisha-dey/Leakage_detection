#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the digital pins connected to the water flow sensors, LED, and buzzer
const int flowSensorPin1 = 2;
const int flowSensorPin2 = 3;
const int buzzerPin = 10;
const int ledPin = 9;

// Variables to store the number of pulses and flow rates for each sensor and the difference in flow rates
volatile int pulseCount1, pulseCount2;
float flowRate1, flowRate2;
float flowRateDifference;

// Define the time interval (in milliseconds) to measure flow rate
unsigned int interval = 1000;  // 1 second interval

// Initialize the LCD with the I2C address and number of columns/rows
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and dimensions

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD display
  lcd.init();
  lcd.backlight();  // Turn on the backlight

  // Initialize digital pins for input and enable the internal pull-up resistors
  pinMode(flowSensorPin1, INPUT);
  pinMode(flowSensorPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(flowSensorPin1, HIGH);  // Activate internal pull-up
  digitalWrite(flowSensorPin2, HIGH);  // Activate internal pull-up
  digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
  digitalWrite(ledPin, LOW);  // Turn off the LED

  // Attach interrupts to the digital pins to count pulses
  attachInterrupt(digitalPinToInterrupt(flowSensorPin1), pulseCounter1, FALLING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin2), pulseCounter2, FALLING);

  // Print initial messages to serial monitor
  Serial.println("Flow Rate Monitoring");

  // Print initial messages to LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water FlowMeter");
  lcd.setCursor(0, 1);
  lcd.print("   sensing...");
  delay(2000);  // Delay for 2 seconds before starting measurements
}

void loop() {
  // Disable interrupts during calculations
  detachInterrupt(digitalPinToInterrupt(flowSensorPin1));
  detachInterrupt(digitalPinToInterrupt(flowSensorPin2));

  // Calculate flow rates
  flowRate1 = ((float)pulseCount1 / interval) * 1000.0 / 7.5;  // 7.5 is the number of pulses per liter for sensor 1
  flowRate2 = ((float)pulseCount2 / interval) * 1000.0 / 7.5;  // 7.5 is the number of pulses per liter for sensor 2

  // Calculate difference in flow rates
  flowRateDifference = flowRate1 - flowRate2;

  // Reset pulse counts
  pulseCount1 = 0;
  pulseCount2 = 0;

  // Enable interrupts
  attachInterrupt(digitalPinToInterrupt(flowSensorPin1), pulseCounter1, FALLING);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin2), pulseCounter2, FALLING);

  // Print flow rates and difference to serial monitor
  Serial.print("Flow rate sensor 1: ");
  Serial.print(flowRate1);
  Serial.println(" L/min");

  Serial.print("Flow rate sensor 2: ");
  Serial.print(flowRate2);
  Serial.println(" L/min");

  Serial.print("Flow rate difference: ");
  Serial.print(flowRateDifference);
  Serial.println(" L/min");

  // Update LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor1: ");
  lcd.print(flowRate1, 1); // Display flow rate sensor 1 with 1 decimal place
  lcd.print(" L/min");

  lcd.setCursor(0, 1);
  lcd.print("Sensor2: ");
  lcd.print(flowRate2, 1); // Display flow rate sensor 2 with 1 decimal place
  lcd.print(" L/min");

  delay(5000);  // Display the flow rates for 5 seconds

  // Check for leakage based on flow rate difference
  lcd.clear();
  if (fabs(flowRateDifference) < 4) {
    lcd.setCursor(0, 0);
    lcd.print("No Leakage");
    lcd.setCursor(0, 1);
    lcd.print("Detected");
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
    digitalWrite(ledPin, LOW);  // Turn off the LED
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Leakage");
    lcd.setCursor(0, 1);
    lcd.print("Detected");
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(5000);
    digitalWrite(buzzerPin, LOW);
  }

  delay(3000);
}

// Interrupt service routine for sensor 1 to count pulses
void pulseCounter1() {
  pulseCount1++;
}

// Interrupt service routine for sensor 2 to count pulses
void pulseCounter2() {
  pulseCount2++;
}
