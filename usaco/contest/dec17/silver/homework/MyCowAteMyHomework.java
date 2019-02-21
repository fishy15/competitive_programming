import java.util.*;
import java.io.*;

public class MyCowAteMyHomework {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("homework.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("homework.out")));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer st = new StringTokenizer(in.readLine());
        int[] grades = new int[n];

        for(int i = 0; i < n; i++) {
            grades[i] = Integer.parseInt(st.nextToken());
        }

        String ans = "";
        long pts = 0;
        int minPts = grades[n - 1]; 
        double ave = (double)pts; 

        for(int k = n - 2; k > 0; k--) {
            pts += max(grades[k], minPts); 
            minPts = min(grades[k], minPts);
            double tempAve = (double)pts/(n - k - 1);
            //System.out.println(pts);
            //System.out.println(minPts);
            //System.out.println(tempAve);
            if (tempAve > ave) {
                ans = (k) + "";
                ave = tempAve;
            } else if (tempAve == ave) {
                ans = (k) + "\n" + ans;
            }
            //System.out.println();
        }

        out.println(ans);
        out.close();
    }

    public static int min(int a, int b) {
        if (a > b) {
            return b; 
        }
        return a; 
    }

    public static int max(int a, int b) {
        if (a > b) {
            return a; 
        }
        return b; 
    }
}