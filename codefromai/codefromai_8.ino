const int gpioPin = 2; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile unsigned long pulseDelay = 10; // delay of 10 microseconds
volatile unsigned long pulseWidth = 5; // pulse width of 5 nanoseconds (scaled to microseconds)
volatile unsigned long pulseStartTime = 0; // start time of pulse

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin
  ARM_DEMCR |= ARM_DEMCR_TRCENA; // enable cycle counter
  ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA; // enable cycle counter
}

void triggerInterrupt() {
  if (pulseStartTime == 0) { // only start pulse if not already active
    digitalWriteFast(outputPin, HIGH);
    pulseStartTime = ARM_DWT_CYCCNT;
    while ((micros() - pulseStartTime / 1000) < pulseWidth) {
      // wait for pulse width to expire
    }
    digitalWriteFast(outputPin, LOW);
    pulseStartTime = 0;
    delayMicroseconds(pulseDelay);
  }
}
