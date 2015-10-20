package heap;

import diskmgr.*;
import bufmgr.*;
import global.*;

import java.io.* ;

public class Scan {

	Page page;
	PageId pageid;
	HFPage hfpage;
	RID rid;
	Heapfile heapfile;
	public Scan(Heapfile hf ) throws InvalidTupleSizeException, Exception {
		heapfile = hf;
		
		pageid = new PageId();
		page = new Page();
		pageid.copyPageId(hf.start_id);
		SystemDefs.JavabaseBM.pinPage(pageid, page, false);
		hfpage = new HFPage(page);
		rid = hfpage.firstRecord();
		
		
	}

	public Tuple getNext(RID killmebitch) throws InvalidTupleSizeException, Exception {
		if( hfpage == null ){ 
			return null;
		}
		while( rid == null ){
			
			PageId next_page_id = hfpage.getNextPage();
			if( next_page_id.pid == -1 ){
				SystemDefs.JavabaseBM.unpinPage(pageid, false);
				return null;
			}else{
				SystemDefs.JavabaseBM.unpinPage(pageid, false);
				SystemDefs.JavabaseBM.pinPage(next_page_id, page, false);
				pageid.copyPageId(next_page_id);
				hfpage = new HFPage(page);
				rid = hfpage.firstRecord();
			}
		}
		//System.out.println(rid.slotNo+"  --  "+rid.pageNo);System.exit(0);
		Tuple res = hfpage.getRecord(rid);
		killmebitch.copyRid(rid);
		rid = hfpage.nextRecord(rid);
		
		return res;
	}



// blank
	public void closescan(){
		try{
			SystemDefs.JavabaseBM.unpinPage(pageid, false);
			page = null;
			hfpage = null;
			pageid= null;
			rid = null;
			heapfile = null;
		}catch(Exception e){
			
		}
	}
	
// blank
	public boolean position( RID myrid ) throws InvalidTupleSizeException, IOException {
		if( heapfile == null )return false; 
		try{
			SystemDefs.JavabaseBM.unpinPage(pageid, false);
		}catch(Exception e){
			return false;	
		}
		
		
		PageId cur_page_id = new PageId();
		Page mypage;
		HFPage myhfpage;
		cur_page_id.copyPageId(heapfile.start_id);
		
		while( cur_page_id.pid != -1 && cur_page_id.pid != myrid.pageNo.pid ){
			mypage = new Page();
			try{
				SystemDefs.JavabaseBM.pinPage(cur_page_id, mypage, false);
				myhfpage = new HFPage(mypage);
				cur_page_id.copyPageId(myhfpage.getNextPage());
				SystemDefs.JavabaseBM.unpinPage(myhfpage.getCurPage(),false);
			}catch( Exception e ){
				return false;
			}
		}
		if( cur_page_id.pid == -1 ) return false;
		try{
			mypage = new Page();
			SystemDefs.JavabaseBM.pinPage(cur_page_id, mypage, false);
			myhfpage = new HFPage(mypage);
			if( myhfpage.getRecord(myrid) == null ){
				SystemDefs.JavabaseBM.unpinPage(cur_page_id, false);
				return false;
			}else{
				page = mypage;
				pageid = cur_page_id;
				hfpage = myhfpage;
				rid = myrid;
				return true;
			}
		}catch(Exception e ){
			return false;
		}
	}

	public RID returnCurRid() {
		return rid;
	} 
	
}
