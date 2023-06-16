import java.util.*;

public class MaximumControl {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int[] planets = new int[n + 1];
		
		for (int i = 0; i < (n - 1) * 2; i++) {
			int num = sc.nextInt();
			planets[num]++;
			
			//System.out.println(choose(n, 2));
			//System.out.println(i);
		}
		
		int count = 0;
		
		for (int i = 0; i < n + 1; i++) {
			if (planets[i] == 1)
				count++;
		}
		
		System.out.println(count);
	}
	
	//~ public static int choose(int n, int k) {
		//~ return (fact(n)/fact(k))/fact(n - k);
	//~ }
	
	//~ public static int fact(int n) {
		//~ int prod = 1;
		
		//~ for (int i = 1; i <= n; i++) {
			//~ prod *= i;
		//~ }
		
		//~ return prod;
	//~ }
}
