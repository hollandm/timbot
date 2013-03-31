import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.OutputStream;


/**
 * ArduinoOutput
 * 
 * The .java file that sends all output signals to the arduino.
 * @author 
 *
 */

public class ArduinoWriter {

	
	OutputStream out = null;
	
	public ArduinoWriter() {}

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



}
