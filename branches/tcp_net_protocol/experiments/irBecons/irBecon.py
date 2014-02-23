##
# This program has the robot drive forward for 10 seconds.
#
# It needs to control each side of wheels individually since they turn
#

import serial, time

serialPort = serial.Serial('/dev/ttyUSB0')
arduinoPort = serial.Serial('/dev/ttyACM0')


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



def turnRight():
    print "Turn Right"
    serialPort.write(chr(129)+" ")
    time.sleep(0.1)
    serialPort.write("VT=-100000 ")
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
 
    return

def turnLeft():
    print "Turn Left"
    # move the other side of wheels
    serialPort.write(chr(130)+" ")
    time.sleep(0.1)
    serialPort.write("VT=100000 ")
    time.sleep(0.1)
    serialPort.write("G ")
    time.sleep(0.1)
    
    serialPort.write(chr(129)+" ")
    time.sleep(0.1)
    serialPort.write("VT=100000 ")
    time.sleep(0.1)
    serialPort.write("G ")
    time.sleep(0.1)



    return

def stop():
    print "Stop"

    # stop both sides
    serialPort.write("S ")
    serialPort.write(chr(129)+" ")
    time.sleep(0.1)
    serialPort.write("S ")
    return

while True:
    input = arduinoPort.readline().strip()

    directions = input.split(", ")

    if len(directions) != 4:
        continue


    forword = int(directions[2])
    backword = int(directions[3])
    left = int(directions[1])
    right = int(directions[0])

    print directions


    if left < 100:
        turnLeft()
    elif backword < 100:
        turnRight()
    elif forword < 100:
        turnRight()
    else:
        stop()


# #this is a comment example
#
# # move one side of wheels

#

# # wait 10 seconds
# time.sleep(10)
#

arduinoPort.close()
serialPort.close()
