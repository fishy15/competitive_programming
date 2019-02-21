import java.util.*;
import java.math.*;

public class NastyaWardrobe {
	final static int MOD = 1000000007;

	public static void main(String[] args) {
		int x, k;
		Scanner sc = new Scanner(System.in);
		BigInteger ans = new BigInteger("0");
		x = sc.nextInt();
		k = sc.nextInt();
		ans = new BigInteger((2 * x - 1) + "");
		ans = ans.shiftLeft(k);
		ans = ans.add(BigInteger.ONE);
		ans = ans.mod(new BigInteger(MOD + ""));
		System.out.println(ans.intValue());
	}
}
