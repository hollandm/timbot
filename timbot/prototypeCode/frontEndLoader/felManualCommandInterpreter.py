import time
import sys
try:
    sys.path.insert(0, "../general")
    from device import device
    from log import logger
    print "Successfully Imported Device"
except ImportError:
    print "Could not import components, terminating program"
    sys.exit()


##
# felManualCommandInterpreter
#
class felManualCommandInterpreter:

    def __init__(self, deviceInfo):
        #TODO: Comment what these are!
        self.targetVel = 0
        self.lastCommandReceived = 0

        self.stopAt = 0
        self.driving = False

        self.deviceInfo = deviceInfo

        self.motors = deviceInfo.getActuator("motors")
        return

    ##
    # interpret
    #
    # Description: interpret a given command, if it is valid then execute the command
    #
    def interpret(self, command):
        print "interpreting"
        # TODO: determine what commands to use for manual control
        command = command.lower()

        split = command.split(" ")

        try:
            print split

            if split[0] == "reset":
                self.driving = False
                self.motors.stopLeft()
                self.motors.stopRight()
                self.motors.reset()

            if split[0] == "stop":
                self.driving = False
                self.motors.stopLeft()
                self.motors.stopRight()

            if split[0] == "drive":
                velocity = split[1]
                seconds = split[2]

                self.driving = True
                self.stopAt = time.time() + float(seconds)
                print "Stop at time: " + str(self.stopAt)
                print "Current time: " + str(time.time())

                self.motors.driveLeft(int(velocity))
                self.motors.driveRight(-1*int(velocity))

                return

            if split[0] == "rotate":
                magnitude = int(split[1])*-1
                seconds = split[2]

                self.driving = True
                self.stopAt = time.time() + float(seconds)

                self.motors.driveLeft(magnitude)
                self.motors.driveRight(magnitude)

                return

        except IndexError:
            print "Invalid argument"

        # TODO: if not a valid command don't do anything
        # TODO: otherwise set lastCommandReceived to be the current time

        return

    ##
    # checkTimeout
    #
    # Description: if the timeout for a command has been reached then stop movement
    def checkTimeout(self):
        # print time.time()
        if self.stopAt <= time.time() and self.driving == True:
            print "stopping"
            self.motors.stopLeft()
            self.motors.stopRight()
            self.driving = False
