import socket
import struct
import time


class udpHandshake:

    UDP_IP = "224.0.0.1"
    UDP_PORT = 6000
    UDP_MAX_PACKET_SIZE = 1024

    ##
    # Constructor
    #
    # Description: opens a udp socket to send and receive handshake messages
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
    # Description: sends the device id over udp, giving the client the
    #   information it needs to open a tcp connection
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
    BUFFER_SIZE = 1024

    TCP_PORT = 6001
    connections = {}

    ##
    # Constructor
    #
    def __init__(self, deviceId, isHub, numDevices=0):


        hs = udpHandshake(deviceId)

        # Is this device the network hub?
        if isHub:
            devicesConnected = 0

            while devicesConnected < numDevices:
                deviceId, addr = hs.receiveHandshake()

                tcpSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                # print addr

                # time.sleep(1)

                tcpSock.connect((addr, self.TCP_PORT))
                self.connections[deviceId] = tcpSock

                devicesConnected += 1

        else:

            tcpSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            tcpSock.bind(('', self.TCP_PORT))
            tcpSock.listen(1)
            tcpSock.settimeout(3)

            inbound = None
            while inbound is None:

                hs.sendHandshake()
                # print "Listening"
                try:
                    inbound = tcpSock.accept()
                    # print inbound
                except socket.error as msg:
                    continue

            self.connections["hub"] = inbound[0]
            tcpSock.close()

        hs.close()
        return

    ##
    # send
    #
    # Description: sends a message to a device
    #
    # Parameters:
    #   msg - the message to send
    #   deviceId - the device to send the message
    #
    def send(self, msg, deviceId):
        self.connections[deviceId].send(msg)

    ##
    # sendAll
    #
    # Description: sends a message to all devices
    #
    # Parameters:
    #   msg - the message to send
    def sendAll(self, msg):
        for device in self.connections:
            self.connections[device].send(msg)

    ##
    # recv
    #
    # Description: attempt to receive a message from each device, if their
    #   are no inbound messages then returns None
    #
    def recv(self):
        for device in self.connections:
            conn = self.connections[device]
            try:
                recv = conn.recv(self.BUFFER_SIZE)
                return recv
            except socket.error:
                continue

        return None

    ##
    # close
    #
    # Description: close all streams
    #
    def close(self):
        for device in self.connections:
            self.connections[device].close()



