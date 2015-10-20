package heap;

import chainexception.*;

public class FileAlreadyDeletedException extends ChainException {
  
  public FileAlreadyDeletedException(Exception e, String name)
    {
      super(e, name); 
    }
}
