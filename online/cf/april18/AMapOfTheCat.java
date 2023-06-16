import java.util.*;

public class AMapOfTheCat {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int noCount = 0;
        
        for (int i = 0; i < 10; i++) {
            System.out.println(i);
            String j = sc.next();
            if (j.startsWith("great")) noCount++;
        }
        
        if (noCount == 1) {
            System.out.println("");
        }
        else {
            System.out.println("");
        }
    }
}
