import java.util.ArrayList;

import edu.purdue.cs.cs180.channel.*;

public class Server implements MessageListener {
	private ArrayList<String> rLoc = new ArrayList<String>();
	private ArrayList<String> rUrg = new ArrayList<String>();
	private ArrayList<Integer> rID = new ArrayList<Integer>();
	private ArrayList<String> vLoc = new ArrayList<String>();
	private ArrayList<Integer> vID = new ArrayList<Integer>();
	private Channel channel = null;
	private String algorithm;
	private int[][] distance;

	public Server(Channel c) {
		channel = c;
		channel.setMessageListener(this);
	}

	public Server(Channel c, String algorithm) {
		channel = c;
		channel.setMessageListener(this);
		this.algorithm = algorithm;
		distance = new int[][] { { 0, 8, 6, 5, 4 }, { 8, 0, 4, 2, 5 },
			{ 6, 4, 0, 3, 1 }, { 5, 2, 3, 0, 7 }, { 4, 5, 1, 7, 0 } };
	}

	@Override
	public void messageReceived(String message, int clientID) {
		if (algorithm.equals("URGENCY"))
			this.urgencyMsgReceived(message, clientID);
		else if (algorithm.equals("CLOSEST"))
			this.closestMsgReceived(message, clientID);
		else
			this.fcfsMsgReceived(message, clientID);
	}

	public void fcfsMsgReceived(String message, int clientID) {
		if (message.contains("VOLUNTEER")) {
			if (rID.isEmpty()) {
				vID.add(clientID);
				vLoc.add(message.substring(10));
			} else {
				sendVolunteer(rLoc.get(0), rUrg.remove(0), clientID);
				sendRequester(clientID,
						getTime(message.substring(10), rLoc.remove(0)), rID.remove(0));
			}
		} else {
			String[] parts;
			parts = message.substring(8).split(" ");
			if (vID.isEmpty()) {
				rID.add(clientID);
				rLoc.add(parts[0]);
				rUrg.add(parts[1]);
			} else {
				sendVolunteer(parts[0], parts[1], vID.get(0));
				sendRequester(vID.remove(0),
						getTime(parts[0], vLoc.remove(0)), clientID);
			}
		}
	}

	public void closestMsgReceived(String message, int clientID) {
		if (message.contains("VOLUNTEER")) {
			if (rID.isEmpty()) {
				vID.add(clientID);
				vLoc.add(message.substring(10));
			} else {
				int i;
				int time;
				String vl = message.substring(10);
				i = 0;
				time = getTime(rLoc.get(0), vl);
				for (int j = 1; j < rLoc.size(); j++) {
					if (getTime(rLoc.get(j), vl) < time) {
						i = j;
						time = getTime(rLoc.get(j), vl);
					}
				}
				sendRequester(clientID, time, rID.remove(i));
				sendVolunteer(rLoc.remove(i), rUrg.remove(i), clientID);
			}
		} else {
			String[] parts;
			parts = message.substring(8).split(" ");
			if (vID.isEmpty()) {
				rID.add(clientID);
				rLoc.add(parts[0]);
				rUrg.add(parts[1]);
			} else {
				int i;
				int time;
				String rl = parts[0];
				i = 0;
				time = getTime(vLoc.get(0), rl);
				for (int j = 1; j < vLoc.size(); j++) {
					if (getTime(vLoc.get(j), rl) < time) {
						i = j;
						time = getTime(vLoc.get(j), rl);
					}
				}
				sendRequester(vID.get(i), time, clientID);
				sendVolunteer(rl, parts[1], vID.remove(i));
				vLoc.remove(i);
			}
		}
	}

	public void urgencyMsgReceived(String message, int clientID) {

		if (message.contains("VOLUNTEER")) {
			if (rID.isEmpty()) {
				vID.add(clientID);
				vLoc.add(message.substring(10));
			} else {
				int i = -1;
				for (int j = 0; j < rUrg.size(); j++) {
					if (rUrg.get(j).equals("EMERGENCY")) {
						i = j;
						break;
					}
				}
				if (i == -1) {
					for (int j = 0; j < rUrg.size(); j++) {
						if (rUrg.get(j).equals("URGENT")) {
							i = j;
							break;
						}
					}
				}
				if (i == -1)
					i = 0;
				sendVolunteer(rLoc.get(i), rUrg.remove(i), clientID);
				sendRequester(clientID,
						getTime(rLoc.remove(i), message.substring(10)),
						rID.remove(i));
			}
		} else {
			String[] parts;
			parts = message.substring(8).split(" ");
			if (vID.isEmpty()) {
				rID.add(clientID);
				rLoc.add(parts[0]);
				rUrg.add(parts[1]);
			} else {
				sendVolunteer(parts[0], parts[1], vID.get(0));
				sendRequester(
						vID.remove(0),
						getTime(parts[0],
								vLoc.remove(0)), clientID);
			}
		}
	}

	public void sendVolunteer(String location, String urgency, int clientID) {
		try {
			channel.sendMessage("LOCATION " + location + " " + urgency,
					clientID);
		} catch (ChannelException e) {
			e.printStackTrace();
		}
	}

	private int getTime(String loc1, String loc2) {
		int i;
		int j;
		if (loc1.equals("CL50"))
			i = 0;
		else if (loc1.equals("EE"))
			i = 1;
		else if (loc1.equals("LWSN"))
			i = 2;
		else if (loc1.equals("PMU"))
			i = 3;
		else
			i = 4;
		if (loc2.equals("CL50"))
			j = 0;
		else if (loc2.equals("EE"))
			j = 1;
		else if (loc2.equals("LWSN"))
			j = 2;
		else if (loc2.equals("PMU"))
			j = 3;
		else
			j = 4;
		return distance[i][j];
	}

	public void sendRequester(int volID, int time, int clientID) {
		try {
			channel.sendMessage("VOLUNTEER " + volID + " " + time, clientID);
		} catch (ChannelException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws NumberFormatException,
			ChannelException {
		Channel c = new TCPChannel(Integer.parseInt(args[0]));
		Server s = new Server(c, args[1]);
	}
}
