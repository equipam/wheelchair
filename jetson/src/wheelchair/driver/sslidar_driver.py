#TODO #15 Create SSLidar usb driver

import pathlib
import ctypes

_FOLDER_PATH = pathlib.Path(__file__).parent.resolve()

# Import C shared library that make the bridge to Lidar's C API
_C_API = ctypes.CDLL(str(_FOLDER_PATH) + "/liblidar.so")

# TODO Research ctypes library: find out how to define C struct types in Python

class SSLidarDriver:
    def __init__(self) -> None:
        pass
