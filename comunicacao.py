import serial
import time

diccom = {}
diccom["motor1"]=200
diccom["dir1"]=1
diccom["motor2"]=200
diccom["dir2"]=1
ser = serial.Serial('/dev/ttyUSB0', 9600)
msg = (str(diccom).encode('ASCII'))
time.sleep(2)
print(msg)
ser.write(msg)
time.sleep(2)

ser.close()
