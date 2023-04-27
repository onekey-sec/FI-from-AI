const int gpioPin = 2; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile bool triggered = false; // flag to indicate trigger occurred
volatile unsigned long pulseDelay = 10000; // delay of 10 microseconds
volatile unsigned long pulseWidth = 50; // pulse width of 50 nanoseconds

void setup() {
  pinMode(outputPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin
}

void loop() {
  if (triggered) { // check if trigger occurred
    digitalWrite(outputPin, HIGH); // send the pulse
    delayMicroseconds(pulseWidth / 1000); // convert pulse width from nanoseconds to microseconds
    digitalWrite(outputPin, LOW);
    delayMicroseconds(pulseDelay); // delay in microseconds
    triggered = false; // reset trigger flag
  }
}

void triggerInterrupt() {
  triggered = true; // set trigger flag
}
