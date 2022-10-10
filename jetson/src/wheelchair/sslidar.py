from wheelchair.driver.sslidar_file_api import SSLidarDriver

class SSLidar:
    def __init__(self, driver: SSLidarDriver, threshold: float) -> None:
        self._driver = driver
        self._collision_threshold = threshold
        pass

    @property
    def distance(self):
        # TODO #14 Create function that gets the distance from Lidar
        pass

    @property
    def collision(self):
        return self.distance >= self._collision_threshold