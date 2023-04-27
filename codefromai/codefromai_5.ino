const int gpioPin = 2; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile unsigned long pulseDelay = 10000; // delay of 10 microseconds
volatile unsigned long pulseWidth = 5; // pulse width of 5 nanoseconds
volatile unsigned long pulseStartTime = 0; // start time of pulse

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin
}

void loop() {
  if (pulseStartTime != 0 && micros() - pulseStartTime >= pulseWidth) { // check if pulse is still active
    digitalWrite(outputPin, LOW);
    pulseStartTime = 0;
  }
}

void triggerInterrupt() {
  if (pulseStartTime == 0) { // only start pulse if not already active
    digitalWrite(outputPin, HIGH);
    pulseStartTime = micros();
    delayMicroseconds(pulseWidth / 1000); // delay in microseconds
    digitalWrite(outputPin, LOW);
    pulseStartTime = 0;
    delayMicroseconds(pulseDelay / 1000); // delay in microseconds
  }
}
