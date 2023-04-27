import serial
import time

class TeensyPulseGenerator:
    def __init__(self, port, baudrate=9600):
        self.ser = serial.Serial(port, baudrate, timeout=1)
        time.sleep(2) # wait for serial to initialize
        self.ser.flushInput()
        self.ser.flushOutput()
        print("Teensy Pulse Generator initialized on port", port)

    def set_gpio_pin(self, gpio_pin):
        self.ser.write(('GPIO' + str(gpio_pin)).encode())
        response = self.ser.readline().decode().strip()
        if response == 'OK':
            print("GPIO pin set to", gpio_pin)
        else:
            print("Error setting GPIO pin:", response)

    def set_output_pin(self, output_pin):
        self.ser.write(('OUT' + str(output_pin)).encode())
        response = self.ser.readline().decode().strip()
        if response == 'OK':
            print("Output pin set to", output_pin)
        else:
            print("Error setting output pin:", response)

    def set_trigger_condition(self, trigger_condition):
        self.ser.write(('TRIG' + str(trigger_condition)).encode())
        response = self.ser.readline().decode().strip()
        if response == 'OK':
            print("Trigger condition set to", trigger_condition)
        else:
            print("Error setting trigger condition:", response)

    def set_pulse_delay(self, pulse_delay):
        self.ser.write(('DELAY' + str(pulse_delay)).encode())
        response = self.ser.readline().decode().strip()
        if response == 'OK':
            print("Pulse delay set to", pulse_delay)
        else:
            print("Error setting pulse delay:", response)

    def set_pulse_width(self, pulse_width):
        self.ser.write(('WIDTH' + str(pulse_width)).encode())
        response = self.ser.readline().decode().strip()
        if response == 'OK':
            print("Pulse width set to", pulse_width)
        else:
            print("Error setting pulse width:", response)

    def generate_pulse(self):
        self.ser.write('PULSE'.encode())
        response = self.ser.readline().decode().strip()
        if response == 'OK':
            print("Pulse generated")
        else:
            print("Error generating pulse:", response)

    def print_status(self):
        self.ser.write('STATUS'.encode())
        response = self.ser.readline().decode().strip()
        if response.startswith('GPIO'):
            gpio_pin = response[4:]
            response = self.ser.readline().decode().strip()
        if response.startswith('OUT'):
            output_pin = response[3:]
            response = self.ser.readline().decode().strip()
        if response.startswith('TRIG'):
            trigger_condition = response[4:]
            response = self.ser.readline().decode().strip()
        if response.startswith('DELAY'):
            pulse_delay = response[5:]
            response = self.ser.readline().decode().strip()
        if response.startswith('WIDTH'):
            pulse_width = response[5:]
            print("GPIO pin:", gpio_pin)
            print("Output pin:", output_pin)
            print("Trigger condition:", trigger_condition)
            print("Pulse delay:", pulse_delay)
            print("Pulse width:", pulse_width)
        else:
            print("Error getting status:", response)
