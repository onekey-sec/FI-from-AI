import serial
import time


class FIfromAI:
    def __init__(self, port, baudrate=115200, timeout=1):
        self.ser = serial.Serial(port, baudrate=baudrate, timeout=timeout)

    def __del__(self):
        if self.ser.isOpen():
            self.ser.close()

    def set_gpio_pin(self, pin):
        self.ser.write(('gpioPin' + str(pin) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'

    def set_output_pin(self, pin):
        self.ser.write(('outputPin' + str(pin) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'

    def set_pulse_delay(self, delay):
        self.ser.write(('pulseDelay' + str(delay) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'

    def set_pulse_width(self, width):
        self.ser.write(('pulseWidth' + str(width) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'

    def set_pulse_timeout(self, timeout):
        self.ser.write(('pulseTimeout' + str(timeout) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'

    def t_reset(self, width):
        self.ser.write(('tReset' + str(width) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'

    def set_trigger_condition(self, condition):
        self.ser.write(('trigger' + str(condition) + '\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'
    def enable(self):
        self.ser.write(('enable\n').encode())
        response = self.ser.readline().decode().rstrip()
        return response == 'OK'
    def check(self):
        response = self.ser.readline().decode().rstrip()
        ##print(response)
        return response == 'AOK'
    def print_variables(self):
        self.ser.write(('print\n').encode())
        response = ''
        while not response.endswith('\r\n\r\n'):
            response += self.ser.readline().decode()
        return response.rstrip()

