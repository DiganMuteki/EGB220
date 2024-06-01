void setup() {
  // Set pin modes for motors
  pinMode(34, OUTPUT);  // Set pin 34 as output for left motor control
  pinMode(35, OUTPUT);  // Set pin 35 as output for right motor control
}

void loop() {
  // Read sensor values
  int valueRight = analogRead(10);   // Read value from right sensor
  int valueRight2 = analogRead(11);  // Read value from additional right sensor
  int valueLeft = analogRead(6);     // Read value from left sensor
  int valueLeft2 = analogRead(7);    // Read value from additional left sensor

  // Check sensor values and control motors accordingly
  if ((valueRight >= 7000) && (valueRight2 >= 7000)) {
    // If both right sensors detect a value above the threshold, turn left
    digitalWrite(34, 0);     // Turn off left motor
    digitalWrite(35, 100);   // Turn on right motor
  } else if ((valueLeft >= 7000) && (valueLeft2 >= 7000)) {
    // If both left sensors detect a value above the threshold, turn right
    digitalWrite(34, 100);   // Turn on left motor
    digitalWrite(35, 0);     // Turn off right motor
  } else {
    // If no sensors detect a value above the threshold, go straight
    digitalWrite(34, 100);   // Turn on left motor
    digitalWrite(35, 100);   // Turn on right motor
  }

  delay(10);  // Delay for 10 ms to stop robot from undershooting hard turns.
}
