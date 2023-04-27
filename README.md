# FI-from-AI

AI-built Teensy Fault Injection Framework

This is an AI-built framework for Teensy-based fault injection. The framework uses a Teensy microcontroller and a Python application to create controlled faults in target devices. The project includes both hardware and software components.

## Getting Started

### Hardware Setup

To use the framework, you will need a Teensy microcontroller and a target device. The Teensy board should be connected to the target device using appropriate wiring. Additionally, the board should be programmed with the firmware provided in the repository using the Arduino IDE. 

### Software Setup
The software components of the framework include the firmware for the Teensy board and a Python library for computer-side control. To use the framework, you will need to install the following:

- Arduino IDE for programming the Teensy board (Compatible with all Arduino supported platform)
- Python 3.x for running the computer-side control library
- Python Serial Library

### Usage

To use the framework, follow these steps:

- Connect the Teensy board to the target device using appropriate cable.
- Program the Teensy board with the firmware provided in the repository using the arduino IDE. For more precise timing, you can try different compiler optimisation in the IDE. 

Import the Python library and use it to control the fault injection process.

```python
tt = FIfromAI.FIfromAI('COM14', 115200, timeout=1) // Creating the Class on the COM Port

# serial target
ser = serial.Serial('COM11', 115200,timeout=0.5) // COMx or /dev/ttyUSBxx based on the OS

# set GPIO and output pins
tt.set_gpio_pin(1)   // GPIO 1 is the Trigger input pin
tt.set_output_pin(11) // GPIO 1 is the Pulse output pin

# set trigger condition to rising edge
tt.set_trigger_condition(RISING)  // The trigger occurs on RISING or FALLING or CHANGE

# set pulse delay and width
tt.set_pulse_delay(random.randint(100,500))  // Delay from the trigger to the pulse
tt.set_pulse_width(random.randint(100,5000)) // Pulse width

# set pulse timeout
tt.set_pulse_timeout(1000)  // How long does the device need to wait for the trigger
print(tt.print_variables()) // print all the hardware variables

# Start the glitch 
tt.enable()

# check if the glitch was successfull or timeout
tt.check()

# Reset the target 
tt.t_reset(100)  // this goes to the reset line of the target. This is hardcoded in the code as Active Low and GPIO 9. 
```

## Contributing

If you'd like to contribute to the project, please follow these steps:

- Fork the repository.
- Make your changes.
- Submit a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

This project was inspired by the work of many researchers in the field of fault injection. We thank them for their contributions to the field.
