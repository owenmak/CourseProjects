import java.util.Scanner;

import edu.purdue.cs.cs180.channel.*;

public class Volunteer implements MessageListener {

	TCPChannel channel = null;

	public Volunteer(Channel c) {
		this.channel = (TCPChannel) c;
		this.channel.setMessageListener(this);
		sendMessage(channel.getID());
	}

	public void sendMessage(int id) {
		Scanner s = new Scanner(System.in);
		System.out.println("Press ENTER when ready:");
		s.nextLine();
		try {
			System.out.println("Waiting for assignment...");
			channel.sendMessage("VOLUNTEER " + id);
		} catch (ChannelException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void messageReceived(String message, int clientID) {
		System.out.println("Proceed to " + message.substring(9));
		sendMessage(channel.getID());
	}

	public static void main(String[] args) throws NumberFormatException,
			ChannelException {
		TCPChannel c = new TCPChannel(args[0], Integer.parseInt(args[1]));
		Volunteer v = new Volunteer(c);
	}

}
