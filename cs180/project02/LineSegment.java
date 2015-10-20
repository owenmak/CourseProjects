public class LineSegment {
	private final Point start;
	private final Point end;

	public LineSegment(Point start, Point end) {
		this.start = new Point(start.getX(), start.getY());
		this.end = new Point(end.getX(), end.getY());
	}

	public double slope() {
		return Math.round((start.getY() - end.getY())
				/ (start.getX() - end.getX()) * 100.0) / 100.0;
	}

	public double yIntercept() {
		return Math.round((start.getY() - this.slope() * start.getX()) * 100.0) / 100.0;
	}

	public Point getStart() {
		return start;
	}

	public Point getEnd() {
		return end;
	}

	public double length() {
		return Math.round(Math.sqrt((end.getX() - start.getX())
				* (end.getX() - start.getX()) + (end.getY() - start.getY())
				* (end.getY() - start.getY())) * 100.0) / 100.0;
	}

	public LineSegment scaleByFactor(double scalar) {
		double newEndX = scalar * (end.getX() - start.getX()) + start.getX();
		double newEndY = scalar * (end.getY() - start.getY()) + start.getY();
		Point newEnd = new Point(newEndX, newEndY);
		LineSegment newSegment = new LineSegment(this.start, newEnd);
		return newSegment;
	}

	@Override
	public String toString() {
		return ("y = " + this.slope() + "x + " + this.yIntercept());
	}

}
