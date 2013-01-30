import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;


public class sendTest {
	public static void main(String args[]) {

		SerialPort serialPort = null;
		/** The port we're normally going to use. */
		String PORT_NAMES[] = { 
			"/dev/tty.usbserial-A9007UX1", // Mac OS X
			"/dev/ttyUSB0", // Linux
			"COM7", // Windows
		};
		/**
		 * A BufferedReader which will be fed by a InputStreamReader 
		 * converting the bytes into characters 
		 * making the displayed results codepage independent
		 */
		BufferedReader input;
		/** The output stream to the port */
		OutputStream output;
		/** Milliseconds to block while waiting for port open */
		int TIME_OUT = 2000;
		/** Default bits per second for COM port. */
		int DATA_RATE = 9600;

		CommPortIdentifier portId = null;
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

		//First, Find an instance of serial port as set in PORT_NAMES.
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
			for (String portName : PORT_NAMES) {
				if (currPortId.getName().equals(portName)) {
					portId = currPortId;
					break;
				}
			}
		}
		if (portId == null) {
			System.out.println("Could not find COM port.");
			return;
		}

		try {
			// open serial port, and use class name for the appName.
			serialPort = (SerialPort) portId.open(this.getClass().getName(),
					TIME_OUT);

			// set port parameters
			serialPort.setSerialPortParams(DATA_RATE,
					SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);

			// open the streams
			input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
			output = serialPort.getOutputStream();

			// add event listeners
			serialPort.notifyOnDataAvailable(true);
			

			String serialMessage = "AT\r\n";
			OutputStream outstream = serialPort.getOutputStream();
			outstream.write(serialMessage.getBytes());
			
		} catch (Exception e) {
			System.err.println(e.toString());
		}


	}
}
