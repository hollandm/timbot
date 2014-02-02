import socket
import struct

PACKET_SIZE = 10

#Where in the byte array, the numeric id of the sender is stored
SENDER_ID_SLOT = 0

#Where in the byte array, the numeric id of the destination is stored
DESTINATION_ID_SLOT = 1

#Where in the byte array, the numeric id of the type of message being sent
MESSAGE_TYPE_SLOT = 2

#Where in the byte array, the data to send across the network
DATA_START_SLOT = 3


#If the message type slot is 0 then stop
MESSAGE_TYPE_ESTOP = 0


UDP_IP = "224.0.0.1"
UDP_PORT = 6000

#recieve data
# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
# sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# sock.bind(('', UDP_PORT))
#
# mreq = struct.pack("=4sl", socket.inet_aton(UDP_IP), socket.INADDR_ANY)
#
# sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)



data = []
data.append(0)
data.append(1)
data.append(2)
data.append(3)
data.append(4)
data.append(5)

#send data
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)
sock.sendto(bytearray(data), (UDP_IP, UDP_PORT))

