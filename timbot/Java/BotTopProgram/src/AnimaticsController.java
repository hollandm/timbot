import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


public class AnimaticsController {

	OutputStream out = null;
	
	public AnimaticsController() {}

	/**
	 * Given a port, connects over serial
	 */
	void connect ( String portName ) throws Exception
	{
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
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		out = null;
	}
	
	/**
	 * This takes a string and writes it to the serial buffer.
	 * If there's not a space at the end, one is added.
	 */
	public void writeString(String in)
	{
	
		if (out == null) return;
		
		in = in.toUpperCase();
		try
		{
			
			int i;
			for (i = 0; i < in.length(); i++)
			{
				this.out.write(in.charAt(i));
			}
			//If there's not a space at the end, add one.
			if (in.charAt(i-1) != ' ') {
				this.out.write(' ');
			}
		}
		catch ( IOException e )
		{
			e.printStackTrace();
		}
//		System.out.println(in);

	}
	
	
	
	public static void main ( String[] args )
	{
		AnimaticsController test = new AnimaticsController();
		try {
			test.connect("COM4");
			
			int acc = 100;
			int vel = 100000;
			test.writeString("ZS"); 
			test.writeString("MV");
			test.writeString("EIGN(2)");
			test.writeString("EIGN(3)");
			test.writeString("ADT="+acc);
			test.writeString("VT="+vel);
			test.writeString("G");
			
			test.disconnect();
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
}
