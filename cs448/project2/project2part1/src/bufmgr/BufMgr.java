/* ... */

package bufmgr;

import java.io.*;
import java.util.*;
import diskmgr.*;
import global.*;

public class BufMgr implements GlobalConst{

 /*class of frame desccriptor*/
  private class fdesc { 
	PageId p;
	int pin_count;
	boolean dirtybit;	
  };

  private LinkedList<Integer> rc; 			// replacement candidate linked list.
  private byte bufpool[][];					// buffer pool
  private int buf_num;						// buffer number
  private String policy;					// replacement polciy
  private fdesc bufDescr[];					// buffer descriptor
  private Hashtable<Integer, Integer> fp; 	// <page number, frame number> hashtable.
  /**
   * Create the BufMgr object.
   * Allocate pages (frames) for the buffer pool in main memory and
   * make the buffer manage aware that the replacement policy is
   * specified by replacerArg (i.e. HL, Clock, LRU, MRU etc.).
   *
   * @param numbufs number of buffers in the buffer pool.
   * @param replacerArg name of the buffer replacement policy.
   */
  public BufMgr(int numbufs, String replacerArg) {
	buf_num = numbufs;
	bufpool = new byte[numbufs][MINIBASE_PAGESIZE];
	policy = new String(replacerArg);
	bufDescr = new fdesc[numbufs];
	rc = new LinkedList<Integer>();
	fp = new Hashtable<Integer, Integer>();
	for(int i = 0; i < numbufs; i++) {
		bufDescr[i] = new fdesc();
		bufDescr[i].pin_count = 0;	
		bufDescr[i].dirtybit = false;
		bufDescr[i].p = null;
		rc.add(i);
	}
	
  };

/*
	public void help() {
		System.out.println("Now printing what's in rc");
		for(int i = 0; i < rc.size(); i++)
			System.out.printf("%d\t", rc.get(i));
		System.out.println();
	}
*/
  /**
   * Pin a page.
   * First check if this page is already in the buffer pool.
   * If it is, increment the pin_count and return a pointer to this
   * page.  If the pin_count was 0 before the call, the page was a
   * replacement candidate, but is no longer a candidate.
   * If the page is not in the pool, choose a frame (from the
   * set of replacement candidates) to hold this page, read the
   * page (using the appropriate method from {\em diskmgr} package) and pin it.
   * Also, must write out the old page in chosen frame if it is dirty
   * before reading new page.  (You can assume that emptyPage==false for
   * this assignment.)
   *
   * @param Page_Id_in_a_DB page number in the minibase.
   * @param page the pointer point to the page.
   * @param emptyPage true (empty page); false (non-empty page)
   */
  public void pinPage(PageId pin_pgid, Page page, boolean emptyPage) throws BufferPoolExceededException, DiskMgrException {

	if(fp.containsKey(pin_pgid.pid)) {

		int bindex = fp.get(pin_pgid.pid);
			page.setpage(bufpool[bindex]);
			if(bufDescr[bindex].pin_count == 0){ 			// remove from replacement candidate ll.
				rc.remove(new Integer(bindex));	
			}
			else {
				if(bufDescr[bindex].dirtybit) {
					try {
						flushPage(bufDescr[bindex].p);
					} catch (Exception e) {	
						throw new DiskMgrException(e, "FLUSH_PAGE_EXCEPTION.");
					}
				}
			}
			bufDescr[bindex].dirtybit = false;
			bufDescr[bindex].pin_count++;
			return;
		}
		else {
			if(rc.isEmpty()) {
				throw new BufferPoolExceededException( new Exception(), "BUFFER_POOL_EXCEEDED_EXCEPTION.");

			}
			else {
				int rcindex = rc.remove();					// choose replacement index
				if( bufDescr[rcindex].dirtybit) {
					try {
						flushPage(bufDescr[rcindex].p); 	// flush the old page.
					} catch (Exception e) {
						throw new DiskMgrException(e, "FLUSH_PAGE_EXCEPTION.");
					}
				}
				page.setpage(bufpool[rcindex]);
				try {
					SystemDefs.JavabaseDB.read_page(pin_pgid, page);
				} catch(Exception e) {
					throw new DiskMgrException(e, "READ_PAGE_EXCEPTION.");
				}
				bufDescr[rcindex].dirtybit = false; 		// set dirtybit to false.
				bufDescr[rcindex].pin_count = 0;			// set pin count to 0.
				bufDescr[rcindex].pin_count++; 				// increment the pin_count.
				if(bufDescr[rcindex].p != null)
					fp.remove(new Integer(bufDescr[rcindex].p.pid));	//remove old entry.
				else
					bufDescr[rcindex].p = new PageId();		// first time
				bufDescr[rcindex].p.copyPageId(pin_pgid); 	// copy the new pageId to buffer descriptor.
				fp.put(pin_pgid.pid, rcindex);				// insert the new entry.
			}
		}

  };

