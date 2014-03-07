import sys, re
try:
    sys.path.insert(0, "../networkProtocol")
    import client
    import server
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


print "Starting Robotics Command Console"

while True:

    try:

        command = raw_input(promptMessage+"$ ")
        command = command.strip().lower()

        args = command.split(" ")

        if args[0] == "quit":
            break

        # Select a robot to send commands to
        if args[0] == "select":
            # TODO: Select a robot
            print args[1]

        if args[0] == "drive":
            if args[1] == "forward":
                #
                print ""

        if args[0] == "stop":
            # TODO: Tell the selected robot to stop
            print ""

    except IndexError:
        print "Invalid Command Entered"