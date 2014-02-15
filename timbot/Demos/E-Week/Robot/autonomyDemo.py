import serial

class autoDriveUntil:

    def __init__(self, serialPort, motorController):
        self.arduinoPort = serial.Serial(serialPort)
        self.motorController = motorController
        self.autonomousStage = 0
        return

    def doThings(self):
        # Begin driving forward, proceed to stage 2
        if self.autonomousStage == 1:
            self.motorController.driveLeft(100000)
            self.motorController.driveRight(-100000)
            self.autonomousStage = 2

        # Check that we aren't about to hit something, if we are then stop
        if self.autonomousStage == 2:
            if self.checkCollisionIminent() is True:
                print "Collision Iminent, Stopping"
                self.motorController.stopLeft()
                self.motorController.stopRight()
                self.autonomousStage = 0


        return

    def checkCollisionIminent(self):
        # Read IR sensor from the arduino
        input = self.arduinoPort.readline()

        try:
            val = int(input)
            print "Distance Detected: " + str(val)
            if val > 250:
                return True
            print val
        except:
		    doNothing = True

        return False
