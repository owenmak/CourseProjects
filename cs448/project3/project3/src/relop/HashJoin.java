package relop;

import global.SearchKey;
import heap.HeapFile;
import index.BucketScan;
import index.HashIndex;

/**
 * Implements the hash-based join algorithm described in section 14.4.3 of the
 * textbook (3rd edition; see pages 463 to 464). HashIndex is used to partition
 * the tuples into buckets, and HashTableDup is used to store a partition in
 * memory during the matching phase.
 */
public class HashJoin extends Iterator {

//	Iterator left_iterator;
//	Iterator right_iterator;
	IndexScan left_iscan;
	IndexScan right_iscan;
	int left_column;
	int right_column;
	boolean isopen;
	HashTableDup hashtabledup;
	Tuple curr_left;
	int curr_index;
	Tuple last_tuple;
  /**
   * Constructs a hash join, given the left and right iterators and which
   * columns to match (relative to their individual schemas).
   */
  public HashJoin(Iterator left, Iterator right, Integer lcol, Integer rcol) {
	  left_iscan = generate_scan(left, lcol);
	  right_iscan = generate_scan(right, rcol);
	  curr_index = 0;
	  this.schema = Schema.join(left.schema,right.schema);
	  left_column = lcol;
	  right_column = rcol;
	  left_iscan.restart();
	  right_iscan.restart();
	  isopen = true;
	  curr_left = left_iscan.getNext();
	  hashtabledup = new HashTableDup();
	  while(right_iscan.hasNext()) {
		  Tuple tuple = right_iscan.getNext();
		  SearchKey searchkey = right_iscan.getLastKey();
		  hashtabledup.add(searchkey, tuple);
	  }
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Constructs/modify the scan to a indexScan.
   */
  private IndexScan generate_scan(Iterator itr, int column) {
	  if(itr instanceof IndexScan)
		  return (IndexScan)itr;
	  HeapFile heapfile;
	  HashIndex hashindex = new HashIndex(null);
	  FileScan fs;
	  if(itr instanceof FileScan) {
		  heapfile = ((FileScan) itr).heapfile;
	  }
	  else {
		  heapfile = new HeapFile(null);
		  while(itr.hasNext()) {
			  heapfile.insertRecord(itr.getNext().data);
		  }
	  }
	  fs = new FileScan(itr.schema, heapfile);
	  while(fs.hasNext()) {
		  SearchKey searchkey = new SearchKey(fs.getNext().getField(column));
          hashindex.insertEntry(searchkey, fs.getLastRID());
	  }
	  fs.close();
	  return new IndexScan(itr.schema, hashindex, heapfile);
  }
  /**
   * Gives a one-line explanation of the iterator, repeats the call on any
   * child iterators, and increases the indent depth along the way.
   */
  public void explain(int depth) {
	  indent(depth);
	  System.out.println("HashJoin");
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Restarts the iterator, i.e. as if it were just constructed.
   */
  public void restart() {
	  left_iscan.restart();
	  curr_left = left_iscan.getNext();
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
	  isopen = false;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if there are more tuples, false otherwise.
   */
  public boolean hasNext() {
	  if(last_tuple!=null) {
		  return true;
	  }
	  SearchKey searchkey = new SearchKey(curr_left.getField(left_column));
	  
	  //System.out.println(curr_left.getField(left_column) + "  " + left_column + "-----");
	  
	  Tuple[] tuples = hashtabledup.getAll(searchkey);
	  while(tuples == null || curr_index > tuples.length - 1) {
		  curr_index = 0;
		  
		  try {
		  curr_left = left_iscan.getNext();
		  }	catch(IllegalStateException e) {
			  return false;
		  }
		  tuples = hashtabledup.getAll(new SearchKey(curr_left.getField(left_column)));
	  }
	  last_tuple = Tuple.join(curr_left, tuples[curr_index], schema);
	  curr_index++;
	  return true;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gets the next tuple in the iteration.
   * 
   * @throws IllegalStateException if no more tuples
   */
  public Tuple getNext() {
	  if(last_tuple!=null) {
		  Tuple tuple = last_tuple;
		  last_tuple = null;
		  return tuple;
	  }
	  Tuple[] tuples = hashtabledup.getAll(new SearchKey(curr_left.getField(left_column)));
	  while(tuples == null || curr_index > tuples.length - 1) {
		  curr_index = 0;
		  curr_left = left_iscan.getNext();		//will throw IllegalStateException.
		  tuples = hashtabledup.getAll(new SearchKey(curr_left.getField(left_column)));
	  }
	  Tuple comb_tuple = Tuple.join(curr_left, tuples[curr_index], schema);
	  curr_index++;
	  return comb_tuple;
    //throw new UnsupportedOperationException("Not implemented");
  }

} // public class HashJoin extends Iterator
