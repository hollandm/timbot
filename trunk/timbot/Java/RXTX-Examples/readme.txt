AUTHOR: 
Raphael Blatter (raphael@blatter.sg) 
based on http://rxtx.qbang.org

INTENTION:
The class 'net.Network' and the interface 'net.Network_iface' 
have been published to simplify access to serial ports for 
unexperienced users. The additional class 'net.Example' shows 
the use in an extremely basic example, to further simplify 
access to a serial port for beginners.
Feel free to use the code in any way you like, change it, use 
it, ignore it, ...

USAGE:
Having 'ant' installed, the following commands are possible 
(while in the folder 'RXTX_example'):
	ant
		Compiles the classes and creates a jar ready to be 
		run. A launcher for Linux is created (RXTX_example.sh), 
		which also adds the external library to the path.
	ant clean
		Delete all binary files, the jar file, the launcher, 
		and the documentation.
	ant run
		Launches the tool. Works only after it has been compiled.
	ant javadoc
		Creates documentation in HTML-format.
On a different OS or compiling and running without my ant-file, 
always make sure that the RXTX library is in your library path. 
Look on the webpage (http://rxtx.qbang.org) for more information.

DOCUMENTATION:
The folder 'documentation' contains two versions of the 
documentation, created by Javadoc. One describes all the methods 
and members, which is useful for people wanting to use ideas 
from the code or use the code as a base for their own programming, 
while the other version describes only the public methods, which 
is more suited for people simply interested in using the class as 
is.

ORIGIN:
This simple interface and the example with the corresponding 
ant-file have been written by Raphael Blatter (raphael@blatter.sg), 
using the great RXTX library (http://rxtx.qbang.org) and highly 
making use of already existing examples from the webpage.
I am no professional programmer, so please forgive me for possible 
bugs or mistakes. Use the code as you like, and always at your own 
risk. This class is taken out of a personal project of mine, so 
the functionalities were implemented as needed for my project, 
however with the goal of more generalized usage in mind.
This example has been written and tested on Linux (Ubuntu 10.04, 
Kernel 2.6.32-22-generic, using java-6-sun-1.6.0.20), communicating
with an arduino (http://www.arduino.cc).

Have fun and good luck with your projects!
