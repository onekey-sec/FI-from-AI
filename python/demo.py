import serial
import FIfromAI
import time
import random

## edge types
RISING = 3 
FALLING = 2
CHANGE = 4

# create FIfromAI instance
tt = FIfromAI.FIfromAI('COM14', 115200, timeout=1)

# serial target
# double check timeout corresponding to the glitcher timeout

ser = serial.Serial('COM11', 115200,timeout=0.5) 

# set GPIO and output pins
tt.set_gpio_pin(1)
tt.set_output_pin(11)

# set trigger condition to rising edge
tt.set_trigger_condition(RISING)

# set pulse delay and width
tt.set_pulse_delay(50)
tt.set_pulse_width(10000)

# set range
min_delay = 100
max_delay = 1000
min_width = 100
max_width = 10000

# set pulse timeout
tt.set_pulse_timeout(1000)
print(tt.print_variables())
rcount = 0
gcount = 0
while(1):

    #send random values to delay and width
    tt.set_pulse_delay(random.randint(min_delay,max_delay))
    tt.set_pulse_width(random.randint(min_width,max_width))
    # enable glitching
    gcount = gcount+1
    tt.enable()
    # send A to serial to start operation
    ser.write(b'A')
    # check if glitched or timedout
    timeout = tt.check()
##    if timeout == 0:
##        rcount = rcount+1
##        if rcount > 5:
##		# reset the target if it times out too much
##            tt.t_reset(100)
##            time.sleep(1)
##            rcount = 0
##            #print("inreset")
##        #print("timeout:" + str(timeout))
##        #print(tt.print_variables())
    result=ser.readline()
    if result == b'data\r\n' or result == b'':  # replace it with your expected data
        print(">>",gcount,"<<")
        # continue:
    else:
        
        print("Glitched")
        print("Output: ", result)
        print(tt.print_variables())
        #exit(0) # do your thing here to either exit the script or loop back

