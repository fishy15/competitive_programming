import java.util.*;

public class CheeseBoard {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int hard = 0;
		int soft = 0;
		
		for (int i = 0; i < n; i++) {
			sc.next();
			String line = sc.next();
			if (line.equals("hard")) {
				hard++;
			} else {
				soft++;
			}
		}
		
		System.out.println(Math.max(hardCalc(hard), softCalc(soft)));
	}
	
	public static int hardCalc(int hard) {
		int mod = hard % 3; 
		int res = hard / 3 * 2;
		if (mod == 1) res += 1;
		else if (mod == 2) res += 2;
		return res;
	}
	
	public static int softCalc(int soft) {
		int mod = soft % 3; 
		int res = soft / 3 * 2;
		if (mod == 1) res += 1;
		else if (mod == 2) res += 1;
		return res;		
	}
}
