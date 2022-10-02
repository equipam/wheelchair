import logging

class Logger:
    def __init__(self, level: str) -> None:
        
        if level == "DEBUG":
            logging_level = logging.DEBUG
        elif level == "INFO":
            logging_level = logging.INFO
        elif level == "WARNING":
            logging_level = logging.WARNING
        elif level == "ERROR":
            logging_level = logging.ERROR
        elif level == "CRITICAL":
            logging_level = logging.CRITICAL
        else:
            logging_level = logging.DEBUG

        logging.basicConfig(format='%(asctime)s - %(message)s', level=logging_level)

    def debug(self, message):
        logging.debug(message)

    def info(self, message):
        logging.info(message)

    def warning(self, message):
        logging.warning(message)

    def error(self, message):
        logging.error(message)

    def critical(self, message):
        logging.critical(message)
