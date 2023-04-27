const int gpioPin = 2; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile unsigned long pulseWidth = 1; // pulse width of 1 microsecond
volatile unsigned long pulseDelay = 100; // delay of 100 microseconds between pulses
volatile unsigned long pulseStartTime = 0; // start time of pulse
volatile boolean pulseActive = false; // flag indicating whether pulse is currently active

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin
}

void triggerInterrupt() {
  if (!pulseActive) { // only start pulse if not already active
    pulseStartTime = micros();
    pulseActive = true;
    delayMicroseconds(pulseDelay);
    digitalWriteFast(outputPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWriteFast(outputPin, LOW);
    pulseActive = false;
  }
}

void loop() {
  // nothing to do here
}
