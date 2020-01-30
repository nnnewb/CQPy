import logging
from cqpy import cqp


class CQHandler(logging.Handler):
    def emit(self, record: logging.LogRecord):
        cqp.add_log(record.levelno, cqp.APP_ID, record.message)
