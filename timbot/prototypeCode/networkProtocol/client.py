# The network client receives data from network servers.
#
# TODO: consider implementing a priority queue if messages build up faster than we can process them
#      We could execute important commands like E-Stop right away
#      Furthermore we might be able to detect redundant packets and throw them away to avoid processing
#

import socket
import struct
import netProtocol

class client:

    def __init__(self, myDevice):

        self.myDevice = myDevice

        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(('', netProtocol.UDP_PORT))

        mreq = struct.pack("=4sl", socket.inet_aton(netProtocol.UDP_IP), socket.INADDR_ANY)

        sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

        sock.setblocking(False)
        sock.settimeout(0.01)

        self.socket = sock

    ##
    # getData
    #
    # Description: Attempts to receive a data packet from the network or the inbound queue.
    #       if a packet is received then return it otherwise return None
    #
    def getData(self):
        received = None

        while True:

            try:
                received = bytearray(self.socket.recv(netProtocol.PACKET_SIZE))
            except socket.timeout:
                return None

            intendedDestination = received[netProtocol.DESTINATION_ID_SLOT]
            if intendedDestination == self.myDevice.DEVICE_ID_ALL or intendedDestination == self.myDevice.deviceId:
                return received

