const int gpioPin = 1; // replace with the GPIO pin number you're using
const int outputPin = 3; // replace with the Teensy pin number you're using for output

volatile unsigned long pulseDelay = 50; // delay of 50 nanoseconds
volatile unsigned long pulseWidth = 5; // pulse width of 5 nanoseconds
volatile unsigned long pulseStartTime = 0; // start time of pulse
volatile bool interruptEnabled = false;
volatile bool interruptTriggered = false;
unsigned long interruptEnableStartTime = 0;
unsigned long detachInterruptDelay = 1000; // detach interrupt if not triggered for 1000 microseconds
unsigned long detachInterruptStartTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT);
}

void loop() {
  if (interruptEnabled && !interruptTriggered) {
    if (micros() - interruptEnableStartTime > detachInterruptDelay) {
      detachInterrupt(digitalPinToInterrupt(gpioPin));
      interruptEnabled = false;
      Serial.println("Interrupt disabled");
    }
  }

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("gpioPin=")) {
      gpioPin = input.substring(8).toInt();
      pinMode(gpioPin, INPUT);
      Serial.println("gpioPin set to " + String(gpioPin));
    } else if (input.startsWith("outPin=")) {
      outputPin = input.substring(7).toInt();
      pinMode(outputPin, OUTPUT);
      Serial.println("outputPin set to " + String(outputPin));
    } else if (input.startsWith("trigger=")) {
      if (input.substring(8) == "rising") {
        attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING);
        Serial.println("Interrupt attached with rising edge trigger");
      } else if (input.substring(8) == "falling") {
        attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, FALLING);
        Serial.println("Interrupt attached with falling edge trigger");
      } else if (input.substring(8) == "change") {
        attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, CHANGE);
        Serial.println("Interrupt attached with change trigger");
      } else {
        Serial.println("Invalid trigger condition");
      }
    } else if (input.startsWith("delay=")) {
      pulseDelay = input.substring(6).toInt();
      Serial.println("Pulse delay set to " + String(pulseDelay) + " ns");
    } else if (input.startsWith("width=")) {
      pulseWidth = input.substring(6).toInt();
      Serial.println("Pulse width set to " + String(pulseWidth) + " ns");
    } else if (input == "enableInterrupt") {
      interruptEnabled = true;
      interruptTriggered = false;
      interruptEnableStartTime = micros();
      attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, RISING);
      Serial.println("Interrupt enabled");
    } else if (input.startsWith("detachDelay=")) {
      detachInterruptDelay = input.substring(13).toInt();
      Serial.println("Detach interrupt delay set to " + String(detachInterruptDelay) + " us");
    } else if (input == "printVars") {
      Serial.println("gpioPin: " + String(gpioPin));
      Serial.println("outputPin: " + String(outputPin));
      Serial.println("pulseDelay: " + String(pulseDelay
