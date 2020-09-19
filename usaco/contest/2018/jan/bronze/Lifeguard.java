import java.util.*;
import java.io.*;

public class Lifeguard {
    public static void main (String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("lifeguard.in"));
        int n = Integer.parseInt(in.readLine()); 
        int[] lower = new int[n]; // lower bounds
        int[] upper = new int[n]; // upper bounds
        int max = Lifeguard.max(upper); 
        int[] numCov = new int[n]; 
        int[] covered = new int[n + 1];  // how many times has been covered 

        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            lower[i] = Integer.parseInt(st.nextToken()); 
            upper[i] = Integer.parseInt(st.nextToken()); 

            for (int j = lower[i]; j < upper[i]; j++) {
                covered[j]++;
            } 
        }


        for (int i = 0; i < n; i++) {
            //for (int j = 0; j < 
        }

        System.out.println(max);
    }

    public static int max(int[] array) {
        int max = -1; 
        for (int i = 0; i < array.length; i++) {
            max = Math.max(max, array[i]); 
        }

        return max;
    }

    public static int min(int[] array) {
        int min = Math.min(array[0], array[1]);
        for (int i = 1; i < array.length; i++) {
            min = Math.min(min, array[i]);
        }

        return min;
    }
}