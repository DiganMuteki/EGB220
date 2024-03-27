// Define motor pins for H-bridge control
const int leftMotorSpeedPin = 9;    // PWM pin for left motor speed control
const int leftMotorDirectionPin1 = 7;  // Direction pin 1 for left motor
const int leftMotorDirectionPin2 = 8;  // Direction pin 2 for left motor

const int rightMotorSpeedPin = 10;   // PWM pin for right motor speed control
const int rightMotorDirectionPin1 = 11;  // Direction pin 1 for right motor
const int rightMotorDirectionPin2 = 12;  // Direction pin 2 for right motor

// Define sensor pins
const int leftSensorPin = A0;  // Analog pins for IR sensor readings
const int rightSensorPin = A1;

// Define sensor threshold values
const int threshold = 500;  // Adjust this value based on sensor calibration

// Define motor speeds
int leftMotorSpeed = 150;  // Initial motor speeds (0-255)
int rightMotorSpeed = 150;

void setup() {
  // Initialize motor control pins as outputs
  pinMode(leftMotorSpeedPin, OUTPUT);
  pinMode(leftMotorDirectionPin1, OUTPUT);
  pinMode(leftMotorDirectionPin2, OUTPUT);

  pinMode(rightMotorSpeedPin, OUTPUT);
  pinMode(rightMotorDirectionPin1, OUTPUT);
  pinMode(rightMotorDirectionPin2, OUTPUT);

  // Initialize sensor pins as inputs
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  // Check if left sensor detects the line
  if (leftSensorValue > threshold) {
    // Turn right at reduced speed
    digitalWrite(leftMotorDirectionPin1, HIGH);
    digitalWrite(leftMotorDirectionPin2, LOW);
    analogWrite(leftMotorSpeedPin, leftMotorSpeed);

    // Stop right motor
    digitalWrite(rightMotorDirectionPin1, LOW);
    digitalWrite(rightMotorDirectionPin2, LOW);
    analogWrite(rightMotorSpeedPin, 0);
  } 
  // Check if right sensor detects the line
  else if (rightSensorValue > threshold) {
    // Turn left at reduced speed
    digitalWrite(leftMotorDirectionPin1, LOW);
    digitalWrite(leftMotorDirectionPin2, LOW);
    analogWrite(leftMotorSpeedPin, 0);

    digitalWrite(rightMotorDirectionPin1, HIGH);
    digitalWrite(rightMotorDirectionPin2, LOW);
    analogWrite(rightMotorSpeedPin, rightMotorSpeed);
  } 
  else {
    // Move forward at set speed
    digitalWrite(leftMotorDirectionPin1, HIGH);
    digitalWrite(leftMotorDirectionPin2, LOW);
    analogWrite(leftMotorSpeedPin, leftMotorSpeed);

    digitalWrite(rightMotorDirectionPin1, HIGH);
    digitalWrite(rightMotorDirectionPin2, LOW);
    analogWrite(rightMotorSpeedPin, rightMotorSpeed);
  } 
  }

