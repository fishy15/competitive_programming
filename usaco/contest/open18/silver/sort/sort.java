import java.util.*;
import java.io.*;

public class sort {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("sort.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
		
		int n = Integer.parseInt(in.readLine());
		int maxSwitch = 0;
		int[] cows = new int[n];
		int[] cowsSort = new int[n];
		
		for (int i = 0; i < n; i++) {
			int j = Integer.parseInt(in.readLine());
			cows[i] = j;
			cowsSort[i] = j;
		}
	
		Arrays.sort(cowsSort);
		
		int mult = 0;
		
		for (int i = 0; i < n; i++) {
			
			if (i > 1 && cowsSort[i] == cowsSort[i - 1]) {
				mult++;
			} else {
				mult = 0;
			}
			
			maxSwitch = Math.max(findPos(cows, cowsSort[i], mult) - i, maxSwitch);
		}
		
		out.println(maxSwitch + 1);
		out.close();
	}
	
	public static int findPos(int[] array, int toFind, int mult) {
		for (int i = 0; i < array.length; i++) {
			if (array[i] == toFind) {
				return (i + mult);
			}
		}
		
		return -1;
	}
}
