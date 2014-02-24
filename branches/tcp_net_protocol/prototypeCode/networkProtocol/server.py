import netProtocol

# a = netProtocol.udpHandshake("Server")
# a.sendHandshake()

b = netProtocol.netManager("Server", True, 1)
print b.connections["Client"].recv(1024)

