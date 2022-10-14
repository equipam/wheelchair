#TODO

from time import sleep
from wheelchair.arduino import Arduino

arduino = Arduino(18)

while True:
    print("Rise")
    arduino.set_stop_signal(True)
    sleep(5)
    print("Fall")
    arduino.set_stop_signal(False)
    sleep(5)