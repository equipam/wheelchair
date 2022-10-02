class Arduino:
    state: bool
    def __init__(self, pin_number) -> None:
        self.state = False
    def set_stop_signal(self, state: bool):
        self.state = state