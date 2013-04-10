import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Scanner;

import usbScanner.UsbScanner;


/**
 * ArduinoOutput
 * 
 * The .java file that sends all output signals to the arduino.
 * @author 
 *
 */

public class Arduino {

	public final static byte BUFFER_SYNC = 101;

	final String regKey = "SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_2341&PID_0010\\64936333936351C061C0";
	
	OutputStream out = null;
	BufferedReader in = null;
	
	public Arduino() {}

	/**
	 * Given a port, connects over serial
	 */
//	void connect ( String portName ) throws Exception
	void connect () throws Exception
	{
		int port = UsbScanner.getComNumber(regKey);
		if (port == -1) {
			System.err.println("Port not found!");
			return;
		}
		String portName = "COM"+port;
		
		CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
		if ( portIdentifier.isCurrentlyOwned() )
		{
			System.out.println("Error: Port is currently in use");
		}
		else
		{
			CommPort commPort = portIdentifier.open(this.getClass().getName(),2000);
			
			if ( commPort instanceof SerialPort )
			{
				SerialPort serialPort = (SerialPort) commPort;
				serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);

				out = serialPort.getOutputStream();
				in = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));

			}
			else
			{
				System.out.println("Error: Only serial ports are handled by this code.");
			}
		}     
		
		
	}
	
	/**
	 * closes the output port
	 */
	public void disconnect() {
		try {
			out.close();
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		out = null;
	}
	
	/**
	 * This takes a string and writes it to the serial buffer.
	 * If there's not a space at the end, one is added.
	 */
	public void write(byte send)
	{
	
		if (out == null) return;
		
		try
		{
			this.out.write(send);
		
		}
		catch ( IOException e )
		{
			e.printStackTrace();
		}

	}
	
	public void write(char send) {
		this.write((byte)send);
	}
	
	public void write (String send) {
		for (char c : send.toCharArray()) {
			this.write((byte)c);
		}
	}
	
	/**
	 * Extend the bucket by the given distance
	 * @param dst
	 */
	public void acuateArm(float spd) {}			//TODO

	/**
	 * Extend the bucket by the given distance 
	 * @param dst
	 */
	public void acuateBucket(float spd) {}		//TODO


	/**
	 * Extend the arm to the target distance 
	 * @param dst
	 */
	public void targetArm(float dst) {}			//TODO

	/**
	 * Extend the bucket to the target distance 
	 * @param dst
	 */
	public void targetBucket(float dst) {}		//TODO


	public static void main(String[] args) throws Exception {
		
		Arduino a = new Arduino();
		a.connect();
		
		while (true) {
			Scanner in = new Scanner(System.in);
//			String i = in.nextLine();
			byte i = (byte)in.nextInt();
//			a.out.write((byte)i.charAt(0));
			a.write(a.BUFFER_SYNC);
			a.write(i);
			System.out.println(i);
			a.write((byte)0);
		}
		
//		a.write('a');
		
//		a.disconnect();
//		a.write("Test");
//		Thread.sleep(1000);
//		System.out.println(a.in.read());
		
	}

	
	

}
