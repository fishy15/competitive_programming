import java.util.*;
import java.io.*;

public class reststops {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("reststops.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("reststops.out")));

		StringTokenizer st = new StringTokenizer(in.readLine());
		int L = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		int rf = Integer.parseInt(st.nextToken());
		int rb = Integer.parseInt(st.nextToken());
		
		int[][] stops = new int[n][2];
		for (int i = 0; i < n; i++) {
			st = new StringTokenizer(in.readLine());
			stops[i][0] = Integer.parseInt(st.nextToken());
			stops[i][1] = Integer.parseInt(st.nextToken());
		}

		int curLoc = 0;
		long taste = 0;
		int speedDif = rf - rb; 
		while (curLoc < L) {
//System.out.println(curLoc);
			int maxI = findMax(stops, curLoc); 
			if (maxI == -1) break;
			int maxLoc = stops[maxI][0];
			int maxNum = stops[maxI][1];
			taste += (maxLoc - curLoc) * (long)maxNum; 
//System.out.printf("%d %d %d\n", maxLoc, maxNum, (maxLoc - curLoc) * maxNum);
			curLoc = maxLoc; 
		}

		out.println(taste * speedDif);
		out.close();
	}

	public static int findMax(int[][] stops, int curLoc) {
		int maxI = -1;
		int max = 0;
		for (int i = 0; i < stops.length; i++) {
			if (stops[i][0] <= curLoc) {
//System.out.println("skipping this");
				continue;
			}
			else if (max <= stops[i][1]) {
				max = stops[i][1];
				maxI = i; 
			}
		}
//System.out.
		return maxI;
	}

	
}