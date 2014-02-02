import socket

UDP_IP = "224.0.0.1"
UDP_PORT = 6000

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
