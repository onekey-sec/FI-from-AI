int gpioPin = 2; // replace with the GPIO pin number you're using
int outputPin = 3; // replace with the Arduino pin number you're using for output
int pulseDelay = 1000; // initial delay of 1000 microseconds
int pulseWidth = 500; // initial pulse width of 500 microseconds

void setup() {
  pinMode(gpioPin, INPUT);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  if (digitalRead(gpioPin) == HIGH) { // check if trigger occurred
    digitalWrite(outputPin, HIGH); // send the pulse
    delayMicroseconds(pulseWidth);
    digitalWrite(outputPin, LOW);
    delayMicroseconds(pulseDelay);
  }
}
