import java.util.*;
import java.io.*;

public class FafaAndTheGates {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		String c = sc.next();
		int uc = 0, rc = 0;
		int count = 0;
		for (int i = 0; i < n - 1; i++) {
			boolean uCheck = false, rCheck = false;
			if (uc - rc == 1) uCheck = true;
			else if (rc - uc == 1) rCheck = true;

			if (c.charAt(i) == 'U') uc++;
			else rc++;
			

			if (uCheck && uc == rc) {
				i++;
				if (c.charAt(i) == 'R') count++;
				i--;
			}
			else if (rCheck && uc == rc) {
				i++;
				if (c.charAt(i) == 'U') count++;
				i--;
			}
		}

		System.out.println(count);
	}
}
