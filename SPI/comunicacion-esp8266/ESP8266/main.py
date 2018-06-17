import machine
import time

D0 = 16
D1 = 5
D2 = 4
D3 = 0
D4 = 2
D5 = 14
D6 = 12
D7 = 13
D8 = 15

hspi = machine.SPI(1, polarity=0, phase=0)
hspi.init(baudrate=1000000)  # set the baudrate


led = machine.Pin(D4)
pwm = machine.PWM(led)
pwm.freq(500)

for i in range(0, 1024):
    pwm.duty(i)
    time.sleep_ms(20)

pwm.duty(0)

# MASTER
SS = machine.Pin(D8, machine.Pin.OUT)
# SLAVE
# SS = machine.Pin(D8, machine.Pin.IN)

buf = bytearray(1)     # create a buffer
a = 1
while a:
    if SS.value:
        hspi.readinto(buf, bytes(int(buf, base=2) + 1))
        data = int.from_bytes(buf, byteorder='big')
        pwm.duty(data * 4)
