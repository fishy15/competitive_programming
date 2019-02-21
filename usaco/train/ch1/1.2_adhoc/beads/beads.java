/*
ID: aaryan.1
TASK: beads
LANG: JAVA
*/

import java.util.*;
import java.io.*;

public class beads {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("beads.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("beads.out")));

		int n = Integer.parseInt(in.readLine());
		String neck = in.readLine();
		neck += neck;
		String necklace = "";
		int count = 0;
		
		for (int i = 0; i < 2 * n; i++) {
			count++;
			if (i != 2 * n - 1) { 
				if (neck.charAt(i) != neck.charAt(i + 1)) {
					necklace += neck.charAt(i);
					necklace += count;
					count = 0;
				}
			} else {
				necklace += neck.charAt(i);
				necklace += count;
			}
		}
		
		int m = necklace.length() / 2; 
		// 2i = color, 2i+1 = # 
		int maxCount = 0; 
		int maxPos = -1;
		 
		count = 0;
		for (int i = 1; i < m; i++) {
			count = 0;
			int type = 0; // r = -1, b = 1
			for (int j = i - 1; j > 0; j--) {
				if (type == 0) {
					if (necklace.charAt(2*j) == 'r') {
						type = -1;
					} else if (necklace.charAt(2*j) == 'b') {
						type = 1;
					}
				} else if (type == -1) {
					if (necklace.charAt(2*j) == 'b') {
						break;
					}					
				} else if (type == 1) {
					if (necklace.charAt(2*j) == 'r') {
						break;
					}
				}
				
				count += necklace.charAt(2*j+1) - '0';
			}
			
			type = 0;
			
			for (int j = i; j < m; j++) {
				if (type == 0) {
					if (necklace.charAt(2*j) == 'r') {
						type = -1;
					} else if (necklace.charAt(2*j) == 'b') {
						type = 1;
					}
				} else if (type == -1) {
					if (necklace.charAt(2*j) == 'b') {
						break;
					}					
				} else if (type == 1) {
					if (necklace.charAt(2*j) == 'r') {
						break;
					}
				}
				
				count += necklace.charAt(2*j+1) - '0'; 
			}
			
			System.out.println(count);
			if (count > maxCount) {
				maxCount = count; 
			}
		}
		
		//System.out.println(necklace);
		
		if (necklace.length() == 2) {
			out.println((necklace.charAt(1) - '0') / 2);
		} else {
			out.println(maxCount);
		}
		out.close();
	}
}
