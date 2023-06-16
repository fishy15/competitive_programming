import java.util.*;
import java.io.*;

public class Rental {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("rental.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rental.out"))); 

        StringTokenizer st = new StringTokenizer(in.readLine()); 
        int n, m, p;
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        p = Integer.parseInt(st.nextToken()); 
        long cents = 0; 

        int[] cows = new int[n];

        for (int i = 0; i < n; i++) {
            cows[i] = Integer.parseInt(in.readLine());
        }

        int size = 0; 
        int[] numAt = new int[m];
        int[] numSell = new int[m]; 

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(in.readLine());
            int f = Integer.parseInt(st.nextToken());
            size += f;
            int g = Integer.parseInt(st.nextToken());
            numSell[i] = g;
            numAt[i] = f; 
        }

        int[] sell = new int[size];
        int pos = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < numAt[i]; j++) {
                sell[pos] = numSell[i];
            }
        }


        Arrays.sort(cows); 
        Arrays.sort(sell);

        for (int i : sell) System.out.println(i);
    }
}