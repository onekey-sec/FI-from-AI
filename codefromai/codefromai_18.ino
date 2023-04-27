import serial
from TeensyTrigger import TeensyTrigger

# set up serial connection
ser = serial.Serial('COM3', 9600, timeout=1)

# create TeensyTrigger instance
tt = TeensyTrigger(ser)

# set GPIO and output pins
tt.set_gpio_pin(1)
tt.set_output_pin(3)

# set trigger condition to rising edge
tt.set_trigger_condition(tt.RISING)

# set pulse delay and width
tt.set_pulse_delay(50)
tt.set_pulse_width(50)

# set pulse timeout
tt.set_pulse_timeout(100000)

# enable interrupt
if tt.enable():
    print("Interrupt enabled!")
else:
    print("Failed to enable interrupt.")

# trigger interrupt
if tt.trigger():
    print("Interrupt triggered!")
else:
    print("Failed to trigger interrupt.")
