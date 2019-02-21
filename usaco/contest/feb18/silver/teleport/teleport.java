import java.util.*;
import java.io.*;

public class teleport {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("teleport.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new PrintWriter("teleport.out")));
		int n = Integer.parseInt(in.readLine());
		Map<Integer, Integer> pp = new HashMap<>();
		Map<Integer, Integer> mp = new HashMap<>();
		Map<Integer, Integer> pm = new HashMap<>();
		Map<Integer, Integer> mm = new HashMap<>();
		Map<Integer, Integer> zero = new HashMap<>();

		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			if (a == 0) {
				zero.put(a, b);
			} else if (a > 0) {
				if (b > 0) {
					pp.put(a, b);
				} else {
					pm.put(a, b);
				}
			} else {
				if (b > 0) {
					mp.put(a, b);
				} else {
					mm.put(a, b);
				}
			}
		}

		long d = 0;

System.out.println(d);

		int pmSum = 0;
		for (Map.Entry mentry : pm.entrySet()) {
			pmSum += Math.abs((int)mentry.getKey() - (int)mentry.getValue());
		}

		int mpSum = 0;
		for (Map.Entry mentry : mp.entrySet()) {
			mpSum += Math.abs((int)mentry.getKey() - (int)mentry.getValue());
		}

		// plus-minus has a larger sum
		if (pmSum > mpSum) {
			d += mpSum;
			for (Map.Entry mentry : mm.entrySet()) {
				d += Math.abs((int)mentry.getKey() - (int)mentry.getValue());
			}
			int[] vals = new int[pm.size()];
			int i = 0;
			for (Map.Entry mentry : pm.entrySet()) {
				d += Math.abs((int)mentry.getKey());
				vals[i] = (int)mentry.getValue();
				i++;
			}

			int y = findMedian(vals);
//System.out.println(y);
			for (Map.Entry mentry : pm.entrySet()) {
				d += Math.abs((int)mentry.getValue() - y);
			}
			for (Map.Entry mentry : pp.entrySet()) {
				int w = 0;
				w += Math.abs((int)mentry.getKey());
				w += Math.abs((int)mentry.getValue() - y);
				d += Math.min(w, Math.abs((int)mentry.getKey() - (int)mentry.getValue()));
			}
		} else {
			d += pmSum;
			for (Map.Entry mentry : pp.entrySet()) {
				d += Math.abs((int)mentry.getKey() - (int)mentry.getValue());
			}
			int[] vals = new int[mp.size() + mm.size()];
			int i = 0;
			for (Map.Entry mentry : mp.entrySet()) {
				d += Math.abs((int)mentry.getKey());
				vals[i] = (int)mentry.getValue();
				i++;
			}
			int y = findMedian(vals);
//System.out.println(y);
			for (Map.Entry mentry : mp.entrySet()) {
				d += Math.abs((int)mentry.getValue() - y);
			}
			for (Map.Entry mentry : mm.entrySet()) {
				int w = 0;
				w += Math.abs((int)mentry.getKey());
				w += Math.abs((int)mentry.getValue() - y);
				d += Math.min(w, Math.abs((int)mentry.getKey() - (int)mentry.getValue()));
			}
		}

		out.println(d);
		out.close();
	}

	public static int findMedian(int[] vals) {
		Arrays.sort(vals);
		int len = vals.length;
		if (len % 2 == 0) {
			return (vals[len/2 - 1] + vals[len/2]) / 2;
		}
		return vals[len/2];
	}
}