

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.NotActiveException;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JDialog;
import javax.swing.JButton;
import javax.swing.JRadioButton;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class ContactsPanel extends JPanel{
 JLabel status = new JLabel(); //a label for the bottom
 Person[] contacts = new Person[200]; //MAX number of contacts is 200
 int length = 0; //number of contacts currently in the list
 
 /* The constructor for the ContactsPanel Object. Read through and try to
  * understand how this object is created.
  */
 public ContactsPanel(){
  super(new BorderLayout()); //call to JFrame's constructor, passing in a BorderLayout
  
  //create the different tabs (which are JPanels) in different methods that return JPanels
  JPanel addTab = createAddTab(); //you create the createAddTab() method 
  JPanel viewTab = createViewTab(); //you create the createViewTab() method 
  
  //creates a JLabel and tells it to be in the center
  status = new JLabel("", JLabel.CENTER);
  
  //creates the tabs, each with its 
  JTabbedPane tabbedPane = new JTabbedPane();
  tabbedPane.addTab("Add Contacts", addTab);
  tabbedPane.addTab("View Contacts", viewTab);
  
  //adds the tabbedPAne and the bottom JLabel to the main window.
  this.add(tabbedPane, BorderLayout.CENTER);
  this.add(status, BorderLayout.PAGE_END);
  
  //sets a border around the JLabel
        status.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
 }
 
 
 
 /* Use this method to create and return a JPanel for adding 
  * a contact to the contacts list.
  */
 private JPanel createAddTab(){
  JPanel result = new JPanel(); //the JPanel to return
  final int numFields = 3; //the number of fields in a person,
  JLabel[] jl = new JLabel[numFields];//create an array  of JLabels with length of the int numFields
  final JTextField[] jt = new JTextField[numFields]; //create an array of JTextFields with length of the int numFields
  jl[0] = new JLabel("0: Enter Contact Name");
  jl[1] = new JLabel("1. Enter phone number (no dashes)");
  jl[2] = new JLabel("2. Enter Contact E-mail");
  jt[0] = new JTextField();
  jt[1] = new JTextField();
  jt[2] = new JTextField();
  
  
  //set each label and textfield. 
  //The 0th label and textfield should be for the name, this field can not be empty.
  //The 1st should be for the phone number, it can be empty or numbers without dashes,
  //and the phone number should not exceed 10 digits.
  //The 2nd should be for the email, can be empty.
  //(Run the jar file for exact wording)
  
 
  //create a submit button
  
  JButton submit = new JButton("submit");
  submit.addActionListener(new ActionListener() {
    public void actionPerformed(ActionEvent e) {
      boolean ready = true;
      if (jt[0].getText().isEmpty()) {
        status.setText("Must Enter a name!");
        ready = false;
      }
      try {
        if (!jt[1].getText().isEmpty()) {
          long phone = Long.parseLong(jt[1].getText());
          if (phone > 999999999) {
            status.setText("Phone number must be less than 10 digits!");
            ready = false;
          }
        }
      }
        catch (NumberFormatException nfe) {
          status.setText("Phone number can't have dashes!");
          ready = false;
        }
        if (ready) {
          contacts[length] = new Person (jt[0].getText(), Long.parseLong(jt[1].getText()), jt[2].getText());
          length++;
          for (int i = 0; i < 3; i++)
            jt[i].setText("");
        }
    }
  });
  /* Add a new action listener to the button. In the action listener's
   * actionPreformed method, make sure that name is not blank, and that 
   * if a phone number has been entered correctly (no dashes). If so
   * add the person into the contacts array.
   */
  
  
  //this statement must be called for aesthetics
  //try commenting it out when finished to see what happens
  result.setLayout(new BoxLayout(result, BoxLayout.PAGE_AXIS));
  
  //prepare the result JPanel by adding all fields and buttons
   for (int i = 0; i < 3; i++) {
     result.add(jl[i]);
     result.add(jt[i]);
   }
   result.add(submit);
   return result;
 }
 
 /* create the method that returns the panel that you see in the 
  * finished product when you click the view tab.
  * There are some tips in the handout that can be helpful for you.
  */
 private JPanel createViewTab(){
   final JPanel viewTab = new JPanel();//create a JPanel and set its layout with proper type by calling setLayout()
   viewTab.setLayout(new BoxLayout(viewTab, BoxLayout.PAGE_AXIS));
   JButton refresh = new JButton("refresh");
   refresh.addActionListener(new ActionListener() {
     public void actionPerformed(ActionEvent e) {
       JLabel[] cl;
       cl = contactLabels();
       for(int i = 0; i < cl.length; i++) {
         viewTab.add(cl[i]);
       }
     }
   });
   viewTab.add(refresh);
   return viewTab;
   
   //create a JButtion with name "refresh" and add it to the JPanel you just created
   
   
   /* Add a new action listener to the JButtion you just created. In the action listener's
    * actionPerformed method, you need to get an JLabel array that contains all the JLabels.
    * Then you need to add all these Jlabels to the panel. 
    */
   
 }
 
 
 /*
  * This is a method that creates a bunch of JLabels based on the number of contacts
  * in the Person array.
  */
 private JLabel[] contactLabels(){
  JLabel[] contactLabels = new JLabel[4 * length]; //4 JLabels per person
  for(int i = 0; i < length; i ++){
   int j = 4 * i; //starting index contactLabels
   contactLabels[j] = new JLabel("Name: "+ contacts[i].getName());
   String phoneNumber = contacts[i].getNumber() == 0 ? "" : Long.toString(contacts[i].getNumber());
   contactLabels[j+1] = new JLabel("Phone Number: "+ phoneNumber);
   contactLabels[j+2] = new JLabel("Email: "+ contacts[i].getEmail());
   contactLabels[j+3] = new JLabel("*******************************");
  }
  
  return contactLabels;
 }
 
 
 
 //the main method. follow instructions.
 public static void main(String[] args){
   JFrame jf = new JFrame("Main Window");
   jf.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
   ContactsPanel cp = new ContactsPanel();
   cp.setPreferredSize(new Dimension(320,240));
   
   jf.setContentPane(cp);
   jf.pack();
   jf.setVisible(true);
  //create the JFrame to be used as the main window.
 
  //set the default close operation to EXIT_ON_CLOSE
  
  //creates the ContactsPanel and pass in the JFrame you created above.

  //set the size of the Contactpanels to 320 by 240
  
  
  //call setContentPane on your JFrame object and pass in your ContactsPanel object
  
  
  //packs the window and sets it visible

 }
}
