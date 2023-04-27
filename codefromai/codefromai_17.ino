teensy = Teensy("/dev/ttyACM0")
teensy.set_gpio_pin(1)
teensy.set_output_pin(3)
teensy.set_pulse_delay(50)
teensy.set_pulse_width(50)
teensy.set_pulse_timeout(100000)
teensy.set_trigger_condition(0)
teensy.enable_interrupt()
time.sleep(1)
response = teensy.print_variables()
print(response)
