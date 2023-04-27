const int gpioPin = 1; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile unsigned long pulseDelay = 50; // delay of 50 nanoseconds
volatile unsigned long pulseWidth = 50; // pulse width of 50 nanoseconds
volatile unsigned long pulseStartTime = 0; // start time of pulse
volatile bool pulseActive = false; // flag for active pulse

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING); // attach interrupt to GPIO pin

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Check for serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // remove any leading or trailing spaces
    handleSerialInput(input);
  }
}

void handleSerialInput(String input) {
  // Parse and handle serial input
  if (input.startsWith("gpioPin")) {
    gpioPin = input.substring(7).toInt();
    pinMode(gpioPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING);
    Serial.println("Set GPIO pin to: " + String(gpioPin));
  } else if (input.startsWith("outputPin")) {
    outputPin = input.substring(9).toInt();
    pinMode(outputPin, OUTPUT);
    Serial.println("Set output pin to: " + String(outputPin));
  } else if (input.startsWith("trigger")) {
    pulseActive = false;
    attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, input.substring(8).toInt());
    Serial.println("Set trigger to: " + input.substring(8));
  } else if (input.startsWith("pulseDelay")) {
    pulseDelay = input.substring(10).toInt();
    Serial.println("Set pulse delay to: " + String(pulseDelay) + " nanoseconds");
  } else if (input.startsWith("pulseWidth")) {
    pulseWidth = input.substring(10).toInt();
    Serial.println("Set pulse width to: " + String(pulseWidth) + " nanoseconds");
  } else if (input == "print") {
    printVariables();
  } else {
    Serial.println("Invalid command");
  }
}

void triggerInterrupt() {
  if (!pulseActive) {
    pulseActive = true;
    pulseStartTime = elapsedNanoseconds(); // record start time of pulse
    digitalWriteFast(outputPin, HIGH);
    delayNanoseconds(pulseWidth);
    digitalWriteFast(outputPin, LOW);
    delayNanoseconds(pulseDelay);
    pulseActive = false;
  }
}

void printVariables() {
  Serial.println("gpioPin: " + String(gpioPin));
  Serial.println("outputPin: " + String(outputPin));
  Serial.println("trigger: RISING");
  Serial.println("pulseDelay: " + String(pulseDelay) + " nanoseconds");
  Serial.println("pulseWidth: " + String(pulseWidth) + " nanoseconds");
  Serial.println();
}
