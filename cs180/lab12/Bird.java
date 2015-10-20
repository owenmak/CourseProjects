public class Bird extends Animal {

	public Bird(String status) {
		super(status);
	}

	@Override public void makeMove(SiteGrid sg) {
		try {
			if(status == "ALIVE") {
				if(this.getSite().getType() == SiteType.WINTERING) {
	        		this.die();
				}
				else
					super.makeMove(sg);
			}
		} catch (NullPointerException e) {
			super.makeMove(sg);
		}
	}
}
