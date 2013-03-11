import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketAddress;
import java.net.UnknownHostException;


public class NetworkComms implements Runnable {

	float leftSpeed = 0;
	float rightSpeed = 0;

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
		try {
			MotorControler.connect("COM4");
			MotorControler.writeString("ZS"); 
			MotorControler.writeString("MV");
			MotorControler.writeString("EIGN(2)");
			MotorControler.writeString("EIGN(3)");
			MotorControler.writeString("ADT="+10000);
			
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

			String speedLeft  = "VT="+(dataIN[0]-50)*2500;
			String speedRight = "VT="+(dataIN[2]-50)*2500;
			
			MotorControler.writeString((char)129+"");
			
			MotorControler.writeString(speedLeft);
			MotorControler.writeString("G");
			
			MotorControler.writeString((char)130+"");
			
			MotorControler.writeString(speedRight);
			MotorControler.writeString("G");

			
			System.out.println("Recieved: "+ speedLeft + " - " + speedRight);
			
			
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
