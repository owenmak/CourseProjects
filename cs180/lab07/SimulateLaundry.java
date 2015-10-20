import javax.swing.JOptionPane;

/**
 * An interface to pay for laundry machine usage with a student 
 * debit account such as Purdue's BoilerExpress.
 */
public class SimulateLaundry implements Runnable {
    /** The PUID to check against */
    static final String USER_PUID = "00229-12345";
 
    /** Format used for System.format to represent money amounts */
    private static final String MONEY_FMT = "$%.2f";

    /** Number of actions available (wash, dry, report) */
    private static final int NUM_ACTIONS = 3;
    
    /** Number of load sizes available for washing (small, large) */
    private static final int NUM_LOAD_SIZES = 2;
    
    /** Code to represent washing.  Used as index to actionOptions array and for switch statements on return values from JOptionPane.showInputDialog. */
    private static final int ACTION_WASH = 0;
    
    /** Code to represent drying.  Used as index to actionOptions array and for switch statements on return values from JOptionPane.showInputDialog. */
    private static final int ACTION_DRY = 1;
    
    /** Code to represent reporting.  Used as index to actionOptions array and for switch statements on return values from JOptionPane.showInputDialog. */
    private static final int ACTION_REPORT = 2;
    
    /** Code to represent a small load.  Used as index to loadSizeOptions array and for switch statements on return values from JOptionPane.showInputDialog. */
    private static final int LOAD_SIZE_SM = 0;
    
    /** Code to represent a large load.  Used as index to loadSizeOptions array and for switch statements on return values from JOptionPane.showInputDialog. */
    private static final int LOAD_SIZE_LG = 1;

    /** Cost per minute to dry */
    private static final double dryRate = .02;
    
    /** Cost to wash a small load */
    private static final double smRate = 1.50;
    
    /** Cost to wash a large load */
    private static final double lgRate = 2.00;

    // Declare variables to store user selections
    int action, loadSize;
    double bill, time;
    Machine machine;
    String timeString;
    int ret;
    // Machine selection
    Machine[] machinesToShow;

    public double balance = 5.0;

    LaundryRoom room = new LaundryRoom();
    /** 
     * Contains String values for action options, indexed by ACTION_WASH, ACTION_DRY AND ACTION_REPORT.  
     *  Used by JOptionPane.showInputPanel to write text to buttons.
     */
    private static String[] actionOptions = new String[NUM_ACTIONS];

    /**
     * Contains String values for load size options, indexed by LOAD_SIZE_SM and LOAD_SIZE_LG.
     */
    private static String[] loadSizeOptions = new String[NUM_LOAD_SIZES];
    public static void main(String[] args) {
        SimulateLaundry sl = new SimulateLaundry();
        sl.run();
    }
 
    public void run() {
    
        /** Default amount of money to start with */

        boolean exitProgram = false;
        boolean exitActionSelection = false;
        String puid = new String();
  
        init();
        // Check PUID  
        puid = promptPUID();
        while (!puid.equals(USER_PUID)) {            
            TODO1();   ////TODO #1: Fill TODO1 function.            
            puid = promptPUID();
        }
  
        // Main loop
        // Label is to specify which loop to break out of 
        mainloop:
        while (!exitProgram) {
   
            // Check if any machines are available at all.  If not, break out of the loop,
            // going straight to the "Goodbye" message.
            if (TODO2()) { //TODO #2: Fill TODO2() function
                TODO3(); //TODO #3: Fill TODO3() function
                break;
            }
   
            // Initialize variables to store user selections
            bill = time = 0;
            action = loadSize = 0;
            exitActionSelection = false;
            machine = null;
   
            // Action selection loop
            // This is a loop because if an action that is not possible is selected,
            // the loop starts over and the user is prompted to select another one.
   
   
            while (!exitActionSelection) {
                //TODO4
                TODO4();
    
                switch (action) {
                case ACTION_WASH:
                    // Check if there are any washers available. If not, select another action
                    if (TODO5()) { //TODO5
                        TODO6(); //TODO6
                        exitActionSelection = true;
                    } else {
                        TODO7();
                        exitActionSelection = false;
                    }
                    break;
 
                case ACTION_DRY:
                    // Check if there are any dryers available.  If not, select another action
                    if (TODO8()) {
                        // Get the amount of time the user wants to dry
                        TODO9();
                        if (timeString == null) {
                            // user hit cancel
                            break mainloop;
                        }
                        time = Double.valueOf(timeString);
                        exitActionSelection = true;
                    } else {
                        TODO10();
                        exitActionSelection = false;
                    }
                    break;
  
                case ACTION_REPORT:
                    // Exit this loop and go straight to machine selection
                    exitActionSelection = true;
                    break;
                }
    
            }

            // Show only washers or dryers depending on action
            if (action == ACTION_WASH) {
                //TODO11
                TODO11();
            } else if (action == ACTION_DRY) {
                TODO12();                
            } else {
                // For REPORT - show all regardless of status
                TODO13();
            }
   
            // Display a drop-down menu (Still with JOptionPane.showInputDialog) to select a machine.
            TODO14();
            if (machine == null) {
                // user hit cancel
                break mainloop;
            }
            if(machine.getStatus() != Machine.STATUS_OK) {
                TODO27();
                continue;
            }
      
   
            if (action == ACTION_REPORT) {
                // Display thank you message and report the selected machine
                TODO15();
                TODO16();                
            } else {
                // Calculate the bill for either action.
                if (action == ACTION_DRY) {
                    TODO17();
                } else if (action == ACTION_WASH) {
     
                    switch(loadSize) {
                    case LOAD_SIZE_SM:
                        TODO18();
                        break;
                    case LOAD_SIZE_LG:
                        TODO19();
                        break;
                    }
                }
    
                // Check if the balance can cover the bill
                if (TODO20()) {
                    // Show the bill, calculate the new balance, and use the machine
                    TODO21();
                    TODO23();
                    TODO22();
                } else {
                    // Show error message
                    TODO24();
                }
    
            }
     
            // Ask if user wants to repeat the process
            TODO25();
            switch (ret) {
            case JOptionPane.YES_OPTION:
                exitProgram = false;
                break;
            case JOptionPane.NO_OPTION:
                exitProgram = true;
                break;

            }

        }
   
        // Display goodbye message
        TODO26();
    }

