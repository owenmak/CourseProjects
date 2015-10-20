/**
 * CS180 - Lab 04 - Male.java
 *
 * This program represents a Male adult or child and his
 * associated information (PUID, age, and cholesterol levels).)
 *
 * @Zilun Mai, <zmai@purdue.edu>
 *
 * @lab (Put your lab section # here)
 *
 * @Sep 11 (Put the date you completed this lab here)
 */


public class Male {
  String puid;
  int age;
  int ldl;
  int hdl;
  int other;
  public Male (String puid, int age, int ldl, int hdl, int other) {
    this.puid = puid;
    this.age = age;
    this.ldl = ldl;
    this.hdl = hdl;
    this.other = other;
  }
  
  
  /**
   * @return Returns an int representing the total cholesterol 
   * which is a sum of this Male's LDL, HDL, and other values. 
   */
  public int getTotalCholesterol() {
    return (this.ldl+this.hdl+this.other);
  }
  
  
  /**
   * @return Returns a boolean: This method returns True
   * if the total cholesterol for this Male is less than 
   * 200 mg/dl for an adult or less than 170 mg/dl for a
   * child. 
   * 
   * Otherwise this method returns False if the TC
   * is greater than or equal to 200 mg/dl for an adult or
   * greater than or equal to 170 mg/dl for a child.
   */
  public boolean hasGoodTotalCholesterol() {
    if (this.age>=18){
      if(this.getTotalCholesterol()<200)
        return true;
      else 
        return false;
    }
    else {
      if(this.getTotalCholesterol()<170) 
        return true;
      else
        return false;
    }
  }
  
  
  /**
   * @return Returns a boolean: This method returns True if
   * the HDL level is within the healthy range; False otherwise.
   * 
   * A healthy range for HDL is greater than or equal to 
   * 40 mg/dl for both adults and children.
   */
  public boolean hasGoodHDL() {
    if(this.hdl>=40) 
      return true;
    else 
      return false;
  }
  
  
  /**
   * @return Returns a boolean: This method returns True if
   * the LDL level is within the healthy range: A healthy LDL level 
   * for an adult should be less than or equal to 130 mg/dl; 
   * a healthy LDL level for a child should be 
   * less than or equal to 110 mg/dl. 
   * 
   * This method returns False if the LDL level is 
   * greater than 130 mg/dl for an adult or 
   * greater than 110 mg/dl for a child.
   */
  public boolean hasGoodLDL() {
    boolean flag = false;
    if ((this.age>=18) && (this.ldl<=130)) 
      flag = true;
    else if((this.age<18) && (this.ldl<=110)) 
      flag = true;
    return flag; 
    }
  } 