  /**
   * Unpin a page specified by a pageId.
   * This method should be called with dirty==true if the client has
   * modified the page.  If so, this call should set the dirty bit
   * for this frame.  Further, if pin_count&gt;0, this method should
   * decrement it. If pin_count=0 before this call, throw an exception
   * to report error.  (For testing purposes, we ask you to throw
   * an exception named PageUnpinnedException in case of error.)
   *
   * @param globalPageId_in_a_DB page number in the minibase.
   * @param dirty the dirty bit of the frame
   */
  public void unpinPage(PageId PageId_in_a_DB, boolean dirty) throws HashEntryNotFoundException, PageUnpinnedException {
	if(!fp.containsKey(PageId_in_a_DB.pid))	{
		throw new HashEntryNotFoundException (new Exception(), "HASH_ENTRY_NOT_FOUND_EXCEPTION.");
	}
	int bindex = fp.get(new Integer(PageId_in_a_DB.pid));
	if(dirty == true)
		bufDescr[bindex].dirtybit = true;
	if(bufDescr[bindex].pin_count <= 0)
		throw new PageUnpinnedException (new Exception(), "PAGE_UNPINNED_EXCEPTION.");
	else {
		if(--bufDescr[bindex].pin_count == 0) {
			rc.add(bindex);
		}
	}
  };


  /**
   * Allocate new pages.
   * Call DB object to allocate a run of new pages and
   * to allocate pages on disk.) If buffer is full, i.e., you
   * can't find a frame for the first page, ask DB to deallocate
   * all these pages, and return null.
   *
   * @param firstpage the address of the first page.
   * @param howmany total number of allocated new pages.
   *
   * @return the first page id of the new pages.  null, if error.
   */
  public PageId newPage(Page firstpage, int howmany) throws DiskMgrException {
	PageId p = new PageId();
	try {
		SystemDefs.JavabaseDB.allocate_page(p, howmany);
	} catch(Exception e) {
		throw new DiskMgrException(e, "NEW_PAGE_FAIL");
	}
	try {
		pinPage(p, firstpage, false);
	} catch (Exception e) {
		throw new DiskMgrException(e, "PIN_PAGE_FAIL.");
	}
	return p;

  };


  /**
   * This method should be called to delete a page that is on disk.
   * This routine must call the method in diskmgr package to
   * deallocate the page.
   *
   * @param globalPageId the page number in the data base.
   */
  public void freePage(PageId globalPageId) throws HashEntryNotFoundException, DiskMgrException, PagePinnedException, PageUnpinnedException {
	if(fp.containsKey(globalPageId.pid)) {
		int bindex = fp.get(globalPageId.pid);
		if(bufDescr[bindex].pin_count > 1)
			throw new PagePinnedException(new Exception(), "PAGE_PINNED_FAIL");
		else if(bufDescr[bindex].pin_count == 1)
		{
			unpinPage(globalPageId, false);
		}
		fp.remove(globalPageId.pid);
		bufDescr[bindex].pin_count = 0;
		bufDescr[bindex].dirtybit = false;
		bufDescr[bindex].p = null;
	}
	try {
		SystemDefs.JavabaseDB.deallocate_page(globalPageId);
	} catch (Exception e) {
		e.printStackTrace();
		throw new DiskMgrException(e, "FREE_PAGE_FAIL");
	}
  };


  /**
   * Used to flush a particular page of the buffer pool to disk.
   * This method calls the write_page method of the diskmgr package.
   *
   * @param pageid the page number in the database.
   */
  public void flushPage(PageId pageid) throws HashEntryNotFoundException, DiskMgrException {
  if(pageid == null)
  	return;
//	System.out.printf("tyring to flush page:%d\n", pageid.pid);

	if(!fp.containsKey(pageid.pid))	{
		throw new HashEntryNotFoundException(null, "HASH_ENTRY_NOT_FOUND_EXCEPTION.");
	}
	int bindex = fp.get(pageid.pid);
	Page page = new Page();
	page.setpage(bufpool[bindex]);
	try {
		SystemDefs.JavabaseDB.write_page(pageid, page);
	} catch (Exception e) {
		throw new DiskMgrException(e, "FLUSH_PAGE_FAIL.");
	}
  };

  
  /** Flushes all pages of the buffer pool to disk
   */
  public void flushAllPages() throws DiskMgrException {
	Set set = fp.entrySet();
	Iterator it = set.iterator();
	while(it.hasNext()) {
		Map.Entry entry = (Map.Entry) it.next();
			int bindex = (int)entry.getValue();
			try {
				flushPage(bufDescr[bindex].p);
			} catch(Exception e) {
				throw new DiskMgrException(e, "FLUSH_PAGE_EXCEPTION.");
			}
	}
  };


  /** Gets the total number of buffers.
   *
   * @return total number of buffer frames.
   */
  public int getNumBuffers() {
	return buf_num;
  };


  /** Gets the total number of unpinned buffer frames.
   *
   * @return total number of unpinned buffer frames.
   */
  public int getNumUnpinnedBuffers() {
	return rc.size();
  };

}

