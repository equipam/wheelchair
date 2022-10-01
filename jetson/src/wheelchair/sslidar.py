from wheelchair.sslidar_driver import SSLidarDriver

class SSLidar:
    def __init__(self, driver: SSLidarDriver, threshold: float) -> None:
        self._driver = driver
        self._collision_threshold = threshold
        pass

    @property
    def distance(self):
        # TODO Create function that gets the distance from Lidar
        pass

    @property
    def collision(self):
        return self.distance >= self._collision_threshold