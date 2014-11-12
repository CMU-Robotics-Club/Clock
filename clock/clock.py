import serial
import datetime
import time
import struct
import logging

class Clock(object):

  def __init__(self, port='/dev/ttyUSB0'):
    self._logger = logging.getLogger()
    self._serial = serial.Serial(port=port)

  def clear(self):
    self._serial.write('\n'.encode())
  
  def set_position(self, i):
    self._serial.write('\x1B{}'.format(struct.pack('b', i)))

  def write(self, m, delay=0.4):
    self.clear()

    if len(m) > self._MAX_CHARACTERS:
      s = m[:self._MAX_CHARACTERS]
      self._serial.write(s.encode())
      time.sleep(delay)
      self.write(m[1:], delay)
    else:
      self._serial.write(s.encode())

  def write_time(self):
    now = datetime.datetime.now()
    s = now.strftime()
    self.write(s)

  # Private

  _MAX_CHARACTERS = 19
