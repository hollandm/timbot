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


