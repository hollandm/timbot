import sys, re
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


destinationDevice = device.DEVICE_ID_ALL
promptMessage = device.DEVICE_NAMES[destinationDevice]



# Setup Network Components
print "attempting to open a connection"
netManager = netProtocol.netManager("CC", True, 1)

print "Starting Robotics Command Console"

while True:

    try:

        command = raw_input(promptMessage+"$ ")
        command = command.strip().lower()

        args = command.split(" ")

        if args[0] == "quit":
            netManager.sendAll("stop")
            netManager.sendAll("quit")
            break

        # Select a robot to send commands to
        if args[0] == "select":
            # TODO: Select a robot
            print args[1]

        print "presanity check"
        netManager.sendAll(command)

        print "sanity check"
        # if args[0] == "get":
        #     if len(args) == 2:
        #         if args[1] == "state":
        #             newState = netManager.recv()
        #             print "Autonomous state: " + str(newState)

    except IndexError:
        print "Invalid Command Entered"