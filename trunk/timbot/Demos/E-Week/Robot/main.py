__author__ = 'matt'


import motorCommands
import networkReciever
import time
import autonomyDemo

# Network socket for recieving commands
net = networkReciever.networkReciever()
net.openClientSocket()

# Open a serial connection to the motors
con = motorCommands.motorController('/dev/ttyUSB0')

# Open a serial connection to the arduino for autonpmous testing
aiController = autonomyDemo.autoDriveUntil('/dev/ttyACM0', con)

# Some number that makes the motors go faster
motorSpeedMod = 5000

# Main loop
while True:

    command = net.getData()

    # If we recieved a packet then look at it
    if command is not None:

        # Did we get a Reset Motors/E-Stop Command?
        if command[6] > 0:
            con.stopLeft()
            con.stopRight()

            con.reset()

            # Terminate "autonomous" functionality
            aiController.autonomousStage = 0

        # If the robot is trying to be autonomous, ignore any movement commands from the user
        if aiController.autonomousStage == 0:
            leftSpeed = (50-command[2])*motorSpeedMod
            # Drive the Right wheels
            con.driveLeft(leftSpeed)

            rightSpeed = (50-command[0])*motorSpeedMod*-1
            con.driveRight(rightSpeed)

            print str(leftSpeed) + " " + str(rightSpeed)

            # The left trigger will enable autonomous mode
            if command[5] > 0:
                if aiController.autonomousStage == 0:
                    print "Beginning Autonomous Operations"
                    aiController.autonomousStage = 1

        # Clear out the network buffer
        while net.getData() is not None:
            continue

    # Do autonomous things, like driving forward until you are about to hit something
    if aiController.autonomousStage > 0:
        aiController.doThings()

    # Sleep so that we don't overflow the serial buffer to the motors
    time.sleep(0.1)


con.close()
net.sock.close()

