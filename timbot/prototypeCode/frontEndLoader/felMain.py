
print "System Initializing"

import sys
from felAutonomousStateMachine import felAutonomousStateMachine
from felManualCommandInterpreter import felManualCommandInterpreter
try:
    sys.path.insert(0, "../networkProtocol")
    import netProtocol
    print "Successfully Imported Network"
    sys.path.insert(0, "../general")
    from device import device
    from log import logger
    print "Successfully Imported Device"
    sys.path.insert(0, "../hardwareInterfaces")
    from animaticsMotors import motorController
    print "Successfully Imported "
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
print "connection established"

# Setup Hardware Components
motors = motorController("/dev/ttyUSB0")
myDevice.addActuator("motors", motors)
# TODO: Open lines of communication with arduino

# TODO: Start off another thread(s) to gather/record sensor data


# setup the autonomous state machine
auto = felAutonomousStateMachine()
manual = felManualCommandInterpreter()

# Enter Main Loop
while True:

    # import heartBeatMonitor
    # attempt to get a message from the command console via network
    inboundData = myDevice.netManager.recv()

    # Did we get a message?
    if inboundData is not None:
        print "Received Command: " + inboundData

        arguments = inboundData.split(" ")

        try:

            # Stop executing the for ever loop, quit out of program
            if arguments[0] == "quit":
                break

            # Set some value on the robot
            if arguments[0] == "set":
                if arguments[1] == "state":
                    try:
                        newState = int(arguments[2])
                        auto.state = newState
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

            # Return some value over the network
            if arguments[0] == "get":
                if arguments[1] == "state":
                    myDevice.netManager.send(str(auto.getState()), "hub")

                if arguments[1] == "mode":
                    myDevice.netManager.sendAll(str(myDevice.deviceMode))

            if myDevice.deviceMode == myDevice.MODE_MANUAL:
                manual.interpret(inboundData)
                continue

        except IndexError:
            print "Invalid Command Received"

    # TODO: Check that no devices have timed out from heartbeat

    if myDevice.deviceMode == myDevice.MODE_MANUAL:
        # if we are in manual mode then check if we need to stop moving
        manual.checkTimeout()
        continue

    if myDevice.deviceMode == myDevice.MODE_AUTONOMOUS:
        # preform autonomous operations
        auto.step()
        continue

    continue

# TODO: Once we have exited the loop cleanup all resources that we have opened/started