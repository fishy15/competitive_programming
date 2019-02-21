import java.util.*; 
import java.io.*; 

public class DiamondCollector {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("diamond.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("diamond.out")));
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        int[] d = new int[n];
        for(int i = 0; i < n; i++) {
            d[i] = Integer.parseInt(in.readLine());
        }
        Arrays.sort(d);
        int max = 0; 
        for(int i = 0; i < n; i++) {
            int count = 0;
            if (i > 0 && d[i] == d[i - 1])
                continue; 
            for (int j = i; j < n; j++) {
                if (d[j] <= d[i] + k) {
                    count++; 
                }
            }
            if (count > max) {
                max = count; 
            }
        }
        out.println(max);
        out.close();
    }   
}