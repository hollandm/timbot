##
# This program has the robot drive forward for 10 seconds.
#
# It needs to control each side of wheels individually since they turn
#

import serial, time

serialPort = serial.Serial('/dev/ttyUSB0')

print serialPort.portstr

# set up
serialPort.write("ZS ")
time.sleep(0.1)
serialPort.write("MV ")
time.sleep(0.1)
serialPort.write("EIGN(2) ")
time.sleep(0.1)
serialPort.write("EIGN(3) ")
time.sleep(0.1)
serialPort.write("ADT=100 ")
time.sleep(0.1)

#this is a comment example

# move one side of wheels
serialPort.write(chr(129)+" ")
time.sleep(0.1)
serialPort.write("VT=100000 ")
time.sleep(0.1)
serialPort.write("G ")
time.sleep(0.1)

# move the other side of wheels
serialPort.write(chr(130)+" ")
time.sleep(0.1)
serialPort.write("VT=-100000 ")
time.sleep(0.1)
serialPort.write("G ")
time.sleep(0.1)

# wait 10 seconds
time.sleep(10)

# stop both sides
serialPort.write("S ")
serialPort.write(chr(129)+" ")
time.sleep(0.1)
serialPort.write("S ")


serialPort.close()