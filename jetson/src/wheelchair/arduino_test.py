#TODO

from time import sleep
from wheelchair.arduino import Arduino

arduino = Arduino(18)

while True:
    arduino.set_stop_signal(True)
    sleep(5)
    arduino.set_stop_signal(False)