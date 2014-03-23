from distutils.command.install import install

print "System Initializing"

import sys
from felAutonamousStateMachine import felAutonamousStateMachine
try:
    sys.path.insert(0, "../networkProtocol")
    import netProtocol
    # import heartBeatMonitor
    print "Successfully Imported Network"
    sys.path.insert(0, "../general")
    from device import device
    from log import logger
    print "Successfully Imported Device"
except ImportError:
    print "Could not import components, terminating program"
    sys.exit()

# Front End Loader Main
#
#

myDevice = device(device.DEVICE_ID_FEL)

# Setup Network Components
print "attempting to open a connection"
myDevice.netManager = netProtocol.netManager("FEL", False)
# myDevice.heartbeatMonitor = heartBeatMonitor.heartBeatMonitor(myDevice)
print "connection established"

# Setup Hardware Components
# TODO: Write this when I have access to the robot


# TODO: Start off another thread(s) to gather/record sensor data


# setup the autonomous state machine
brain = felAutonamousStateMachine()

# Enter Main Loop
while True:

    inboundData = myDevice.netManager.recv()

    # Did we get a message?
    if inboundData is not None:
        print "Received Command: " + inboundData

        arguments = inboundData.split(" ")

        try:

            if arguments[0] == "quit":
                break

            if arguments[0] == "set":
                if arguments[1] == "state":
                    try:
                        newState = int(arguments[2])
                        brain.state = newState
                        print "Setting autonomous state to " + str(newState)
                    except ValueError:
                        print "Invalid state"

                if arguments[1] == "mode":
                    try:
                        newMode = int(arguments[2])
                        myDevice.deviceMode = newMode
                        print "Setting device mode to " + str(newMode)
                    except ValueError:
                        print "Invalid state"

            if arguments[0] == "get":
                if arguments[1] == "state":
                    myDevice.netManager.send(str(brain.getState()), "hub")

                if arguments[1] == "mode":
                    myDevice.netManager.sendAll(str(myDevice.deviceMode))

            # TODO: check if the message is telling us to E-Stop
            # TODO: check if the message is telling us to switch mode
            # TODO: check if this is a heartbeat message

            if myDevice.deviceMode == myDevice.MODE_MANUAL:
                # TODO: if this message is manual control commands then do what they say
                continue

        except IndexError:
            print "Invalid Command Received"

    # TODO: Check that no devices have timed out from heartbeat

    if myDevice.deviceMode == myDevice.MODE_MANUAL:
        # TODO: if no manual control command has been issued recently then stop
        continue

    if myDevice.deviceMode == myDevice.MODE_AUTONOMOUS:
        # preform autonomous operations
        brain.step()
        continue

    continue