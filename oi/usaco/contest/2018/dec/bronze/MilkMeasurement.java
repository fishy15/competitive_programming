import java.util.*;
import java.io.*;

public class MilkMeasurement {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("measurement.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("measurement.out")));
        int n = Integer.parseInt(in.readLine());
        int[] bDays = new int[100];
        int[] eDays = new int[100];
        int[] mDays = new int[100];

        int[] cows = {7, 7, 7}; // B, E, M
        boolean[] most = {true, true, true};

        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int day = Integer.parseInt(st.nextToken()); 
            char cow = st.nextToken().charAt(0);
            int change = Integer.parseInt(st.nextToken());

            if (cow == 'B') {
                bDays[day - 1] = change; 
            }

            if (cow == 'E') {
                eDays[day - 1] = change; 
            }

            if (cow == 'M') {
                mDays[day - 1] = change; 
            }
        }

        int count = 0; 

        for (int i = 0; i < 100; i++) {
            if (bDays[i] != 0) {
                cows[0] += bDays[i];
                boolean[] temp = winner(cows);
                if (unequal(most, temp)) {
System.out.println("change");
                    count++;
                    most = temp; 
                }
            }
            if (eDays[i] != 0) {
                cows[1] += eDays[i];
                boolean[] temp = winner(cows);
                if (unequal(most, temp)) {
System.out.println("change");
                    count++;
                    most = temp; 
                }
            }
            if (mDays[i] != 0) {
                cows[2] += mDays[i];
                boolean[] temp = winner(cows);
                if (unequal(most, temp)) {
System.out.println("change");
                    count++;
                    most = temp; 
                }
            }
        }

        out.println(count);
        out.close();
    }

    public static boolean[] winner(int[] cows) {
        if (cows[0] > cows[1] && cows[0] > cows[2]) {
            boolean[] ans =  {true, false, false};
            return ans; 
        }

        if (cows[1] > cows[0] && cows[1] > cows[2]) {
            boolean[] ans = {false, true, false};
            return ans; 
        }

        if (cows[2] > cows[1] && cows[2] > cows[0]) {
            boolean[] ans = {false, false, true};
            return ans;
        }

        if (cows[0] == cows[1] && cows[0] > cows[2]) {
            boolean[] ans = {true, true, false};
            return ans;
        }

        if (cows[0] == cows[2] && cows[0] > cows[1]) {
            boolean[] ans = {true, false, true};
            return ans;
        }

        if (cows[1] == cows[2] && cows[1] > cows[0]) {
            boolean[] ans = {false, true, true};
            return ans;
        }
        
        boolean[] ans = {true, true, true};
        return ans;
    }

    public static boolean unequal(boolean[] x, boolean[] y) {
        for (int i = 0; i < x.length; i++) {
            if (x[i] != y[i]) {
                return true;
            }
        }

        return false;
    }
}