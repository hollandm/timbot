import socket
import netProtocol


class server:

    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)

    ##
    # sendData
    #
    # Description: sends a data packet to all clients on the network
    def sendData(self, data):
        self.sock.sendto(bytearray(data), (netProtocol.UDP_IP, netProtocol.UDP_PORT))
