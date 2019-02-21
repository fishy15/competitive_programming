import java.util.*;
import java.io.*;

public class FafaAndHisCompany {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); 
        int count = 0;
        for (int i = 1; i <= n/2; i++) {
            if ((n - i) % i == 0)
                count++;
        }
        System.out.println(count);
    }
}
