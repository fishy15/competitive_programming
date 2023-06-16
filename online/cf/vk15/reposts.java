import java.util.*;
import java.io.*;

public class reposts {
	static int N;
	static int total;
	static int max;
	static Map<String, List<String>> ppl;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		sc.nextLine();
		ppl = new HashMap<>();

		String start = "";
		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(sc.nextLine());
			String second = st.nextToken().toLowerCase();

			st.nextToken(); // throwaway

			String first = st.nextToken().toLowerCase();

			if (i == 0) {
				start = first;
			}
		
			if (ppl.get(first) == null) {
				ppl.put(first, new ArrayList<>());
			}

			//System.out.printf("%d: %s %s\n", i, first, second);
			ppl.get(first).add(second);
		}

		//System.out.printf("first: %s\n", start);
		dfs(start);

		System.out.println(max);
	}

	public static void dfs(String start) {
		//System.out.println(start);
		total++;
		
		List<String> list = ppl.get(start);

		if (list == null || list.isEmpty()) {
			if (total > max) {
				max = total;
			}
		} else {
			for (int i = 0; i < list.size(); i++) {
				dfs(list.get(i));
			}
		} 

		total--;
	}
}


