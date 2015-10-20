import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Organizes Machines of any kind.
 */
public class LaundryRoom {
  
  // Declare a Map that maps classes to lists of machines.
  private Map<Class<?>, List<Machine>> machineLists = new HashMap<Class<?>, List<Machine>>();
  
  /**
   * @return the number of machines in the room
   */
  public int size() {
    int size = 0;
    for (List<Machine> m : machineLists.values()) {
      size += m.size();
    }
    return size;
  }
  
  /**
   * Adds a new machine to the room.
   * @param m Machine to be added
   */
  public void add(Machine m) {
    // If m's type already has its own list, add it to that one
    if (machineLists.containsKey(m.getClass())) {
      machineLists.get(m.getClass()).add(m);
    }
    // Otherwise create a new one
    else {
      List<Machine> newList = new ArrayList<Machine>();
      machineLists.put(m.getClass(), newList);
      newList.add(m);
    }
  }
  
  /**
   * @return an array containing all of the machines in the room
   */
  public Machine[] getAll() {
    Machine[] all = new Machine[size()];
    int i = 0;
    for (List<Machine> list : machineLists.values()) {
      for (Machine m : list) {
        all[i++] = m;
      }
    }
    return all;
  }
  
  /**
   * Get all of the machines of a certain class as an array, or null if there
   * are none
   * 
   * @param type
   *            The class you want
   * @return An array of class "type"
   */
  public Machine[] getAll(Class<?> type) {
    // Hint: Map.get(key) returns null if there is nothing mapped to key
    List<Machine> list = machineLists.get(type);
    if (list == null) {
      return null;
    } else {
      return (Machine[]) list.toArray(new Machine[list.size()]);
    }
  }
  
  /**
   * Counts machines of a certain class.
   * @param type The class to count, e.g. Washer.class or Dryer.class
   * @return The number of machines in the room of that type
   */
  public int count(Class<?> type) {
    // Hint: Map.get(key) returns null if there is nothing mapped to key
    List<Machine> list = machineLists.get(type);
    if (list == null) {
      return 0;
    } else {
      return list.size();
    }
  }
  
  /**
   * Counts machines of a certain class that are available for use.
   * @param type The class to count, e.g. Washer.class or Dryer.class
   * @return The number of machines in the room of that type
   */
  public int countFree(Class<?> type) {
    int count = 0;
    // Hint: Map.get(key) returns null if there is nothing mapped to key
    List<Machine> list = machineLists.get(type);
    if (list == null) {
      return 0;
    }
    for (Machine m : list) {
      if (m.getStatus() == Machine.STATUS_OK) {
        count++;
      }
    }
    return count;
  }
  
  /**
   * Checks if a free machine of class "type" is in the room.
   */
  public boolean hasFree(Class<?> type) {
    return (countFree(type) > 0);
  }
  
  public boolean hasFreeWashers() {
    return hasFree(Washer.class);
  }
  
  public Machine[] getFreeWashers() {
    return getFree(Washer.class);
  }
  
  public Machine[] getFreeDryers() {
    return getFree(Dryer.class);
  }
  
  
  public boolean hasFreeDryers() {
    return hasFree(Dryer.class);
  }
  /**
   * Returns all of the machines of a certain class as an array that are of status
   * Machine.STATUS_OK, or null if there are none
   * 
   * @param type
   *            The class you want
   * @return An array of class "type"
   */
  public Machine[] getFree(Class<?> type) {
    List<Machine> list = machineLists.get(type);
    // Hint: Map.get(key) returns null if there is nothing mapped to key
    if (list == null) {
      return null;
    } else {
      return (Machine[]) list.toArray(new Machine[list.size()]);
    }
  }
  
}
