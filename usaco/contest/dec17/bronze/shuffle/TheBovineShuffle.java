import java.util.*;
import java.io.*; 

public class TheBovineShuffle {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("shuffle.in")); 
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shuffle.out")));
        int n = Integer.parseInt(in.readLine()); 
        StringTokenizer st1 = new StringTokenizer(in.readLine()); 
        StringTokenizer st2 = new StringTokenizer(in.readLine()); 
        int[] shuffle = new int[n + 1];
        int[] id = new int[n + 1]; 

        for(int i = 0; i < n; i++) {
            shuffle[i + 1] = Integer.parseInt(st1.nextToken()); 
        }

        for(int i = 0; i < n; i++) {
            id[i + 1] = Integer.parseInt(st2.nextToken()); 
        }
        
        int[] cur = new int[n + 1]; 
        for(int i = 1; i < n + 1; i++) {
            cur[i] = i; 
        }

        for(int i = 0; i < 3; i++) {
            int[] temp = new int[n + 1]; 
            for(int j = 1; j < n + 1; j++) {
                temp[j] = cur[shuffle[j]];
            }
            cur = temp; 
        }

        for(int i = 1; i < n + 1; i++) {
            out.println(id[cur[i]]);
        }
        out.close();
    }
}