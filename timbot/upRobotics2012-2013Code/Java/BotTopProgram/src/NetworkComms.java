import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.util.Scanner;


public class NetworkComms implements Runnable {


	float armSpeed = 0;
	float bucketSpeed = 0;

	int mode = 0;


	public NetworkComms(BotTop robot) {
		
	}

	@Override
	public void run() {

		

	}

	public static void main(String args[]) throws IOException, InterruptedException {
		
		AnimaticsController MotorControler = new AnimaticsController();
		Arduino arduino = new Arduino();
		try {
			MotorControler.connect("/dev/ttyUSB0");
			arduino.connect("/dev/ttyS34");
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		byte[] dataIN = new byte[7];
		
		MulticastSocket in = new MulticastSocket(6000);
		DatagramPacket recv = new DatagramPacket(dataIN, 7);
//		SocketAddress addr = SocketAddress;
		InetAddress add = InetAddress.getByName("224.0.0.1");
		in.joinGroup(add);
		
		in.setReceiveBufferSize(7);
		
		System.out.println("Listening to traffic");
		
		while (true) {
			in.receive(recv);

			int speed = 5000;
			
			String speedLeft;
			String speedRight;
			
			if (dataIN[4] != (byte)0  || dataIN[5] != (byte)0) {	//Dig Mode
				speedLeft  = "VT="+(dataIN[0]-50)*speed*-1;
				speedRight = "VT="+(dataIN[0]-50)*speed;
				
				byte arm = (byte) dataIN[2];
				byte bucket = (byte)dataIN[3];
				
				//avoid cloging the arduino buffer
				if ((arm != (byte)50) || (bucket != (byte)50)) {

					arduino.write(arduino.BUFFER_SYNC);			//SYNC stuff
					arduino.write(arm);					//Actuate Arm
					arduino.write(bucket);					//Actuate Bucket
//					Thread.sleep(10);
				}
				
			} else {											//Drive Mode
				speedLeft  = "VT="+(dataIN[2]-50)*speed*-1;
				speedRight = "VT="+(dataIN[0]-50)*speed;
			}
			
			
//			
			MotorControler.writeString((char)129+"");
			
			MotorControler.writeString(speedLeft);
			MotorControler.writeString("G");
			
			MotorControler.writeString((char)130+"");
			
			MotorControler.writeString(speedRight);
			MotorControler.writeString("G");
			System.out.println(dataIN[0] + " " + dataIN[1] + " " + dataIN[2] + " " + dataIN[3] + " " + dataIN[4] + " " + dataIN[5] + " " +  dataIN[6]);
			
			
			//read data back
			byte[] b = new byte[10];
//			System.out.println(arduino.in.readLine());
			
			
//			System.out.println("Recieved: "+ speedLeft + " - " + speedRight);
//			Thread.sleep(10);			
			
		}
		
		/*
		//client
		byte[] data = new byte[7];
		data[0]=0;
		data[1]=0;
		data[2]=0;
		data[3]=0;
		data[4]=0;
		data[5]=0;
		data[6]=0;
		
		
//		DatagramSocket DGSocket = new DatagramSocket(6000);
		MulticastSocket out = new MulticastSocket(6000);
		InetAddress dest = InetAddress.getByName("224.0.0.1");
//		InetAddress dest = InetAddress.getByName("255.255.255.255");
//		InetAddress dest = InetAddress.getByName("192.168.0.119");
		
		DatagramPacket send = new DatagramPacket(data, 7, dest, 6000);
		
		while (true) {
//			DGSocket.send(send);
			out.send(send);
			Thread.sleep(10);
		}
		
		*/
		
	}


}
