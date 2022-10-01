#TODO #4 Create interface between Jetson Nano and Arduino

import Jetson.GPIO as GPIO       #Necessary inicial set up

class Arduino:
    def __init__(self, pin_number) -> None:
        # setup pin
        self._output_pin = pin_number  #Pin 18 advised (SPI Communication) -- board Pin number 12
        self.state = False
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self._output_pin, GPIO.OUT, initial=GPIO.LOW)

    def set_stop_signal(self, state: bool):        
        # interface with pin
        if state == True:
            try:
                GPIO.output(self._output_pin, GPIO.HIGH)
                self.state = True
            finally:
                GPIO.cleanup()
        else:
            try:
                GPIO.output(self._output_pin, GPIO.LOW)
                self.state = False
            finally:
                GPIO.cleanup()