#TODO

from time import sleep
from wheelchair.arduino import Arduino

arduino: Arduino
with Arduino(18) as arduino:
    while True:
        print("Rise")
        arduino.set_stop_signal(True)
        sleep(0.5)
        print("Fall")
        arduino.set_stop_signal(False)
        sleep(0.5)