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

selectedDevice = None

print "Starting Robotics Command Console"

while True:

    try:

        if selectedDevice is not None:
            promptMessage = selectedDevice
        else:
            promptMessage = "Robots"

        command = raw_input(promptMessage+"$ ")
        command = command.strip().lower()

        args = command.split(" ")

        if args[0] == "quit":
            netManager.sendAll("stop")
            netManager.sendAll("quit")
            break

        # Select a robot to send commands to
        if args[0] == "select":
            if args[1] in netManager.connections:
                selectedDevice = args[1]
            else:
                selectedDevice = None
            continue

        if args[0] == "set":

            if args[1] == "mode":
                if args[2] == "manual":
                    args[2] = str(device.MODE_MANUAL)
                elif args[2] == "autonomous":
                    args[2] = str(device.MODE_AUTONOMOUS)
                else:
                    args[2] = str(device.MODE_STANDBY)

                command = " ".join(args)

        netManager.send(command, selectedDevice)

        if args[0] == "get":

            if args[1] == "state":
                newState = netManager.recv()
                print "Autonomous state: " + str(newState)

            if args[1] == "mode":
                newMode = netManager.recv()
                # print "received: " + newMode
                if newMode == device.MODE_MANUAL:
                    print "Device Mode: Manual"
                elif newMode == device.MODE_AUTONOMOUS:
                    print "Device Mode: Autonomous"
                else:
                    print "Device Mode: Standby"

    except IndexError:
        print "Invalid Command Entered"
