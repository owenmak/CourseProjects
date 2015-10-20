package edu.purdue.cs180.safewalk;

import java.util.Observable;
import java.util.Observer;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

/**
 * VolunteerFragment is the starting point for the Volunteer application.
 *
 * INSTRUCTIONS: Study RequesterFragment.java and fill in comparable code where TODO markers are.
 * 
 * @author zmai
 * @author jiang221
 */
@SuppressLint("DefaultLocale")
public class VolunteerFragment extends Fragment implements ChannelListener, View.OnClickListener, Observer, OnItemSelectedListener {
    final static Model model = new Model();
    final static AndroidChannel channel = MainActivity.initializeChannel();
    private Button button;
    private TextView status;
    private Spinner locations;

    /**
     * Creates the Volunteer user interface, and sets up the model and channel to the server.
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.volunteer, container, false);
        button = (Button) rootView.findViewById(R.id.volunteer_button);
        status = (TextView) rootView.findViewById(R.id.volunteer_status_textview);
        locations = (Spinner) rootView.findViewById(R.id.locations_spinner);

        // TODO: add this Fragment object to the Model observer and AndroidChannel listener...
        model.addObserver(this);
        channel.setChannelListener(this);
        // TODO: set/restore the UI state from the model...
        update(model, null);
        // TODO: add listeners for the Volunteer button and spinner...
        button.setOnClickListener(this);
        locations.setOnItemSelectedListener(this);
        return rootView;
    }
    
    /**
     * Cleans up on exit by deleting the model observer.
     */
    @Override
    public void onDestroyView() {
        super.onDestroyView();
        // TODO: add code to delete this Observer from the model
        super.onDestroyView();
        model.deleteObserver(this);
    }

    /**
     * Handles processing of "Press When Ready" button press.
     */
    @Override
    public void onClick(View v) {
        // TODO Delete this line (!)
    	model.setUIEnabled(false);
        model.setStatus("Sending message to server; waiting for requester");
        model.notifyObservers();
        // TODO: disable controls until request assigned (or failure sent)...
    	
        // TODO: prepare message and send to server...
        String selectedItem = (String) locations.getSelectedItem();
        String[] words = selectedItem.split(" ");
        String message = "VOLUNTEER " + words[0];
        System.out.printf("Sending: %s\n", message);
        channel.sendMessage(message);
    }

    /**
     * Updates the view widgets whenever the model changes.
     */
    @Override
    public void update(Observable observable, Object data) {
        // TODO: using data from the model, update the UI widgets (locations, button, and status)
    	locations.setSelection(model.getLocation(), true);
        button.setEnabled(model.isUIEnabled());
        locations.setEnabled(model.isUIEnabled());
        status.setText(model.getStatus());
    }

    /**
     * Receives a message from the AndroidChannel on the UI thread, so safe to call UI methods. This method is for the
     * Volunteer application, so the only message it knows about it is the LOCATION message: "LOCATION id urgency".
     */
    public void messageReceived(String message) {
        // TODO: handle message from server (only valid one is "LOCATION ID URGENCY") by updating model
        // TODO: don't forget to notify observers
    		String[] fields = message.split(" ");
    		if (fields[0].equals("LOCATION") && (fields[2].equals("EMERGENCY") || fields[2].equals("URGENT") || fields[2].equals("NORMAL"))) {
    			try {
    				Integer.parseInt(fields[1]);
    	    		model.setUIEnabled(true);
    	            model.setStatus(String.format("Proceed to %s, Urgency: %s", fields[1], fields[2]));
    			} catch (NumberFormatException e) {
    				model.setStatus("unexpected message: " + message);
    			}
    	} else
    		model.setStatus("unexpected message: " + message);
    	model.notifyObservers();
    }

    /**
     * Handles changes to the "locations" and "urgencies" spinners. Updates the model.
     */
    @Override
    public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
        // TODO: when an item is selected on the spinner, update the model to keep track of it
        if (arg0 == locations)
            model.setLocation(arg2);
        else
            System.err.printf("ERROR: Unexpected spinner (%s)\n", arg0.toString());
    }

    /**
     * Handles resets to the spinner; which we ignore.
     */
    @Override
    public void onNothingSelected(AdapterView<?> arg0) {
        // do nothing
    }

    /**
     * Updates the status in the event of server connection failure. Called by AndroidChannel.
     */
    public void notifySendFailure() {
    	model.setStatus("Error sending message to server; check server status and network connection");
        model.setUIEnabled(true);
        model.notifyObservers();
        // TODO: the network connection is down or server unavailable; update status message in model
        // TODO: don't forget to notify observers
    }
}
