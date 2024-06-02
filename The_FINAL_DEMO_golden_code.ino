// Define motor pins for H-bridge control
const int RightMotorSpeedPin = 16; // Pin for controlling right motor speed
const int LeftMotorSpeedPin = 17;  // Pin for controlling left motor speed

// Define sensor pins
int numSensors = 8;
const int sensorPins[] = {1, 2, 3, 4, 5, 6, 7, 8}; // Pins connected to the sensors
int sensorValue[8] = {}; // Array to store sensor readings

// Define sensor threshold value
const int threshold_ir = 290; // Threshold value for sensor activation

// Define constants for proportional control
int BaseSpeed = 100;
int Error = 0;
double Kp = 32;  // Proportional gain
double Output = 0; // Output control signal

void setup() {
  // Define OUTPUT pins for motors
  pinMode(RightMotorSpeedPin, OUTPUT);
  pinMode(LeftMotorSpeedPin, OUTPUT);
}

void loop() {
  // Read sensors and store values in sensorValue array
  for (int i = 0; i < numSensors; i++) {
    sensorValue[i] = analogRead(sensorPins[i]);
  }
  // Call the Controller function to adjust motor speeds based on sensor readings
  Controller();
}

int Calculate_Error() {
  // Calculate error based on sensor values and threshold
  if (sensorValue[0] >= threshold_ir && sensorValue[1] >= threshold_ir) {
    Error = -3; // Both leftmost sensors activated, significant left deviation
  }
  else if (sensorValue[1] >= threshold_ir && sensorValue[2] >= threshold_ir) {
    Error = -2; // Two left sensors activated, moderate left deviation
  }
  else if (sensorValue[2] >= threshold_ir && sensorValue[3] >= threshold_ir) {
    Error = -1; // Slight left deviation
  }
  else if (sensorValue[3] >= threshold_ir && sensorValue[4] >= threshold_ir) {
    Error = 0;  // Centered, no deviation
  }
  else if (sensorValue[4] >= threshold_ir && sensorValue[5] >= threshold_ir) {
    Error = 1;  // Slight right deviation
  }
  else if (sensorValue[5] >= threshold_ir && sensorValue[6] >= threshold_ir) {
    Error = 2;  // Two right sensors activated, moderate right deviation
  }
  else if (sensorValue[6] >= threshold_ir && sensorValue[7] >= threshold_ir) {
    Error = 3;  // Both rightmost sensors activated, significant right deviation
  }  
  return Error; // Return calculated error
}

void Controller() {
  // Retrieve error from Calculate_Error function
  Error = Calculate_Error();

  // Calculate proportional output
  Output = Kp * Error;

  // Adjust motor speeds based on proportional output
  int LeftSpeed = BaseSpeed + Output;
  int RightSpeed = BaseSpeed - Output;

  // Ensure motor speeds are within valid range (0 to 255)
  if (LeftSpeed > 255) LeftSpeed = 255;
  if (LeftSpeed < 0) LeftSpeed = 0;
  if (RightSpeed > 255) RightSpeed = 255;
  if (RightSpeed < 0) RightSpeed = 0;

  // Apply motor speeds using PWM
  analogWrite(LeftMotorSpeedPin, LeftSpeed);
  analogWrite(RightMotorSpeedPin, RightSpeed);

  // Apply 10 ms delay to smooth out controller response
  delay(10);
}
