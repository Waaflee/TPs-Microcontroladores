from machine import Pin, SPI

hspi = SPI(1, baudrate=1000000, polarity=0, phase=0)
hspi.init(baudrate=1000000)  # set the baudrate


buf = bytearray(50)     # create a buffer

SS = Pin(4, Pin.IN, Pin.PULL_UP)
while 1:
    if SS.value:
        hspi.readinto(buf, 0xff)
        print(buf)
