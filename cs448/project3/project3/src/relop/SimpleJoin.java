package relop;

/**
 * The simplest of all join algorithms: nested loops (see textbook, 3rd edition,
 * section 14.4.1, page 454).
 */
public class SimpleJoin extends Iterator {
	Iterator left_iterator;
	Iterator right_iterator;
	Predicate[] predicates;
	boolean isopen;
	Tuple last_tuple;
	
  /**
   * Constructs a join, given the left and right iterators and join predicates
   * (relative to the combined schema).
   */
  public SimpleJoin(Iterator left, Iterator right, Predicate... preds) {
	left_iterator = left;
	right_iterator = right;
	predicates = preds;
	schema = Schema.join(left_iterator.schema, right_iterator.schema);
	left_iterator.restart();
	right_iterator.restart();
	isopen = true;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gives a one-line explaination of the iterator, repeats the call on any
   * child iterators, and increases the indent depth along the way.
   */
  public void explain(int depth) {
	  indent(depth);
	  System.out.println("SimpleJoin");
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Restarts the iterator, i.e. as if it were just constructed.
   */
  public void restart() {
		left_iterator.restart();
		right_iterator.restart();
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
	  right_iterator.close();
	  left_iterator.close();
	  isopen = false;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if there are more tuples, false otherwise.
   */
  public boolean hasNext() {
	  if(last_tuple != null)
		  return true;
	  while(left_iterator.hasNext()) {
		  Tuple left_tuple;
		  Tuple right_tuple;
		  Tuple comb_tuple;
		  left_tuple = left_iterator.getNext();
		  if(!right_iterator.hasNext())
			  right_iterator.restart();
		  right_tuple = right_iterator.getNext();
		  comb_tuple = Tuple.join(left_tuple, right_tuple, schema);
		  for(int i = 0; i < predicates.length; i++) {
			  if(!predicates[i].evaluate(comb_tuple))
				  break;
			  if(i == predicates.length - 1) {
				  last_tuple = comb_tuple;
				  return true;
			  }
		  }
	  }
	  return false;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gets the next tuple in the iteration.
   * 
   * @throws IllegalStateException if no more tuples
   */
  public Tuple getNext() {
	  if(last_tuple != null) {
		  Tuple tuple = last_tuple;
		  last_tuple = null;
		  return tuple;
	  }
	  
	  while(left_iterator.hasNext()) {
		  Tuple left_tuple;
		  Tuple right_tuple;
		  Tuple comb_tuple;
		  left_tuple = left_iterator.getNext();
		  if(!right_iterator.hasNext())
			  right_iterator.restart();
		  right_tuple = right_iterator.getNext();
		  comb_tuple = Tuple.join(left_tuple, right_tuple, schema);
		  for(int i = 0; i < predicates.length; i++) {
			  if(!predicates[i].evaluate(comb_tuple))
				  break;
			  if(i == predicates.length - 1) {
				  return comb_tuple;
			  }
		  }
	  }
	  return null;
	  
  }

} // public class SimpleJoin extends Iterator
