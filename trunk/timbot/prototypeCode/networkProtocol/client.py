# The network client receives data from network servers.

import netProtocol

# a = netProtocol.udpHandshake("Client")
# print a.receiveHandshake()

b = netProtocol.netManager("Client", False)
try:
    # print b.connections
    b.send("Hello World!", "hub")
    # b.sendAll("Hello World!")
    # for sock in b.connections:
    #     print "Sending?"
    #     print type(b.connections[sock])
    #     # print "Socket" + str(b.connections[sock])
    #     b.connections[sock].send("Hello World!")
except:
    print "Message could not be sent"
    b.close()

# b.connections["hub"].send('test')