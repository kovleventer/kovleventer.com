import serial

s = serial.Serial("/dev/ttyUSB0",
                    baudrate=1200,
                    bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_ODD,
                    stopbits=serial.STOPBITS_ONE)
