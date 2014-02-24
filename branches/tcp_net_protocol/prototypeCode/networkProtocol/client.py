# The network client receives data from network servers.

import netProtocol

# a = netProtocol.udpHandshake("Client")
# print a.receiveHandshake()

b = netProtocol.netManager("Client", False)
b.connections["hub"].send('test')