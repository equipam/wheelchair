from glob import glob
import os
import pathlib
import signal
import subprocess

_FOLDER_PATH = pathlib.Path(__file__).parent.resolve()

class SSLidarDriver:
    def __init__(self) -> None:
        self._cpid = None
        self._data_file = None
        files = [path.replace(str(_FOLDER_PATH) + "/","") for path in glob(str(_FOLDER_PATH) + "/*")]
        if not "driver.out" in files:
            # Compile driver
            subprocess.run(
                [
                    "gcc",
                    "driver.c",
                    "-o",
                    "driver.out",
                    "-g",
                    "-Wall"
                    "-Wl,-rpath=./",
                    "-L./",
                    "-lhps3d_arm"
                ]
            )

    def __enter__(self):
        # Run driver and open data file
        self._cpid = os.spawnv(os.P_NOWAIT , str(_FOLDER_PATH) + "/" + "driver.out" )
        self._data_file = open(str(_FOLDER_PATH) + "/" + "data.txt", "r")
        return self

    def __exit__(self, type, value, traceback):
        # Kill driver and close data file
        os.kill(self._cpid, signal.SIGTERM)
        self._data_file.close()

    @property
    def data(self):
        """Returns data outputed from SSLidar C program"""
        if not self._data_file:
            raise Exception("Data file was not successfully open")
        return self._data_file.read()

driver = SSLidarDriver()
