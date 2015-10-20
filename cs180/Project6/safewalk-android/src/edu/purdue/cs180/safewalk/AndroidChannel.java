package edu.purdue.cs180.safewalk;

import android.os.AsyncTask;
import android.os.Handler;
import edu.purdue.cs.cs180.channel.ChannelException;
import edu.purdue.cs.cs180.channel.MessageListener;
import edu.purdue.cs.cs180.channel.TCPChannel;

/**
 * AndroidChannel is a layer on top of the Channel/TCPChannel classes for managing connections to the Server. It
 * supports the background network processing required by the Android OS.
 * 
 * @author jtk
 * 
 */
public class AndroidChannel implements MessageListener {
    private ChannelListener channelListener;
    private String hostName;
    private int portNumber;
    private TCPChannel channel;
    private AndroidHandler androidHandler;

    /**
     * Class constructor specifying the host name and port number of the server. Opens the TCPChannel in background.
     * 
     * @param hostName
     * @param portNumber
     */
    public AndroidChannel(String hostName, int portNumber) {
        this.hostName = hostName;
        this.portNumber = portNumber;
    }

    public void setChannelListener(ChannelListener channelListener) {
        this.channelListener = channelListener;
        androidHandler = new AndroidHandler(channelListener);
    }

    /**
     * Sends a message to the server. Handles the message processing in the background so this method can be called from
     * the UI thread.
     * 
     * @param message
     */
    public void sendMessage(String message) {
        new MessageSender(this, message, channelListener).execute();
    }

    /**
     * Handles messages received from the Server, passing them to the UI thread via the registered handler.
     */
    @Override
    public void messageReceived(String message, int clientID) {
        android.os.Message msg = new android.os.Message();
        msg.obj = message;
        androidHandler.sendMessage(msg);
    }

    /**
     * Returns a TCPChannel to the server, opening it if necessary. Used by MessageSender.doInBackground. This method
     * cannot be called from UI thread.
     * 
     * @throws ChannelException
     */
    TCPChannel getTCPChannel() throws ChannelException {
        if (channel == null) {
            System.out.printf("OPENING channel to %s:%d\n", hostName, portNumber);
            channel = new TCPChannel(hostName, portNumber);
            channel.setMessageListener(this);
            System.out.printf("CHANNEL opened\n");
        }
        return channel;
    }
}

/**
 * MessageSender sends a message to the Server, but does so using an ASyncTask worker thread so that it can be called
 * from the UI thread.
 * 
 * @author jtk
 */
class MessageSender extends AsyncTask<Void, Void, Boolean> {
    AndroidChannel androidChannel;
    String message;
    ChannelListener channelListener;

    MessageSender(AndroidChannel androidChannel, String message, ChannelListener channelListener) {
        this.androidChannel = androidChannel;
        this.message = message;
        this.channelListener = channelListener;
    }

    protected Boolean doInBackground(Void... params) {
        try {
            TCPChannel channel = androidChannel.getTCPChannel();
            channel.sendMessage(message);
            return true;
        } catch (ChannelException e) {
            System.err.printf("ERROR: sendMessage to server failed\n");
            return false;
        }
    }

    protected void onPostExecute(Boolean messageSent) {
        if (!messageSent)
            channelListener.notifySendFailure();
    }
}

/**
 * Handles messages received by the Channel thread that need to be acted on by the UI thread.
 */
class AndroidHandler extends Handler {
    ChannelListener channelListener;

    AndroidHandler(ChannelListener channelListener) {
        this.channelListener = channelListener;
    }

    /**
     * Note: This method is run on the UI thread, so can update the GUI.
     */
    @Override
    public void handleMessage(android.os.Message msg) {
        String message = (String) msg.obj;
        channelListener.messageReceived(message);
    }
}
