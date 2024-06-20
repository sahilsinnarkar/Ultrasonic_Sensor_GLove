// Include the required library
#include <NewPing.h>

// Define the pin configurations
#define TRIG_PIN 2
#define ECHO_PIN 3
#define BUZZER_PIN 5
#define VIBRATOR_PIN 6
#define LED_PIN 7

// Define constants for obstacle detection
#define MAX_DISTANCE 70
#define MIN_DISTANCE 0
#define DISTANCE_THRESHOLD_1 50
#define DISTANCE_THRESHOLD_2 30
#define DISTANCE_THRESHOLD_3 15

// Create an instance of the NewPing library
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBRATOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void beep(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(VIBRATOR_PIN, LOW);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(VIBRATOR_PIN, HIGH);
}

void loop() {
  // Trigger the ultrasonic sensor to measure distance
  delay(50);
  int distance = sonar.ping_cm();

  // Check if an obstacle is within the specified range
  if (distance > MIN_DISTANCE && distance < MAX_DISTANCE) {
    // Obstacle detected, vary the beeping based on distance
    if (distance > DISTANCE_THRESHOLD_1) {
      beep(500); // Slow beep for longer distances
    } else if (distance > DISTANCE_THRESHOLD_2) {
      beep(300); // Medium beep for intermediate distances
    } else if (distance > DISTANCE_THRESHOLD_3) {
      beep(200); // Fast beep for closer distances
    } else {
      // Continuous fast beep when very close
      while (distance <= DISTANCE_THRESHOLD_3) {
        beep(100); // Adjust the duration for continuous beep
        delay(100); // Adjust the delay between continuous beeps
        distance = sonar.ping_cm(); // Update the distance
      }
    }

    // Turn on the LED
    digitalWrite(LED_PIN, HIGH);
  } else {
    // No obstacle
    digitalWrite(LED_PIN, LOW);
  }

  // Print the distance for debugging (optional)
  Serial.print("Distance: ");
  Serial.println(distance);

  // Add a delay to avoid continuous detection
  delay(500);
}
