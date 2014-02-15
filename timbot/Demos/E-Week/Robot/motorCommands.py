import serial, time


class motorController:

    allAddress = chr(128) + " "
    leftAddress = chr(129) + " "
    rightAddress = chr(130) + " "

    ##
    # __init__
    #
    # Description: Constructor initializes the serial connection to the motor
    #
    # Parameters:
    #  motorPath: File path of the serial port
    #
    def __init__(self, motorPath):
        self.serialPort = serial.Serial(motorPath)

        self.write("ZS ")
        self.write("MV ")
        self.write("EIGN(2) ")
        self.write("EIGN(3) ")
        self.write("ADT=100 ")

    ##
    # write
    #
    # Description: sends a command to the motors while ensuring
    #   the command has a single trailing whitespace
    #
    # Parameters:
    #   command: the command to send to the motors
    def write(self, command):
        command = command.strip() + " "
        self.serialPort.write(command)

        # Don't do it this way. Otherwise we will forget this is happening
        # when we are trying to debug it
        #time.sleep(self.delayTime)


    ##
    # driveLeft
    #
    # Description: sets the velocity of the left wheels
    #
    # Parameters:
    #   velocity: speed for the motors to go (Units Unknown)
    #
    def driveLeft(self, velocity):

        # address the left wheels
        self.write(self.leftAddress)

        self.write("VT=" + str(velocity) + " ")
        self.write("G ")

    ##
    # driveRight
    #
    # Description: sets the velocity of the right wheels
    #
    # Parameters:
    #   velocity: speed for the motors to go (Units Unknown)
    #
    def driveRight(self, velocity):

        # address the right wheels
        self.write(self.rightAddress)

        self.write("VT=" + str(velocity) + " ")
        self.write("G ")


    ##
    # stopLeft
    #
    # Description: stops the left wheels
    #
    # Parameters:
    #   None
    #
    def stopLeft(self):

        # address the left wheels
        self.write(self.leftAddress)
        self.write("S ")

    ##
    # stopRight
    #
    # Description: stops the left wheels
    #
    # Parameters:
    #   None
    #
    def stopRight(self):

        # address the left wheels
        self.write(self.rightAddress)
        self.write("S ")

    ##
    # reset
    #
    # Description: Resets the motors
    #
    # Parameters:
    #   None
    #
    def reset(self):
        self.write(self.allAddress)
        self.write("ZS ")

    ##
    # close
    #
    # Description: Stops the motors and closes the serial port
    #
    # Parameters:
    #   None
    #
    def close(self):
        self.stopLeft()
        self.stopRight()
        self.serialPort.close()


# Test Code
#
# Runs the robot forward for 5 seconds and then stops
#
con = motorController('/dev/ttyUSB0')
con.driveLeft(1000)
con.driveRight(-1000)

time.sleep(5)

con.stopLeft()
con.stopLeft()
con.close()



