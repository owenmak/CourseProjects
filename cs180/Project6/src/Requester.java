import java.util.Scanner;

import edu.purdue.cs.cs180.channel.*;

public class Requester implements MessageListener {
	TCPChannel channel = null;
	String loc;

	public Requester(Channel c) {
		this.channel = (TCPChannel) c;
		this.channel.setMessageListener(this);
		this.setLoc();
		this.sendMessage();
	}

	public void setLoc() {
		int choice = 0;
		boolean valid = true;
		Scanner s = new Scanner(System.in);
		while (valid) {
			System.out.println("1. CL50 - Class of 1950 Lecture Hall");
			System.out.println("2. EE - Electrical Engineering Building");
			System.out.println("3. LWSN - Lawson Computer Science Building");
			System.out.println("4. PMU - Purdue Memorial Union");
			System.out.println("5. PUSH - Purdue University Student Health Center");
			System.out.printf("Enter your location (1-5): ");
			try {
				choice = Integer.parseInt(s.next());
				if (choice > 0 && choice < 6) {
					valid = false;
					break;
				}
				System.out.println("Invalid input. Please try again.");
			} catch (NumberFormatException e) {
				System.out.println("Invalid number format. Please try again.");
			}
		}
		switch (choice) {
			case 1:
				loc = "CL50";
				break;
			case 2:
				loc = "EE";
				break;
			case 3:
				loc = "LWSN";
				break;
			case 4:
				loc = "PMU";
				break;
			case 5:
				loc = "PUSH";
				break;
			default:
				break;
		}
	}

	public String getLoc() {
		return this.loc;
	}

	public void sendMessage() {
		try {
			System.out.println("Waiting for volunteer...");
			channel.sendMessage("REQUEST " + loc);
		} catch (ChannelException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void messageReceived(String message, int clientID) {
		System.out.println("Volunteer " + clientID
				+ " assigned and will arrive shortly.");
		this.setLoc();
		this.sendMessage();
	}

	public static void main(String[] args) throws NumberFormatException,
			ChannelException {
		TCPChannel c = new TCPChannel(args[0], Integer.parseInt(args[1]));
		Requester r = new Requester(c);
	}

}
