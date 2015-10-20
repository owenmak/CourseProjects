/**
 * Abstract class that represents a laundry machine.
 */
public abstract class Machine {
	/** Machine is ready for use */
	public static final int STATUS_OK = 0;
	
	/** Machine is being used and cannot be used */
	public static final int STATUS_BUSY = 1;
	
	/** Machine has been reported and cannot be used */
	public static final int STATUS_DOWN = 2;
	
	private int status;
	private String name;
		
	/** Creates a named Machine. */
	public Machine(String name) {
		this.name = name;
		this.status = STATUS_OK;
	}
	
	/** Creates a nameless Machine. */
	public Machine() {
		// empty constructor
	}
	
	/** Returns the status of the machine.
	 * 
	 * @return Either STATUS_OK, STATUS_BUSY OR STATUS_DOWN
	 */
	public int getStatus() {
		return status;
	}
	
	/** Mark this machine as being in use. */
	public void use() {
		status = STATUS_BUSY;
	}
	
	/** Mark this machine as being down. */
	public void report() {
		status = STATUS_DOWN;
	}
	
	/**
	 * Returns the name of the machine in addition to its status.  Format: "[NAME] - [OK|Busy|Down]"
	 * Example: W01 - OK
	 */
	public String toString() {
		StringBuilder s = new StringBuilder();
		s.append(name + " - ");
		switch (status) {
		case STATUS_OK:
			s.append("OK");
			break;
		case STATUS_BUSY:
			s.append("Busy");
			break;
		case STATUS_DOWN:
			s.append("Down");
			break;
		}
		return s.toString();
	}

}
