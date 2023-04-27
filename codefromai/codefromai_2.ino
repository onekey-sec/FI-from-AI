const int gpioPin = 2; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Arduino pin number you're using for output

volatile bool triggered = false; // flag to indicate trigger occurred
volatile unsigned long pulseDelay = 1000000; // initial delay of 1000000 nanoseconds (1 millisecond)
volatile unsigned long pulseWidth = 500000; // initial pulse width of 500000 nanoseconds (0.5 millisecond)

void setup() {
  pinMode(outputPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin
}

void loop() {
  if (triggered) { // check if trigger occurred
    digitalWrite(outputPin, HIGH); // send the pulse
    delayMicroseconds(pulseWidth / 1000); // convert pulse width from nanoseconds to microseconds
    digitalWrite(outputPin, LOW);
    delayMicroseconds(pulseDelay / 1000); // convert pulse delay from nanoseconds to microseconds
    triggered = false; // reset trigger flag
  }
}

void triggerInterrupt() {
  triggered = true; // set trigger flag
}
