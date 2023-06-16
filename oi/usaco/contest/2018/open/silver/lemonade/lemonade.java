import java.util.*;n
import java.io.*;

public class lemonade {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("lemonade.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lemonade.out")));
		
		int n = Integer.parseInt(in.readLine());
		StringTokenizer st = new StringTokenizer(in.readLine());
		
		int[] cows = new int[n];
		for (int i = 0; i < n; i++) {
			cows[i] = Integer.parseInt(st.nextToken());
		}
		
		Arrays.sort(cows);
		
		int i;
		for (i = 0; i < n; i++) {
			//System.out.printf("%d %d\n", cows[n-i-1], i);
			if (cows[n - i - 1] < i) {
				//System.out.println("break");
				break;
			}
		}
		
		out.println(i);
		out.close();
	}
}
