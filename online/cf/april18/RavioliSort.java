import java.util.*;

public class RavioliSort {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int x = sc.nextInt();
        boolean k = false;
        for (int i = 1; i < n; i++) {
            int y = sc.nextInt();
            if (Math.abs(x - y) > 1) {
				k = true; 
				break;
            }
            x = y;
        }
        
        if (k) {
			System.out.println("NO");
		} else {
			System.out.println("YES");
		}
    }
}
