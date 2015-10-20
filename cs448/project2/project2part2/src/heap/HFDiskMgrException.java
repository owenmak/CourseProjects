package heap;

import chainexception.*;

public class HFDiskMgrException extends ChainException {
  
  public HFDiskMgrException(Exception e, String name)
    {
      super(e, name); 
    }
}