    // Helper method to display an input for ID number persistently until one is returned
    static private String promptPUID() {
        String s = null;
        while (s == null) {
            s = JOptionPane.showInputDialog(null,
                                            "Please enter your Purdue ID number", "PUID",
                                            JOptionPane.QUESTION_MESSAGE);
   
        }
        return s;

    }

    public void addMachines() {
        // Create three washers and three dryers
        room.add(new Washer("W01"));
        room.add(new Washer("W02"));
        room.add(new Washer("W03"));
        room.add(new Dryer("D01"));
        room.add(new Dryer("D02"));
        room.add(new Dryer("D03"));
    }
    
    public void init() {
        actionOptions[ACTION_WASH] = "Wash";
        actionOptions[ACTION_DRY] = "Dry";
        actionOptions[ACTION_REPORT] = "Report a problem";
  
        loadSizeOptions[LOAD_SIZE_SM] = "Small";
        loadSizeOptions[LOAD_SIZE_LG] = "Large";
  
        addMachines();
    }
    /*
      TODO #1: Create a dialog such that:
      The text of the dialog should be: "Sorry, that is incorrect. Please try again"
      The title of the dialog should be: "Invalid PUID"
      The message type is ERROR
      Buttons: OK
     */
    public void TODO1() {
        JOptionPane.showMessageDialog(null, "Sorry, that is incorrect. Please try again", "Invalid PUID",
                                      JOptionPane.ERROR_MESSAGE);
    }

    //TODO2: returns true only if room does **NOT** have machines available. Look at room's room.hasFreeWashers() and room.hasFreeDryers() methods
    public boolean TODO2() {
      if (!room.hasFreeWashers() && !room.hasFreeDryers())
        return true;
      else
        return false;
    }

    /*
      TODO3:
      The text of the dialog should be: "Sorry, there are no available machines."
      The title of the dialog should be: "Sorry"
      The message type is ERROR
      Buttons: OK
     */
    public void TODO3() {
        JOptionPane.showMessageDialog(null, "Sorry, there are no available machines.", "Sorry", JOptionPane.ERROR_MESSAGE);
    }

    /*Create a dialog such that:
    The actionOptions array already contains the actions that you will need for this part. These will create the options for the dialog as "Wash", "Dry"
    The title of the dialog should be: ?Menu?
    The text of the dialog should be: ?Your balance is $x.xx. What would you like to do??
    The user action should be stored in variable action
    The message type is QUESTION.
    Buttons: ?Wash?, ?Dry?, ?Report a problem?.
    */
    public void TODO4() {
        action = JOptionPane.showOptionDialog(null, String.format("Your balance is $%.2f. What would you like to do?",balance), "Menu", JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, actionOptions, actionOptions[0]);
    }

    //returns true only if there are washers avilable.
    public boolean TODO5() {
        if (room.hasFreeWashers())
          return true;
        else
          return false; //change this as needed
    }

    /*Create a dialog such that:
    The dialog text should be: ?Are you washing a small or large load??
    The dialog title should be ?Load Size?
    The dialog message type should be QUESTION.
    The dialog options are stored in the array loadSizeOptions. This should create the two buttons "Small", "Large"
    Buttons: ?Small?, ?Large?
    */
    public void TODO6() {
        loadSize = JOptionPane.showOptionDialog(null, "Are you washing a small or large load?", "Load Size", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, loadSizeOptions, loadSizeOptions[0]);
    }

    /*Create a dialog such that:
    The dialog text should be: ?Sorry, there are no washers available.?
    The dialog title should be: ?Sorry?
    The message type is ERROR
    Buttons: ?OK?
    */
    public void TODO7() {
        JOptionPane.showMessageDialog(null, "Sorry, there are no washers available.", "Sorry", JOptionPane.ERROR_MESSAGE);
    }

    //returns true only if there are dryers avilable.
    public boolean TODO8() {
      if (room.hasFreeDryers())
        return true;
      else
        return false; //change this as needed
    }
    
