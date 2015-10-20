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
 * RequesterFragment is the starting point for the Requester application.
 * 
 * @author fmeawad
 * @author jtk
 */
@SuppressLint("DefaultLocale")
public class RequesterFragment extends Fragment implements ChannelListener, View.OnClickListener, Observer, OnItemSelectedListener {
    final static Model model = new Model();
    final static AndroidChannel channel = MainActivity.initializeChannel();

    private Button button;
    private TextView status;
    private Spinner locations;
    private Spinner urgencies;

    /**
     * Creates the Android user interface, and sets up the model and channel to the server.
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.requester, container, false);
        button = (Button) rootView.findViewById(R.id.requester_button);
        status = (TextView) rootView.findViewById(R.id.requester_status_textview);
        locations = (Spinner) rootView.findViewById(R.id.locations_spinner);
        urgencies = (Spinner) rootView.findViewById(R.id.urgencies_spinner);

        // add this Fragment object to the Model observer and AndroidChannel listener...
        model.addObserver(this);
        channel.setChannelListener(this);
        
        // set/restore the UI state from the model...
        update(model, null);

        // add listeners for the Request button and spinners...
        button.setOnClickListener(this);
        locations.setOnItemSelectedListener(this);
        urgencies.setOnItemSelectedListener(this);
        return rootView;
    }
    
    /**
     * Cleans up on exit by deleting the model observer.
     */
    @Override
    public void onDestroyView() {
        super.onDestroyView();
        model.deleteObserver(this);
    }

    /**
     * Handles processing of "Submit Request" button press.
     */
    @Override
    public void onClick(View v) {
        // disable controls until volunteer chosen (or send failure)...
        model.setUIEnabled(false);
        model.setStatus("Sending message to server; waiting for volunteer");
        model.notifyObservers();

        // prepare message and send to server...
        String selectedItem = (String) locations.getSelectedItem();
        String[] words = selectedItem.split(" ");
        String urgency = (String) urgencies.getSelectedItem();
        String message = "REQUEST " + words[0] + " " + urgency.toUpperCase();
        System.out.printf("Sending: %s\n", message);
        channel.sendMessage(message);
    }

    /**
     * Updates the view widgets whenever the model changes.
     */
    @Override
    public void update(Observable observable, Object data) {
        locations.setSelection(model.getLocation(), true);
        urgencies.setSelection(model.getUrgency(), true);

        button.setEnabled(model.isUIEnabled());
        locations.setEnabled(model.isUIEnabled());
        urgencies.setEnabled(model.isUIEnabled());

        status.setText(model.getStatus());
    }

    /**
     * Receives a message from the AndroidChannel on the UI thread, so safe to call UI methods. This method is for the
     * Requester application, so the only message it knows about it is the VOLUNTEER message: "VOLUNTEER id minutes".
     */
    public void messageReceived(String message) {
        String[] fields = message.split(" ");

        if (fields[0].equals("VOLUNTEER")) {
            model.setUIEnabled(true);
            model.setStatus(String.format("Volunteer %s assigned and will arrive in %s minutes", fields[1], fields[2]));
        } else
            model.setStatus("Unexpected message: " + message);
        model.notifyObservers();
    }

    /**
     * Handles changes to the "locations" and "urgencies" spinners. Updates the model.
     */
    @Override
    public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
        if (arg0 == locations)
            model.setLocation(arg2);
        else if (arg0 == urgencies)
            model.setUrgency(arg2);
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
    }
}
