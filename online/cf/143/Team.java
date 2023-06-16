import java.util.*; 

public class Team {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); 
        int counter = 0; 
        int a, b, c;
        for(int i = 0; i < n; i++) {
			a = sc.nextInt(); 
			b = sc.nextInt(); 
			c = sc.nextInt(); 
			if (a + b + c > 1) {
				counter++; 
			}
            //System.out.println(i);
        }
        
        System.out.println(counter);
    }
}
