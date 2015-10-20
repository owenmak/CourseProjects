package heap;

import chainexception.*;

public class SpaceNotAvailableException extends ChainException {
  
  public SpaceNotAvailableException(Exception e, String name)
    {
      super(e, name); 
    }
}