    /*Create an **input** dialog such that:
    The dialog text should be: ?How long would you like to dry (in minutes)??
    The dialog title should be: ?Drying time?
    The dialog message type is QUESTION
    Buttons: ?OK?, ?Cancel?
    */
    public void TODO9() {
        timeString = JOptionPane.showInputDialog(null, "How long would you like to dry (in minutes)?", "Drying time", JOptionPane.QUESTION_MESSAGE);//timeString = ... complete this
    }

    /*Create a dialog such that:
    The dialog text should be: ?Sorry, there are no dryers available.?
    The dialog title should be: ?Sorry?
    The dialog message type is ERROR
    Buttons: ?OK?
    */
    public void TODO10() {
        JOptionPane.showMessageDialog( null, "Sorry, there are no dryers available.", "Sorry", JOptionPane.ERROR_MESSAGE);
    }

    /*
    Returns only washers
    */
    public void TODO11() {
        machinesToShow = room.getFreeWashers();
    }

    /*
    Returns only dryers
    */
    public void TODO12() {
        machinesToShow = room.getFreeDryers();
    }

    /*
    Returns all machines
    */
    public void TODO13() {
        machinesToShow = room.getAll();
    }

    /*Create a dialog such that:
    The dialog text should be: ?Which machine??
    The dialog title should be: ?Machine Selection?
    The dialog message type is QUESTION.
    Buttons: ?OK?, ?Cancel?
    You will need to cast the return value of the dialog to Machine type.
    */
    public void TODO14() {
        machine = (Machine) JOptionPane.showInputDialog( null, "Which machine?", "Machine Selection", JOptionPane.QUESTION_MESSAGE, null, machinesToShow, machinesToShow[0]);
    }

    /*Create a dialog such that:
    The dialog text should be: ?Thank you. The issue has been reported.?
    The dialog title should be: ?Thanks?
    The dialog message type is INFORMATION.
    Buttons: ?OK?
    */
    public void TODO15() {
        JOptionPane.showMessageDialog(null, "Thank you. The issue has been reported.", "Thanks", JOptionPane.INFORMATION_MESSAGE);
    }

    //TODO23: report the machine as needed.
    public void TODO16() {
        machine.report();
    }

    //Do your bill computation for a Dry action. The cost of a dry action is the time * dryRate
    public void TODO17() {
        bill += time * dryRate;
    }
    
    //Do your bill computation for a Small Wash action. The cost is stored in smRate
    public void TODO18() {
        bill += smRate;
    }
    
    //Do your bill computation for a Large Wash action. The cost is stored in lgRate
    public void TODO19() {
        bill += lgRate;
    }

    //TODO23: Use the machine
    public void TODO23() {
        machine.use();
    }
    
    //TODO20: this method returns true only if balance is enough to pay the bill.
    public boolean TODO20() {
        if (balance >= bill)
          return true;
        else
          return false; //change this as needed
    }

    //compute the new balance by subtracting the bill amount
    public void TODO21() {
        balance -= bill;
    }

    /*Create a dialog such that:
    The dialog text should be: ?You were charged $x.xx. Your new balance is $x.xx.?
    The dialog title should be: ?Success?
    The message type is INFORMATION.
    Buttons: ?OK?
    */
    public void TODO22() {
        JOptionPane.showMessageDialog(null, "You were charged " +String.format(MONEY_FMT,bill) + ". Your new balance is " + String.format(MONEY_FMT,balance) +"." , "Success", JOptionPane.INFORMATION_MESSAGE);
    }

    /*Create a dialog such that:
    The dialog text should be: ?Sorry, your balance $x.xx is inadequate for your bill, $x.xx.?
    The dialog title should be: ?Indadequate Funds?
    The message type is ERROR.
    Buttons: ?OK?
    */
    public void TODO24() {
        JOptionPane.showMessageDialog(null, "Sorry, your balance " + String.format(MONEY_FMT, balance) + " is inadequate for your bill, " + String.format(MONEY_FMT, bill) + ".", "Indadequate Funds", JOptionPane.ERROR_MESSAGE);
    }

    /*Create a dialog such that:
    The dialog text should be: ?Would you like to perform another action??
    The dialog title should be: ?Are you done??
    The message type is QUESTION.
    Buttons: ?Yes?, ?No?
    */
    public void TODO25() {
        ret = JOptionPane.showOptionDialog(null, "Would you like to perform another action?", "Are you done?", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null );
    }

    /*Create a dialog such that:
    The dialog text should be: ?Thank you, come again!?
    The dialog title should be: ?Thanks?
    The message type is PLAIN.
    Buttons: ?OK?
    */
    public void TODO26() {
        JOptionPane.showMessageDialog(null, "Thank you, come again!", "Thanks", JOptionPane.PLAIN_MESSAGE);
    }

    /*Create a dialog such that:
    The dialog text should be: ?Sorry! Machine not available.?
    The dialog title should be: ?Sorry?
    The message type is ERROR.
    Buttons: ?OK?
    */
    public void TODO27() {
    }

}