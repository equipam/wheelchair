import os
from typing import Optional
import typer
from wheelchair.sslidar_driver import SSLidarDriver
from wheelchair.sslidar import SSLidar
from wheelchair.logger import Logger

# Do this conditional import to avoid importing Jetson Nano GPIO library
if os.getenv("TESTING") == "TRUE":
    from wheelchair.testrig.fake_arduino import Arduino
else:
    from wheelchair.arduino import Arduino

DEFAULT_COLLISION_THRESHOLD = 0.5
DEFAULT_STOP_PIN = 1

app = typer.Typer()

logger = Logger(os.getenv("LOGGING"))

def check_collision(lidar: SSLidar, arduino: Arduino, verbose: bool):
    logger.debug(f"{lidar.collision=} | {arduino.state=}")
    if lidar.collision and arduino.state is False:
        if verbose:
            logger.info("Collision!")
        arduino.set_stop_signal(True)
    elif not lidar.collision and arduino.state is True:
        if verbose:
            logger.info("Not colliding anymore!")
        arduino.set_stop_signal(False)
    return


@app.command()
def main(
    threshold: float = DEFAULT_COLLISION_THRESHOLD,
    stop_pin: int = DEFAULT_STOP_PIN,
    once: Optional[bool] = False,
    verbose: Optional[bool] = False,
):
    driver = SSLidarDriver()
    lidar = SSLidar(driver, threshold)
    arduino = Arduino(stop_pin)

    if once:
        check_collision(lidar, arduino, verbose)
        raise typer.Exit(0)

    while True:
        check_collision(lidar, arduino, verbose)
        pass


if __name__ == "__main__":
    app()
