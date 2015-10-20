/**
 * Note
 * ====
 * This file is NOT a model for any of the programs in your solution --
 * it is merely a way to test your Server implementation without having to open
 * multiple terminals or Android applications.
 *
 * Purpose
 * =======
 * This program is a simple test client you may use to send messages from
 * different channels to a server. You may enter messages (one per line), which
 * will each be sent to the server from a newly-instantiated channel.
 *
 * Simple Usage
 * ============
 * java TestClient <address> <port>
 * Example:
 *          $ java TestClient localhost 9001
 * [stdin]  REQUEST EE EMERGENCY
 * [stdout] [Client   0]    Sending to server: REQUEST EE EMERGENCY
 * [stdin]  VOLUNTEER LWSN
 * [stdout] [Client   1]    Sending to server: VOLUNTEER LWSN
 * [stdout] [Client   0] Received from server: VOLUNTEER 1 4
 * [stdout] [Client   1] Received from server: LOCATION EE EMERGENCY
 *
 * Input from File
 * ===============
 * If you would like to use messages from a file, you can use stream
 * redirection. Example:
 *
 * $ java TestClient localhost 9001 < mymessages.txt
 */

import edu.purdue.cs.cs180.channel.*;
import java.util.*;
import java.io.*;

public class TestClient implements MessageListener {

    private final Channel channel;

    private TestClient (Channel channel) {
        this.channel = channel;
        channel.setMessageListener(this);
    }

    private static synchronized void printf (String str, Object... args) {
        System.out.printf(str, args);
    }

    public void sendMessage (String message) throws ChannelException {
        printf("[Client %3d]    Sending to server: %s\n", channel.getID(), message);
        channel.sendMessage(message);
    }

    @Override
    public void messageReceived (String message, int id) {
        printf("[Client %3d] Received from server: %s\n", id, message);
    }

    public static void main(String[] args) throws IOException {
        String addr = args[0];
        String port = args[1];
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = in.readLine()) != null) {
            if (line.length() < 0)
                continue;
            try {
                TestClient tc = new TestClient(new TCPChannel(addr, Integer.parseInt(port)));
                tc.sendMessage(line);
                Thread.sleep(200);
            } catch (ChannelException e) {
                printf("Error connecting to server at %s:%s.\n", addr, port);
                System.exit(1);
            } catch (Exception e) {
                printf("Caught exception %s\n", e.getClass().getName());
                System.exit(1);
            }
        }
    }
}
