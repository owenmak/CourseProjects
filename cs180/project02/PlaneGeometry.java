import java.util.Scanner;

public class PlaneGeometry {
	public static void main(String[] args) {
		double x1, x2, y1, y2, scalar;
		Scanner s = new Scanner(System.in);
		System.out.println("Please enter the value for coordinate X1:\n");
		x1 = s.nextDouble();
		System.out.println("Please enter the value for coordinate Y1:\n");
		y1 = s.nextDouble();
		System.out.println("Please enter the value for coordinate X2:\n");
		x2 = s.nextDouble();
		System.out.println("Please enter the value for coordinate Y2:\n");
		y2 = s.nextDouble();
		System.out.println("Please enter the value for the scalar:\n");
		scalar = s.nextDouble();
		Point start = new Point(x1, y1);
		Point end = new Point(x2, y2);
		LineSegment ls = new LineSegment(start, end);
		System.out.printf("Slope: %.2f\n", ls.slope());
		System.out.printf("Length: %.2f\n", ls.length());
		System.out.printf("Y-Intercept: %.2f\n", ls.yIntercept());
		System.out.printf("Equation: " + ls.toString() + "\n");
		System.out.printf("Length After Scaling: %.2f\n", ls.scaleByFactor(scalar).length());
		System.out.printf("End Point After Scaling: (%.2f, %.2f)\n", (ls.scaleByFactor(scalar).getEnd()).getX(),(ls.scaleByFactor(scalar).getEnd()).getY());
	}
}
