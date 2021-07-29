import java.util.*;
import java.io.*;

public class CloningToys {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x, y;
        x = sc.nextInt();
        y = sc.nextInt(); 
        int c = 0;
        c += y - 1;
        if (c % 2 == x % 2 && c <= x)
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}
