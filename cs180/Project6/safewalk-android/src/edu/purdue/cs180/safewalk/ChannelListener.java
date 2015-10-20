package edu.purdue.cs180.safewalk;

/**
 * Interface between the AndroidChannel class and the Activity or Fragment that needs to receive messages and
 * notifications from the server.
 * 
 * @author jtk
 * 
 */
public interface ChannelListener {
    void messageReceived(String message);

    void notifySendFailure();
}
