package relop;

/**
 * The selection operator specifies which tuples to retain under a condition; in
 * Minibase, this condition is simply a set of independent predicates logically
 * connected by OR operators.
 */
public class Selection extends Iterator {
	Iterator iterator;
	Predicate[] predicates;
	boolean isopen;
	Tuple last_tuple;
  /**
   * Constructs a selection, given the underlying iterator and predicates.
   */
  public Selection(Iterator iter, Predicate... preds) {
	  iterator = iter;
	  predicates = preds;
	  iterator.restart();
	  isopen = true;
	  this.schema = iter.schema;
	  
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gives a one-line explaination of the iterator, repeats the call on any
   * child iterators, and increases the indent depth along the way.
   */
  public void explain(int depth) {
	  System.out.println("Selection");
	  iterator.explain(depth); 
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Restarts the iterator, i.e. as if it were just constructed.
   */
  public void restart() {
	  iterator.restart();
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
	  iterator.close();
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if there are more tuples, false otherwise.
   */
  public boolean hasNext() {
	  if(last_tuple != null)
		  return true;
	  while(iterator.hasNext()) {
		  Tuple tuple = iterator.getNext();
		  for(Predicate p : predicates) {
			  if(p.evaluate(tuple)) {
				  last_tuple = tuple;
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
	  while(iterator.hasNext()) {
		  Tuple tuple = iterator.getNext();
		  for(int i = 0; i < predicates.length; i++) {
			  if(predicates[i].evaluate(tuple)) {
				  return tuple;
			  }
		  }
	  }
	  throw new IllegalStateException("NO_MORE_TUPLES");
	  
    //throw new UnsupportedOperationException("Not implemented");
  }

} // public class Selection extends Iterator
