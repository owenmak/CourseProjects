package relop;

/**
 * The projection operator extracts columns from a relation; unlike in
 * relational algebra, this operator does NOT eliminate duplicate tuples.
 */
public class Projection extends Iterator {
	Iterator iterator;
	Integer[] fld;
	boolean isopen;
  /**
   * Constructs a projection, given the underlying iterator and field numbers.
   */
  public Projection(Iterator iter, Integer... fields) {
	  iterator = iter;
	  iterator.restart();
	  fld = fields;
	  schema = new Schema(fields.length);
	  for(int i = 0; i < fields.length; i++) {
		  int field_num = fields[i];
		  schema.initField(i, iterator.schema.fieldType(field_num), 
				  iterator.schema.fieldLength(field_num), iterator.schema.fieldName(field_num));
	  }
	  
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gives a one-line explaination of the iterator, repeats the call on any
   * child iterators, and increases the indent depth along the way.
   */
  public void explain(int depth) {
	  indent(depth);
	  System.out.println("Projection");
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
	  isopen = false;
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Returns true if there are more tuples, false otherwise.
   */
  public boolean hasNext() {
	  return iterator.hasNext();
    //throw new UnsupportedOperationException("Not implemented");
  }

  /**
   * Gets the next tuple in the iteration.
   * 
   * @throws IllegalStateException if no more tuples
   */
  public Tuple getNext() {
	  try {
		  Tuple old_tuple = iterator.getNext();
		  Tuple new_tuple = new Tuple(schema);
		  for(int i = 0; i < fld.length; i++) {
			  int field_num = fld[i];
			  new_tuple.setField(i, old_tuple.getField(field_num));
		  }
		  return new_tuple;
	  } catch (IllegalStateException e) {
		  throw e;
	  }
    //throw new UnsupportedOperationException("Not implemented");
  }

} // public class Projection extends Iterator
