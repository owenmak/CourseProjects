package edu.purdue.cs180.safewalk;

import java.util.Observable;

/**
 * Model contains the data associated with the application. It is an observable so that the UI can be notified of
 * changes.
 * 
 * Note: The Requester and Volunteer Fragments share this class, but each has its own instance (object) of it.
 * 
 * @author jtk
 * 
 */
public class Model extends Observable {
    private boolean uiEnabled = true;
    private String status = null;
    private int location = 0;
    private int urgency = 0;

    /*
     * Setters and getters below. All setters need to do a setChanged() so that observers can be notified.
     */
    void setStatus(String status) {
        this.status = status;
        setChanged();
    }

    public String getStatus() {
        return status;
    }
    
    void setUIEnabled(boolean b) {
        uiEnabled = b;
        setChanged();
    }

    public boolean isUIEnabled() {
        return uiEnabled;
    }

    public int getLocation() {
        return location;
    }

    public void setLocation(int location) {
        this.location = location;
        setChanged();
    }

    public int getUrgency() {
        return urgency;
    }

    public void setUrgency(int urgency) {
        this.urgency = urgency;
        setChanged();
    }
}
