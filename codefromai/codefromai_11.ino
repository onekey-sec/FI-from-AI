const int MAX_SERIAL_INPUT = 50;
const unsigned long INTERRUPT_TIMEOUT = 10000UL; // 10ms
int gpioPin = 1;
int outputPin = 3;
int triggerCondition = RISING;
unsigned long pulseDelay = 50; // delay of 50 nanoseconds
unsigned long pulseWidth = 50; // pulse width of 50 nanoseconds

volatile unsigned long pulseStartTime = 0; // start time of pulse
volatile bool pulseActive = false; // flag indicating whether pulse is currently active

void setup() {
  Serial.begin(115200);
  pinMode(outputPin, OUTPUT);
  pinMode(gpioPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, triggerCondition); // attach interrupt to GPIO pin
}

void loop() {
  // read serial input and parse command
  if (Serial.available() > 0) {
    char input[MAX_SERIAL_INPUT];
    int index = 0;
    while (Serial.available() > 0 && index < MAX_SERIAL_INPUT-1) {
      char c = Serial.read();
      if (c == '\n') {
        input[index] = '\0'; // terminate string
        break;
      }
      input[index++] = c;
    }
    input[index] = '\0';
    parseCommand(input);
  }
}

void parseCommand(char* input) {
  char* command = strtok(input, " ");
  if (strcmp(command, "gpio") == 0) {
    char* value = strtok(NULL, " ");
    gpioPin = atoi(value);
    pinMode(gpioPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, triggerCondition); // attach interrupt to GPIO pin
    Serial.print("GPIO set to ");
    Serial.println(gpioPin);
  } else if (strcmp(command, "out") == 0) {
    char* value = strtok(NULL, " ");
    outputPin = atoi(value);
    pinMode(outputPin, OUTPUT);
    Serial.print("Output pin set to ");
    Serial.println(outputPin);
  } else if (strcmp(command, "trig") == 0) {
    char* value = strtok(NULL, " ");
    triggerCondition = (strcmp(value, "RISING") == 0) ? RISING : FALLING;
    detachInterrupt(digitalPinToInterrupt(gpioPin));
    attachInterrupt(digitalPinToInterrupt(gpioPin), triggerInterrupt, triggerCondition); // attach interrupt to GPIO pin
    Serial.print("Trigger condition set to ");
    Serial.println(value);
  } else if (strcmp(command, "delay") == 0) {
    char* value = strtok(NULL, " ");
    pulseDelay = atol(value);
    Serial.print("Pulse delay set to ");
    Serial.print(pulseDelay);
    Serial.println(" ns");
  } else if (strcmp(command, "width") == 0) {
    char* value = strtok(NULL, " ");
    pulseWidth = atol(value);
    Serial.print("Pulse width set to ");
    Serial.print(pulseWidth);
    Serial.println(" ns");
  } else {
    Serial.println("Invalid command");
  }
}

void triggerInterrupt() {
  if (!pulseActive) { // only start pulse if not already active
    pulseStartTime = micros();
    pulseActive = true;
    delayNanoseconds(pulseDelay);
    digitalWriteFast(outputPin, HIGH);
    delayNanoseconds(pulseWidth);
    digitalWriteFast(outputPin, LOW
