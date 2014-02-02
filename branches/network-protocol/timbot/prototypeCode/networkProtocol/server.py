import socket
import struct

UDP_IP = "224.0.0.1"
UDP_PORT = 6000

# recieve data

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', UDP_PORT))

mreq = struct.pack("=4sl", socket.inet_aton(UDP_IP), socket.INADDR_ANY)

sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

while True:
    array = bytearray(sock.recv(10))
    for byte in array:
        print byte
    # print array
    # print type(array)
    # print bytearray(array)[1]

