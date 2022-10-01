#TODO #4 Create interface between Jetson Nano and Arduino

import JetsonNano.GPIO as GPIO       #Necessary inicial set up

class Arduino:
    def __init__(self, pin_number) -> None:
        # setup pin
        self.output_pin = pin_number  #Pin 18 advised (SPI Communication) -- board Pin number 12
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.output_pin, GPIO.OUT, initial=GPIO.LOW)

        pass

    def set_stop_signal(self, state: bool):        
        # interface with pin
        if state == True:
            try:
                GPIO.output(self.output_pin, GPIO.HIGH)
            finally:
                GPIO.cleanup()
                pass
        else:
            try:
                GPIO.output(self.output_pin, GPIO.LOW)
            finally:
                GPIO.cleanup()
                pass
            pass