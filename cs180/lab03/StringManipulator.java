/**
 * Purdue CS 180 Fall 2013
 * Lab 3
 * 
 * Sample implementation of StringManipulator
 * 
 * @author Zilun Mai <zmai@purdue.edu>
 */

/**
 * Manipulate names and addresses.
 */

public class StringManipulator {
  public String makeUsername(String name) {
    return (name.substring(0,1)+name.substring(name.indexOf(' ')+1)).toLowerCase();
  }
  public String makeEmail(String name, String domain){
    return ((name.substring(0,1)+name.substring(name.indexOf(' ')+1))+"@"+domain).toLowerCase();
  }
  public String winToUnixPath(String winpath) {
    return "/homes/" + this.makeUsername(winpath.substring(winpath.indexOf("\\",4)+1, winpath.indexOf("\\",10))) + "/" + winpath.substring(winpath.indexOf("\\",10)+1);
}
}
