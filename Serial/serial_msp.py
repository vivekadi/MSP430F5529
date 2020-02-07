import serial
import time

msp = serial.Serial("/dev/ttyUSB0",9600)

while 1:
	msp.write(b'a')
	print("Led on")
	time.sleep(2)

	msp.write(b'b')
	print("Led_off")
	time.sleep(2)

msp.close()





 
