const int gpioPin = 2; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile unsigned long pulseWidth = 5; // pulse width of 5 nanoseconds (scaled to microseconds)
volatile unsigned long pulseStartTime = 0; // start time of pulse
volatile unsigned long timeSinceTrigger = 0; // time elapsed since last trigger

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
    timeSinceTrigger = micros();
  }
}

void loop() {
  if (timeSinceTrigger > 0) { // only start new pulse if enough time has elapsed since last trigger
    unsigned long pulseDelay = 10000 - timeSinceTrigger; // calculate pulse delay based on time since trigger
    if (pulseDelay < 0) {
      pulseDelay = 0; // avoid negative pulse delay
    }
    delayMicroseconds(pulseDelay);
    timeSinceTrigger = 0;
  }
}
