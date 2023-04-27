
volatile  int gpioPin = 1; // replace with the GPIO pin number you're using
volatile  int outputPin = 3; // replace with the Teensy pin number you're using for output
volatile  int triggerCondition = RISING;
volatile  int resetPin = 9;
volatile unsigned long pulseDelay = 50; // delay of 10 microseconds
volatile unsigned long pulseWidth = 50; // pulse width of 5 nanoseconds
volatile unsigned long lastTriggerTime = 0; // start time of pulse
volatile unsigned long pulseTimeout = 1000; // pulse timeout in ms you can do micro by replacing millis by micros.
volatile unsigned long resetWidth = 1000; // pulse timeout in ms you can do micro by replacing millis by micros.

volatile bool interruptEnabled = false;

void setup() {
  Serial.begin(115200);
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT);
  pinMode(resetPin, OUTPUT);

  digitalWriteFast(resetPin, HIGH);
}


void loop() {
  // Check for serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // remove any leading or trailing spaces
    handleSerialInput(input); // parsing the values and assigning to the volatile
  }

  if (interruptEnabled && millis() - lastTriggerTime > pulseTimeout) { // disable interrupt if not triggered for 100 us ; timeout
    detachInterrupt(digitalPinToInterrupt(gpioPin));
    interruptEnabled = false;
    Serial.println("NOK");
  }

}

void triggerInterrupt() {

  delayNanoseconds(pulseDelay);
  digitalWriteFast(outputPin, HIGH);
  delayNanoseconds(pulseWidth);
  digitalWriteFast(outputPin, LOW);
  detachInterrupt(digitalPinToInterrupt(gpioPin));
  interruptEnabled = false;
  Serial.println("AOK");
}


void handleSerialInput(String input) {

    // Parse and handle serial input
    if (input.startsWith("gpioPin")) {
    gpioPin = input.substring(7).toInt();
    pinMode(gpioPin, INPUT_PULLUP);
    Serial.println("OK");
  } else if (input.startsWith("outputPin")) {
    outputPin = input.substring(9).toInt();
    pinMode(outputPin, OUTPUT);
    Serial.println("OK");
  } else if (input.startsWith("trigger")) {
    triggerCondition = input.substring(7).toInt();
    Serial.println("OK");
  } else if (input.startsWith("pulseDelay")) {
    pulseDelay = input.substring(10).toInt();
    Serial.println("OK");
  } else if (input.startsWith("pulseWidth")) {
    pulseWidth = input.substring(10).toInt();
    Serial.println("OK");
  } else if (input.startsWith("pulseTimeout")) {
    pulseTimeout = input.substring(12).toInt();
    Serial.println("OK");
  } else if (input.startsWith("tReset")) {
    resetWidth = input.substring(6).toInt();
    digitalWrite(resetPin, LOW);
    delay(resetWidth);
    digitalWrite(resetPin, HIGH);
    Serial.println("OK");
  } else if (input.startsWith("enable")) {
    interruptEnabled = true;
    Serial.println("OK");
    attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, triggerCondition);
    lastTriggerTime = millis();
  } else if (input == "print") {
    printVariables();
  } else {
    Serial.println("NAK");
  }
  
}


void printVariables() {
  Serial.println("gpioPin: " + String(gpioPin));
  Serial.println("outputPin: " + String(outputPin));
  Serial.println("trigger:" + String(triggerCondition));
  Serial.println("pulseDelay: " + String(pulseDelay) + " ns");
  Serial.println("pulseWidth: " + String(pulseWidth) + " ns");
  Serial.println("pulseTimeout: " + String(pulseTimeout) + " ms");
  Serial.println();
}

