import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


public class RXTX_PROGRAM {


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
				// serialPort.setEndOfInputChar((byte) ' ');
				InputStream in = serialPort.getInputStream();
				OutputStream out = serialPort.getOutputStream();

				(new Thread(new SerialReader1(in))).start();
				(new Thread(new SerialWriter1(out))).start();

			}
			else
			{
				System.out.println("Error: Only serial ports are handled by this example.");
			}
		}     
	}

	/** */
	public static class SerialReader1 implements Runnable 
	{
		InputStream in;

		public SerialReader1 ( InputStream in )
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
	public static class SerialWriter1 implements Runnable 
	{
		OutputStream out;

		public SerialWriter1 ( OutputStream out )
		{
			this.out = out;
		}

		public void run ()
		{
			System.out.println("RUN");
			int acc = 100;
			int vel = 100000;
			int pos = 100*vel;
			//writeString("O=0");
			writeString("ZS"); 
			writeString("MV");
			writeString("EIGN(2)");
			writeString("EIGN(3)");
			writeString("ADT"+acc);
			writeString("VT="+vel);
		//	writeString("PRT="+pos);
			writeString("G");
			try {
				out.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			System.exit(0);
			
		}
		
		/**
		 * This takes a string and writes it to the serial buffer.
		 * If there's not a space at the end, one is added.
		 */
		public void writeString(String in)
		{
			
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
		}
	}

	public static void main ( String[] args )
	{
		try
		{
			(new RXTX_PROGRAM()).connect("COM9");

		}
		catch ( Exception e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
