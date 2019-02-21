import java.util.*;

public class woodcutting {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        for (int i = 0; i < t; i++) {
            int c = sc.nextInt();
            long[] custs = new long[c];

            for (int j = 0; j < c; j++) {
                long tot = sc.nextLong();
                for (int k = 0; k < tot; k++) {
                    custs[j] += sc.nextLong();
                }
            }

            Arrays.sort(custs);

            double time = 0.0;
            double total = 0.0;

            for (int j = 0; j < c; j++) {
                time += custs[j];
                total += time;
            }

            System.out.println(total / c);
        }
    }
}
