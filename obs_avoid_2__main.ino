// Define pins for ultrasonic sensor
#define trigPin 9
#define echoPin 8

// Define pins for motor driver
#define motor1Pin1 4
#define motor1Pin2 5
#define motor2Pin1 6
#define motor2Pin2 7
#define enableM1 10
#define enableM2 11

// Define distance threshold
#define obstacleDistance 25 // in centimeters

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Define motor pins as outputs
  pinMode(enableM1, OUTPUT);
  pinMode(enableM2, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Define trigger pin as output and echo pin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set initial motor speeds using PWM (analogWrite)
  analogWrite(enableM1, 80);
  analogWrite(enableM2, 80);
}

void loop() {
  // Send a pulse to the ultrasonic sensor to initiate a reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);       // Transmit Waves For 10us
  delayMicroseconds(10);
  noInterrupts();
  long duration = pulseIn(echoPin, HIGH);  // Receive Reflected Waves
  interrupts();
  long distance = duration / 58.2; // Convert the duration to distance in centimeters
  Serial.println(distance); // Print the distance
  
  delay(50); // Wait for a short time

  // Move the robot forward by default
  forward();
  
  // Check if an obstacle is detected within the defined threshold
  if (distance <= obstacleDistance) {
    stopp(); // Stop the robot
    delay(500); // Wait for a brief moment
    
    backward(); // Move backward
    delay(500); // Wait for a brief moment
    
    stopp(); // Stop the robot again
    
    // Turn left or right randomly
    if (random(2)) {
      // Turn left
      left();
      delay(125); // Adjust turn duration as needed
    } else {
      // Turn right
      right();
      delay(125); // Adjust turn duration as needed
    }
  }  
}

// Function to stop the robot
void stopp() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move the robot forward
void forward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to move the robot backward
void backward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn left
void left() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn right
void right() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}
/*This code sets up an Arduino to control a robot equipped with an ultrasonic sensor and two motors. Here's a breakdown of what it does:

Pins are defined for the ultrasonic sensor (trigger and echo pins) and the motor driver (motor pins and enable pins).
A distance threshold is defined to detect obstacles.

In the setup() function:
Serial communication is initialized.
Motor pins are set as outputs.
Ultrasonic sensor pins are set as output for trigger and input for echo.
Initial motor speeds are set using PWM (Pulse Width Modulation) via analogWrite() function.

In the loop() function:
A pulse is sent to the ultrasonic sensor to initiate a reading.
The duration of the pulse received back is measured using pulseIn() function and converted to distance in centimeters.
The distance is printed to the Serial Monitor.
The robot moves forward by default.
If an obstacle is detected within the defined threshold:
The robot stops briefly.
Then it moves backward.
After a brief delay, it stops again.
It randomly chooses to turn left or right and performs the corresponding action.

Functions are defined to control the robot's movement: stopp() to stop, forward() to move forward, backward() to move backward, left() to turn left, 
and right() to turn right.
 These functions control the motor pins accordingly to achieve the desired movement. */ 