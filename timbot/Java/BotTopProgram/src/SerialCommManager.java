
import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/** Manages the commport */
public class SerialCommManager{
	SerialWriter ostream;
	SerialReader istream;
	void connect (String portName) throws Exception
	{
		CommPortIdentifier portIdent = CommPortIdentifier.getPortIdentifier(portName);
		if (portIdent.isCurrentlyOwned())
		{
			System.out.println("Error: Port in use");
		}
		else
		{
			CommPort commPort = portIdent.open(this.getClass().getName(),2000);

			if ( commPort instanceof SerialPort )
			{
				SerialPort serialPort = (SerialPort) commPort;
				serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
				// serialPort.setEndOfInputChar((byte) ' ');
				InputStream in = serialPort.getInputStream();
				OutputStream out = serialPort.getOutputStream();
				//Set up the reading and writing threads...
				(new Thread(istream = new SerialReader(in))).start();
				(new Thread(ostream = new SerialWriter(out))).start();
			}
		}     
		
	}
		
	/**
	 * This takes a string and writes it to the serial buffer.
	 * If there's not a space at the end, one is added.
	 */
	public void writeString(String in)
	{
		
		in = in.toUpperCase();
		int i;
		for (i = 0; i < in.length(); i++)
		{
			ostream.write(in.charAt(i));
		}
		//If there's not a space at the end, add one.
		if (in.charAt(i-1) != ' ') {
			ostream.write(' ');
		}
	}
	public static class SerialReader implements Runnable 
	{
		InputStream in;

		public SerialReader ( InputStream in )
		{
			this.in = in;
		}

		public void run ()
		{
			byte[] buffer = new byte[1024];
			int len = -1;
			try
			{
				while ( ( len = this.in.read(buffer)) > -1 )
				{
					System.out.print(new String(buffer,0,len));
				}
			}
			catch ( IOException e )
			{
				e.printStackTrace();
			}            
		}
	}

	/** */
	public static class SerialWriter implements Runnable 
	{
		OutputStream out;

		public SerialWriter ( OutputStream out )
		{
			this.out = out;
		}
		public void write (char input)
		{
			try
			{
				this.out.write(input);
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
		public void run ()
		{
		//For now, do nothing	
		}
		
	}	
}
