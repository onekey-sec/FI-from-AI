#include <Arduino.h>

#define OUTPUT_PIN 3

volatile unsigned long pulseDelay = 50; // delay of 50 nanoseconds
volatile unsigned long pulseWidth = 50; // pulse width of 50 nanoseconds
volatile unsigned long pulseStartTime = 0; // start time of pulse
volatile int gpioPin = 1; // default gpio pin

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(gpioPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin
  Serial.begin(9600); // start serial communication
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    if (input.startsWith("setPin ")) {
      gpioPin = input.substring(7).toInt(); // set GPIO pin
      pinMode(gpioPin, INPUT_PULLUP);
    } else if (input.startsWith("setOut ")) {
      OUTPUT_PIN = input.substring(7).toInt(); // set output pin
      pinMode(OUTPUT_PIN, OUTPUT);
    } else if (input.startsWith("setDelay ")) {
      pulseDelay = input.substring(9).toInt(); // set pulse delay
    } else if (input.startsWith("setWidth ")) {
      pulseWidth = input.substring(9).toInt(); // set pulse width
    } else if (input == "printVars") {
      // print all variables
      Serial.print("gpioPin: ");
      Serial.println(gpioPin);
      Serial.print("outputPin: ");
      Serial.println(OUTPUT_PIN);
      Serial.print("pulseDelay: ");
      Serial.println(pulseDelay);
      Serial.print("pulseWidth: ");
      Serial.println(pulseWidth);
    }
  }
}

void triggerInterrupt() {
  unsigned long currentMillis = micros(); // get current time in microseconds
  if (currentMillis - pulseStartTime >= pulseDelay) { // only start pulse if not already active
    digitalWriteFast(OUTPUT_PIN, HIGH);
    delayNanoseconds(pulseWidth);
    digitalWriteFast(OUTPUT_PIN, LOW);
    pulseStartTime = currentMillis;
  }
}
