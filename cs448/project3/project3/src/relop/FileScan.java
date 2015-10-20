package relop;

import global.RID;
import heap.HeapFile;
import heap.HeapScan;

/**
 * Wrapper for heap file scan, the most basic access method. This "iterator"
 * version takes schema into consideration and generates real tuples.
 */
public class FileScan extends Iterator {

	boolean isopen;
	HeapScan heapscan;
    HeapFile heapfile;
    RID last_rid;

    // Schema schema;
  /**
   * Constructs a file scan, given the schema and heap file.
   */
  public FileScan(Schema schema, HeapFile file) {
      heapfile = file;
      this.schema = schema;
      heapscan = heapfile.openScan();
      isopen = true;
  }

  /**
   * Gives a one-line explaination of the iterator, repeats the call on any
   * child iterators, and increases the indent depth along the way.
   */
  public void explain(int depth) {
	  indent(depth);
	  System.out.println("File Scan");
      // throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Restarts the iterator, i.e. as if it were just constructed.
   */
  public void restart() {
      heapscan.close();
      heapscan = heapfile.openScan();
      isopen = true;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if the iterator is open; false otherwise.
   */
  public boolean isOpen() {
      return isopen;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Closes the iterator, releasing any resources (i.e. pinned pages).
   */
  public void close() {
      heapscan.close();
      last_rid = null;
      isopen = false;
//    throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if there are more tuples, false otherwise.
   */
  public boolean hasNext() {
      return heapscan.hasNext();

      //    throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gets the next tuple in the iteration.
   * 
   * @throws IllegalStateException if no more tuples
   */
  public Tuple getNext() {
	  last_rid = new RID();
	  try {
		  Tuple tuple = new Tuple(schema, heapscan.getNext(last_rid));
		  return tuple;
	  } catch (IllegalStateException e) {
		  throw e;
	  }
      //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gets the RID of the last tuple returned.
   */
  public RID getLastRID() {
      return last_rid;
//    throw new UnsupportedOperationException("Not implemented");
  }

} // public class FileScan extends Iterator