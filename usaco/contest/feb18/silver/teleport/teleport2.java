import java.util.*;
import java.io.*;

public class teleport2 {
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
		
		long pSum = 0, mSum = 0;
		for (Map.Entry mentry : pm.entrySet()) {
			mSum += Math.abs((int)mentry.getValue() - (int)mentry.getKey()); 
		}
		for (Map.Entry mentry : pp.entrySet()) {
			pSum += Math.abs((int)mentry.getValue() - (int)mentry.getKey());
		}
		for (Map.Entry mentry : mp.entrySet()) {
			pSum += Math.abs((int)mentry.getValue() - (int)mentry.getKey());
		}
		for (Map.Entry mentry : mm.entrySet()) {
			mSum += Math.abs((int)mentry.getValue() - (int)mentry.getKey());
		}
//System.out.println(mSum);
//System.out.println(pSum);

		if (pSum > mSum) {
//System.out.println(mSum);
			d += sumVals(mp, pp, mSum, true);
		} else {
			d += sumVals(pm, mm, pSum, true);
		}

		out.println(d);
		out.close();
	}
		
	public static int findMedian(Integer[] vals, int size) {
		
		Arrays.sort(vals);
		int len = vals.length;
		if (len % 2 == 0) {
			return (vals[len/2 - 1] + vals[len/2]) / 2;
		}
		return vals[len/2];
	}

	public static long sumVals(Map<Integer, Integer> a, Map<Integer, Integer> b, long sum, boolean fg) {
		long d = 0;
		List<Integer> list = new ArrayList<>();
		for (Map.Entry mentry : a.entrySet()) {
			list.add((int)mentry.getValue());
		}
		for (Map.Entry mentry : b.entrySet()) {
			list.add((int)mentry.getValue());
		}
		Integer[] vals = new Integer[b.size() + a.size()];
		vals = list.toArray(vals);
		int y = findMedian(vals, list.size());

		for (Map.Entry mentry : b.entrySet()) {
			long w = 0;
			w += Math.abs((int)mentry.getKey());
			w += Math.abs((int)mentry.getValue() - y);
			if (w >= Math.abs((int)mentry.getKey() - (int)mentry.getValue())) {
				d += Math.abs((int)mentry.getKey() - (int)mentry.getValue());
				Map <Integer, Integer> b2 = new HashMap<>(b);
				b2.remove((int)mentry.getKey());
				d += sumVals(a, b2, sum, false);
			} else {
				d += w; 
			}
			//d += Math.min(w, Math.abs((int)mentry.getKey() - (int)mentry.getValue()));
		}
		if (fg) {
			for (Map.Entry mentry : a.entrySet()) {
				d += Math.abs((int)mentry.getKey());
				d += Math.abs((int)mentry.getValue() - y);
			}
			d += sum;
		}
		return d;
	}
}