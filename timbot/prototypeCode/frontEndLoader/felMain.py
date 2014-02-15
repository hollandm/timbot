import sys
try:
    sys.path.insert(0, "../networkProtocol")
    import client
    import server
    import netProtocol
    import heartBeatMonitor
    print "Successfully Imported Network"
    sys.path.insert(0, "../general")
    from device import device
    print "Successfully Imported Device"
except ImportError:
    print "Could not import components, terminating program"
    sys.exit()

# Front End Loader Main
#
#

myDevice = device(device.DEVICE_ID_FEL)

# Setup Network Components
myDevice.client = client.client(myDevice)
myDevice.server = server.server()
myDevice.heartbeatMonitor = heartBeatMonitor.heartBeatMonitor(myDevice)

# Setup Hardware Components
# TODO: Write this when I have access to the robot


# TODO: Start off another thread(s) to gather/record sensor data

# Enter Main Loop
while True:

    inboundData = myDevice.client.getData()

    if inboundData is not None:

        # TODO: check if the message is telling us to E-Stop
        # TODO: check if the message is telling us to switch mode
        # TODO: check if this is a heartbeat message

        if myDevice.deviceMode == myDevice.MODE_MANUAL:
            # TODO: if this message is manual control commands then do what they say
            continue

    # TODO: Check that no devices have timed out from heartbeat

    if myDevice.deviceMode == myDevice.MODE_MANUAL:
        # TODO: if no manual control command has been issued recently then stop
        continue


    if myDevice.deviceMode == myDevice.MODE_AUTONOMOUS:
        # TODO: preform autonomous operations
        continue

    continue