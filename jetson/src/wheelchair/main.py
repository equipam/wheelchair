# TODO #8 Create jetson nano main routine logic

from typing import Optional
import typer
from wheelchair.sslidar_driver import SSLidarDriver
from wheelchair.sslidar import SSLidar
from wheelchair.arduino import Arduino

DEFAULT_COLLISION_THRESHOLD = 0.5
DEFAULT_STOP_PIN = 1

app = typer.Typer()


def check_collision(lidar: SSLidar, arduino: Arduino, verbose: bool):
    if lidar.collision and arduino.state is False:
        if verbose:
            print("Collision!")
        arduino.set_stop_signal(True)
    elif not lidar.collision and arduino.state is True:
        if verbose:
            print("Collision!")
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
