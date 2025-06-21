// Water sensor
int water = A0;      // Water level sensor pin
int waterTrigger = 300;  // Water sensor threshold

// Motor A pins
int ena = 5;         // Enable pin for Motor A
int in1 = 6;         // Input 1 for Motor A
int in2 = 7;         // Input 2 for Motor A

// Motor B pins
int enb = 10;        // Enable pin for Motor B
int in3 = 8;         // Input 1 for Motor B
int in4 = 9;         // Input 2 for Motor B

// Buzzer pin
int buzzer = 11;     // Pin for the buzzer
int c = 0;           // State variable

void setup() {
  // Pin setup for Motor A
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Pin setup for Motor B
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Pin setup for buzzer
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int waterLevel = analogRead(water); // Read water level
  Serial.print("Water Level: ");
  Serial.println(waterLevel);
  Serial.print("State (c): ");
  Serial.println(c);
  delay(3000);
  // Trigger pull-up operation if water level exceeds threshold and c is 0
  if (waterLevel >= waterTrigger && c == 0) {
    triggerMotorsAndBuzzer();
    c = 1; // Change state to indicate pull-up operation is done
  } 
  // Trigger reverse operation if water level is <= 10 and c is 1
  else if (waterLevel <= 10 && c == 1) {
    reverseMotors();
    c = 0; // Reset state after reversing motors
  } 
  // Stop motors if no specific condition is met
  else {
    stopMotors();
  }

  delay(100); // Small delay for sensor stability
}

// Function to trigger motors clockwise and buzzer (Pull-up operation)
void triggerMotorsAndBuzzer() {
  Serial.println("Water level triggered! Running motors clockwise and buzzing...");

  // Buzzer ON for 1 second
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);

  // Motor A - Clockwise
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255); // Full speed

  // Motor B - Clockwise
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255); // Full speed

  delay(1000); // Ensure operation completes
}

// Function to reverse motors counterclockwise (Reverse operation)
void reverseMotors() {
  Serial.println("Water level is low! Reversing motors...");

  // Buzzer ON for 1 second
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);

  // Motor A - Counterclockwise
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255); // Full speed

  // Motor B - Counterclockwise
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255); // Full speed

  delay(1000); // Ensure operation completes
}

// Function to stop both motors
void stopMotors() {
  Serial.println("Stopping motors...");

  // Stop Motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ena, 0);

  // Stop Motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enb, 0);

  // Ensure buzzer is OFF
  digitalWrite(buzzer, LOW);
}
