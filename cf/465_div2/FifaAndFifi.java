import java.util.*;
import java.io.*;

public class FifaAndFifi {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int R = sc.nextInt();
		int x1 = sc.nextInt();
		int y1 = sc.nextInt();
		int x2 = sc.nextInt();
		int y2 = sc.nextInt();
		x2 = x2 - x1;
		y2 = y2 - y1;
//System.out.printf("%d %d\n", x2, y2);
		if (Math.sqrt(x2*x2 + y2*y2) >= R) {
			System.out.printf("%f %f %f\n", (double)x1, (double)y1, (double)R);
		} else if (x2 == 0 && y2 == 0) {
			System.out.printf("%f %f %f\n", x1 + (double)R / 2, (double)y1, (double)R/2); 
		} else {
			int sx = -1, sy = -1;
			if (x2 > 0) sx = 1;
			if (y2 > 0) sy = 1;
			double theta = Math.atan((double)y2/x2);
			double x3 = R*Math.cos(theta);
			double y3 = R*Math.sin(theta);
			x3 *= -sx;
			y3 *= -sx;
			double xm = (x2 + x3) / 2.0;
			double ym = (y2 + y3) / 2.0;
			double r = Math.sqrt((x3-xm)*(x3-xm) + (y3-ym)*(y3-ym)); 
			System.out.printf("%f %f %f\n", xm + x1, ym + y1, r);
		}
	}
}
