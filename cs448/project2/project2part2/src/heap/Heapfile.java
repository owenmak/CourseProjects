package heap;

//import global.RID;

import diskmgr.*;
import bufmgr.*;
import global.*;

import java.io.* ;
import java.util.* ;


public class Heapfile implements GlobalConst {

	// store pages 
	protected PageId start_id;
	public Heapfile(String string) throws HFException, HFBufMgrException, HFDiskMgrException, IOException, Exception {
		if( string == null ) string = "temp_file";
		if( (start_id = SystemDefs.JavabaseDB.get_file_entry(string)) == null ){
			Page start_page = new Page();
			start_id = SystemDefs.JavabaseBM.newPage(start_page, 1);
			HFPage start_hf_page = new HFPage();
			start_hf_page.init(start_id, start_page);
			start_hf_page.setPrevPage(new PageId(-1));
			start_hf_page.setNextPage(new PageId(-1));
			SystemDefs.JavabaseBM.unpinPage(start_id, true);
			
			
			SystemDefs.JavabaseDB.add_file_entry(string, start_id);	
			
		}
	}

	public RID insertRecord(byte[] byteArray) throws InvalidUpdateException,InvalidSlotNumberException, InvalidTupleSizeException, SpaceNotAvailableException, HFDiskMgrException, HFBufMgrException, HFException, Exception {
		if( byteArray.length > HFPage.MAX_SPACE){
			throw new SpaceNotAvailableException(new Exception(), "Not Enough Space InsertRecord");
		}
		PageId cur_page_id = new PageId();
		PageId next_page_id = new PageId();
		cur_page_id.copyPageId(start_id);
		
		RID rid;
		Page cur_page = new Page();
		
		HFPage next_hf_page;
		HFPage cur_hf_page;
		
		SystemDefs.JavabaseBM.pinPage(cur_page_id, cur_page, false);
		cur_hf_page = new HFPage(cur_page);
		while( (rid=cur_hf_page.insertRecord(byteArray)) == null ){
			
			next_page_id = cur_hf_page.getNextPage();
			
			if( next_page_id.pid != -1 ){	
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, false);
				
				SystemDefs.JavabaseBM.pinPage(next_page_id,cur_page, false);
				cur_page_id.copyPageId(next_page_id);
				cur_hf_page = new HFPage(cur_page);
				
			}else{
				Page next_page = new Page();
				next_page_id = SystemDefs.JavabaseBM.newPage(next_page, 1);
				next_hf_page = new HFPage();
				next_hf_page.init(next_page_id, next_page);
			
				next_hf_page.setPrevPage(cur_page_id);
				next_hf_page.setNextPage(new PageId(-1));
				
				cur_hf_page.setNextPage(next_page_id);
				
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, true);
				
				cur_hf_page = next_hf_page;
				cur_page_id.copyPageId(next_page_id);
			}
			
		}
		SystemDefs.JavabaseBM.unpinPage(cur_page_id, true);
		return rid;
	}

	public int getRecCnt() throws InvalidSlotNumberException, InvalidTupleSizeException, HFDiskMgrException, HFBufMgrException, Exception{
		PageId cur_page_id = new PageId();
		cur_page_id.copyPageId(start_id);
		int count = 0;
		while( cur_page_id.pid != -1 ){
			Page page = new Page();
			SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
			HFPage hf_page = new HFPage(page);
			count += hf_page.getSlotCnt();
			cur_page_id.copyPageId(hf_page.getNextPage());
			SystemDefs.JavabaseBM.unpinPage(hf_page.getCurPage(), false);
		}
		return count;
	}

	public Scan openScan() throws InvalidUpdateException, InvalidTupleSizeException, Exception {
		Scan scan = new Scan(this);
		return scan;
	}

	public boolean deleteRecord(RID rid) throws InvalidSlotNumberException, InvalidTupleSizeException, HFDiskMgrException, HFBufMgrException,HFException, Exception  {
		PageId cur_page_id = new PageId();
		Page page;
		HFPage hfpage;
		cur_page_id.copyPageId(start_id);
		while( cur_page_id.pid != -1 && cur_page_id.pid != rid.pageNo.pid ){
			page = new Page();
			SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
			hfpage = new HFPage(page);
			cur_page_id.copyPageId(hfpage.getNextPage());
			SystemDefs.JavabaseBM.unpinPage(hfpage.getCurPage(),false);
		}
		if( cur_page_id.pid == -1 )
				return false;
		else{
			try{
				page = new Page();
				SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
				hfpage = new HFPage(page);
				hfpage.deleteRecord(rid);
				
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, true);
				return true;
			}catch( InvalidSlotNumberException e ){
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, false);
				throw e;
			}			
		}
		
	}

	public boolean updateRecord(RID rid, Tuple newTuple) throws InvalidUpdateException, InvalidSlotNumberException, InvalidTupleSizeException, HFDiskMgrException, HFBufMgrException, HFException,Exception {
		PageId cur_page_id = new PageId();
		Page page;
		HFPage hfpage;
		cur_page_id.copyPageId(start_id);
		while( cur_page_id.pid != -1 && cur_page_id.pid != rid.pageNo.pid ){
			page = new Page();
			SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
			hfpage = new HFPage(page);
			cur_page_id.copyPageId(hfpage.getNextPage());
			SystemDefs.JavabaseBM.unpinPage(hfpage.getCurPage(),false);
		}
		if( cur_page_id.pid == -1 )
				return false;
		else{
			try{
				page = new Page();
				SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
				hfpage = new HFPage(page);
				Tuple cur_tuple = hfpage.returnRecord(rid);
				if( cur_tuple == null )
					throw new InvalidSlotNumberException(new Exception(),"null cur_tuple");
				if( cur_tuple.getLength() != newTuple.getLength())
					throw new InvalidUpdateException(new Exception() ,"Update not same length");
				cur_tuple.tupleCopy(newTuple);
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, true);
				return true;
			}catch( InvalidSlotNumberException e ){
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, false);
				throw e;
			}catch( InvalidUpdateException e ){
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, false);
				throw e;
			}
		}
	}

	public Tuple getRecord(RID rid) throws InvalidUpdateException, HFException, HFBufMgrException, HFDiskMgrException, InvalidSlotNumberException, InvalidTupleSizeException, Exception{
		PageId cur_page_id = new PageId();
		Page page;
		HFPage hfpage;
		cur_page_id.copyPageId(start_id);
		while( cur_page_id.pid != -1 && cur_page_id.pid != rid.pageNo.pid ){
			page = new Page();
			SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
			hfpage = new HFPage(page);
			cur_page_id.copyPageId(hfpage.getNextPage());
			SystemDefs.JavabaseBM.unpinPage(hfpage.getCurPage(),false);
		}
		if( cur_page_id.pid == -1 )
				return null;
		else{
			try{
				page = new Page();
				SystemDefs.JavabaseBM.pinPage(cur_page_id, page, false);
				hfpage = new HFPage(page);
				Tuple cur_tuple = hfpage.getRecord(rid);
				if( cur_tuple == null )
					throw new InvalidSlotNumberException(new Exception(),"null cur_tuple");
				
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, true);
				return cur_tuple;
			}catch( InvalidSlotNumberException e ){
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, false);
				throw e;
			}
		}
	}



}
