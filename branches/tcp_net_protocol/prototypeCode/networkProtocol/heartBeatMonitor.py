# The heart beat monitor will detect if one or more devices ceases to function.
# The local machine can then react accordingly, most likely this will mean moving the
# system to a stand by stage
#
# TODO: Consider including the heartbeat time within the message for greater accuracy

import time
import server
import client
import netProtocol

try:
    import sys

    sys.path.insert(0, "../general")
    import device

except:
    sys.exit()


class heartBeatMonitor:

    # How long to wait between heartbeat messages
    HEARTBEAT_SEND_DELAY = 1000

    # How long to wait since the last heart beat was received until we begin to panick
    HEARTBEAT_MAX_RECEIVE_DELAY = 3000

    ##
    # __init__
    #
    # Description: Initializes the heartbeat monitor
    #
    def __init__(self, myDevice):
        self.myDevice = myDevice

        self.message = bytearray([0] * netProtocol.PACKET_SIZE)
        self.message[0] = myDevice.deviceId
        self.message[1] = myDevice.DEVICE_ID_ALL
        self.message[2] = netProtocol.MESSAGE_TYPE_HEARTBEAT

        self.lastHeartbeatFromDevice = {-1, -1, -1}

    ##
    # triggerHeartbeat
    #
    # Description: Sends a heart beat message to all other devices on the network to notify
    #   them that this device is still functioning
    def triggerHeartbeat(self):
        self.myDevice.server.sendData(self.message)

    ##
    # gotHeartbeat
    #
    # Description: When a heartbeat message is received, record the time that it was received
    #
    # Parameters:
    #   deviceId - The id of the device that sent the heartbeat.
    def gotHeartbeat(self, deviceId):
        self.lastHeartbeatFromDevice[deviceId] = time.clock()

    ##
    # checkHeartbeatOverdue
    #
    # Description: used to check weather or not a device is overdue
    def checkHeartbeatOverdue(self):

        curTime = time.clock()

        for lastHeartbeat in self.lastHeartbeatFromDevice:
            if curTime-self.HEARTBEAT_MAX_RECEIVE_DELAY < lastHeartbeat:
                return True

        return False