import socket
import struct
import sys


class udpHandshake:

    UDP_IP = "224.0.0.1"
    UDP_PORT = 6000
    UDP_MAX_PACKET_SIZE = 1025

    ##
    # Constructor
    #
    # Description: opens a udp socket to send and recieve handshake messages
    #
    def __init__(self, deviceId):
        self.deviceId = deviceId

        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('', self.UDP_PORT))

        mreq = struct.pack("=4sl", socket.inet_aton(self.UDP_IP), socket.INADDR_ANY)

        sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

        self.socket = sock

        return


    ##
    # receiveHandshake
    #
    # Description: sends the device id over udp, giving the client the information it needs to open a tcp connection
    #
    def sendHandshake(self):

        self.socket.sendto(self.deviceId, (self.UDP_IP, self.UDP_PORT))

        return

    ##
    # receiveHandshake
    #
    # Description: gets the device id and address who just send a handshake
    #
    def receiveHandshake(self):
        deviceId, addr = self.socket.recvfrom(self.UDP_MAX_PACKET_SIZE)

        return deviceId, addr[0]

    ##
    # close
    #
    # Description: Closes the socket
    #
    def close(self):
        self.socket.close()


class netManager:
    TCP_PORT = 6001
    connections = {}

    ##
    # Constructor
    #
    #
    #
    def __init__(self, deviceId, isHub, numDevices=0):


        hs = udpHandshake(deviceId)

        if isHub:
            devicesConnected = 0

            while devicesConnected < numDevices:
                deviceId, addr = hs.receiveHandshake()

                tcpSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                print addr

                tcpSock.connect((addr, self.TCP_PORT))

                self.connections[deviceId] = tcpSock

                devicesConnected += 1

        else:


            tcpSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            tcpSock.bind(('', self.TCP_PORT))

            hs.sendHandshake()
            tcpSock.listen(1)


            self.connections["hub"] = tcpSock

        hs.close()
        return


    def close(self):
        return

#If the message type slot is 0 then stop
MESSAGE_TYPE_ESTOP = 0
MESSAGE_TYPE_HEARTBEAT = 1
MESSAGE_TYPE_SET_MODE = 2
MESSAGE_TYPE_MANUAL_COMMAND = 3

