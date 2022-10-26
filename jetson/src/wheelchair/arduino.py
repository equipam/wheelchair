import Jetson.GPIO as GPIO       #Necessary inicial set up

class Arduino:
    def __init__(self, pin_number) -> None:
        # setup pin
        self._output_pin = pin_number  #Pin 18 advised (SPI Communication) -- board Pin number 12
        self.state = False

    def setup(self):
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self._output_pin, GPIO.OUT, initial=GPIO.LOW)

    def cleanup(self):
        GPIO.cleanup()

    def __enter__(self):
        self.setup()
        return self

    def __exit__(self, exc_type, exc_value, exc_traceback):
        print("GPIO Cleanup")
        del exc_type, exc_value, exc_traceback
        self.cleanup()

    def set_stop_signal(self, state: bool):        
        # interface with pin
        if state == self.state:
            return

        try:
            GPIO.output(self._output_pin, GPIO.HIGH if state else GPIO.LOW)
            self.state = state
        except Exception:
            self.cleanup()
            self.setup()