package relop;

import global.SearchKey;
import heap.HeapFile;
import index.BucketScan;
import index.HashIndex;
import index.HashScan;

/**
 * Wrapper for hash scan, an index access method.
 */
public class KeyScan extends Iterator {
	HashScan hashscan;
	HeapFile heapfile;
	HashIndex hashindex;
	SearchKey searchkey;
	boolean isopen;
  /**
   * Constructs an index scan, given the hash index and schema.
   */
  public KeyScan(Schema schema, HashIndex index, SearchKey key, HeapFile file) {
      heapfile = file;
      this.schema = schema;
      hashindex = index;
      searchkey = key;
      hashscan = hashindex.openScan(searchkey);
      isopen = true;
  }

  /**
   * Gives a one-line explaination of the iterator, repeats the call on any
   * child iterators, and increases the indent depth along the way.
   */
  public void explain(int depth) {
	  indent(depth);
	  System.out.println("Key Scan");
  }

  /**
   * Restarts the iterator, i.e. as if it were just constructed.
   */
  public void restart() {
	  hashscan.close();
      hashscan = hashindex.openScan(searchkey);
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
	  hashscan.close();
	  isopen = false;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if there are more tuples, false otherwise.
   */
  public boolean hasNext() {
	  return hashscan.hasNext();
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gets the next tuple in the iteration.
   * 
   * @throws IllegalStateException if no more tuples
   */
  public Tuple getNext() {
	  try {
		  byte[] data = heapfile.selectRecord(hashscan.getNext());
		  return new Tuple(schema, data);
	  } catch(IllegalStateException e) {
		  throw e;
	  }
    //throw new UnsupportedOperationException("Not implemented");
  }

} // public class KeyScan extends Iterator
