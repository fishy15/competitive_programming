import java.io.*;
import java.math.*;
import java.util.*;

public class ProductEquality {
    public static final double eps = 1e-8;

    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);

        int n = io.getInt();

        BigInteger[] nums = new BigInteger[n];
        double[] logs = new double[n];

        for (int i = 0; i < n; i++) {
            String word = io.getWord();
            nums[i] = new BigInteger(word);

            logs[i] = BigMath.logBigInteger(nums[i]);
        }

        Arrays.sort(nums);
        for (int i = 0; i < n; i++) {
        }

        TreeMap<Double, HashMap<BigInteger, Integer>> seen = new TreeMap<>();
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            logs[i] = BigMath.logBigInteger(nums[i]);
            var oldValues = seen.getOrDefault(logs[i], new HashMap<>());
            oldValues.put(nums[i], oldValues.getOrDefault(nums[i], 0) + 1);
            seen.put(logs[i], oldValues);

            for (int j = i; j < n; j++) {
                double logSum = logs[i] + logs[j];
                var sameValues = seen.get(logSum);
                var lowerValues = seen.lowerEntry(logSum);
                var higherValues = seen.higherEntry(logSum);

                boolean lowerOk = lowerValues != null && closeEnough(logSum, lowerValues.getKey());
                boolean higherOk = higherValues != null && closeEnough(logSum, higherValues.getKey());

                // if i and j are both one, then skip
                if (nums[i].equals(BigInteger.ONE) && nums[j].equals(BigInteger.ONE)) {
                    continue;
                }

                if (sameValues == null && !lowerOk && !higherOk) {
                    continue;
                }

                int total = 0;
                var prod = nums[i].multiply(nums[j]);

                total += process(sameValues, prod);

                if (lowerOk) {
                    total += process(lowerValues.getValue(), prod);
                }

                if (higherOk) {
                    total += process(higherValues.getValue(), prod);
                }

                if (i == j) {
                    ans += total;
                } else {
                    ans += 2 * total;
                }
            }
        }

        // deal with ones
        int oneCount = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i].equals(BigInteger.ONE)) {
                oneCount++;
            }
        }

        ans += oneCount * oneCount * oneCount;

        io.println(ans);
        io.close();
    }

    static boolean closeEnough(double base, Double value) {
        return value != null && (base - value) < eps;
    }

    static int process(HashMap<BigInteger, Integer> cnts, BigInteger prod) {
        int ans = 0;
        if (cnts != null) {
            for (var num : cnts.entrySet()) {
                if (prod.equals(num.getKey())) {
                    ans += num.getValue();
                }
            }
        }
        return ans;
    }
}

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
	super(new BufferedOutputStream(System.out));
	r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
	super(new BufferedOutputStream(o));
	r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
	return peekToken() != null;
    }

    public int getInt() {
	return Integer.parseInt(nextToken());
    }

    public double getDouble() { 
	return Double.parseDouble(nextToken());
    }

    public long getLong() {
	return Long.parseLong(nextToken());
    }

    public String getWord() {
	return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
	if (token == null) 
	    try {
		while (st == null || !st.hasMoreTokens()) {
		    line = r.readLine();
		    if (line == null) return null;
		    st = new StringTokenizer(line);
		}
		token = st.nextToken();
	    } catch (IOException e) { }
	return token;
    }

    private String nextToken() {
	String ans = peekToken();
	token = null;
	return ans;
    }
}

/**
 * Provides some mathematical operations on {@code BigDecimal} and {@code BigInteger}.
 * Static methods.
 */
class BigMath {
    public static final double LOG_2 = Math.log(2.0);
    public static final double LOG_10 = Math.log(10.0);

    // numbers greater than 10^MAX_DIGITS_10 or e^MAX_DIGITS_E are considered unsafe ('too big') for floating point operations
    private static final int MAX_DIGITS_10 = 294;
    private static final int MAX_DIGITS_2 = 977; // ~ MAX_DIGITS_10 * LN(10)/LN(2)
    private static final int MAX_DIGITS_E = 677; // ~ MAX_DIGITS_10 * LN(10)

    /**
     * Computes the natural logarithm of a {@link BigInteger} 
     * <p>
     * Works for really big integers (practically unlimited), even when the argument 
     * falls outside the {@code double} range
     * <p>
     * 
     * 
     * @param val Argument
     * @return Natural logarithm, as in {@link java.lang.Math#log(double)}<br>
     * {@code Nan} if argument is negative, {@code NEGATIVE_INFINITY} if zero.
     */
    public static double logBigInteger(BigInteger val) {
        if (val.signum() < 1)
            return val.signum() < 0 ? Double.NaN : Double.NEGATIVE_INFINITY;
        int blex = val.bitLength() - MAX_DIGITS_2; // any value in 60..1023 works here
        if (blex > 0)
            val = val.shiftRight(blex);
        double res = Math.log(val.doubleValue());
        return blex > 0 ? res + blex * LOG_2 : res;
    }

    /**
     * Computes the natural logarithm of a {@link BigDecimal} 
     * <p>
     * Works for really big (or really small) arguments, even outside the double range.
     * 
     * @param val Argument
     * @return Natural logarithm, as in {@link java.lang.Math#log(double)}<br>
     * {@code Nan} if argument is negative, {@code NEGATIVE_INFINITY} if zero.
     */
    public static double logBigDecimal(BigDecimal val) {
        if (val.signum() < 1)
            return val.signum() < 0 ? Double.NaN : Double.NEGATIVE_INFINITY;
        int digits = val.precision() - val.scale();
        if (digits < MAX_DIGITS_10 && digits > -MAX_DIGITS_10)
            return Math.log(val.doubleValue());
        else
            return logBigInteger(val.unscaledValue()) - val.scale() * LOG_10;
    }

    /**
     * Computes the exponential function, returning a {@link BigDecimal} (precision ~ 16).
     * <p>
     * Works for very big and very small exponents, even when the result 
     * falls outside the double range.
     *
     * @param exponent Any finite value (infinite or {@code Nan} throws {@code IllegalArgumentException})    
     * @return The value of {@code e} (base of the natural logarithms) raised to the given exponent, 
     * as in {@link java.lang.Math#exp(double)}
     */
    public static BigDecimal expBig(double exponent) {
        if (!Double.isFinite(exponent))
            throw new IllegalArgumentException("Infinite not accepted: " + exponent);
        // e^b = e^(b2+c) = e^b2 2^t with e^c = 2^t 
        double bc = MAX_DIGITS_E;
        if (exponent < bc && exponent > -bc)
            return new BigDecimal(Math.exp(exponent), MathContext.DECIMAL64);
        boolean neg = false;
        if (exponent < 0) {
            neg = true;
            exponent = -exponent;
        }
        double b2 = bc;
        double c = exponent - bc;
        int t = (int) Math.ceil(c / LOG_10);
        c = t * LOG_10;
        b2 = exponent - c;
        if (neg) {
            b2 = -b2;
            t = -t;
        }
        return new BigDecimal(Math.exp(b2), MathContext.DECIMAL64).movePointRight(t);
    }

    /**
     * Same as {@link java.lang.Math#pow(double,double)} but returns a {@link BigDecimal} (precision ~ 16).
     * <p>
     * Works even for outputs that fall outside the {@code double} range.
     * <br>
     * The only limitation is that {@code b * log(a)} cannot exceed the {@code double} range. 
     * 
     * @param a Base. Should be non-negative 
     * @param b Exponent. Should be finite (and non-negative if base is zero)
     * @return Returns the value of the first argument raised to the power of the second argument.
     */
    public static BigDecimal powBig(double a, double b) {
        if (!(Double.isFinite(a) && Double.isFinite(b)))
            throw new IllegalArgumentException(
                    Double.isFinite(b) ? "base not finite: a=" + a : "exponent not finite: b=" + b);
        if (b == 0)
            return BigDecimal.ONE;
        else if (b == 1)
            return BigDecimal.valueOf(a);
        if (a <= 0) {
            if (a == 0) {
                if (b >= 0)
                    return BigDecimal.ZERO;
                else
                    throw new IllegalArgumentException("0**negative = infinite b=" + b);
            } else
                throw new IllegalArgumentException("negative base a=" + a);
        }
        double x = b * Math.log(a);
        if (Math.abs(x) < MAX_DIGITS_E)
            return BigDecimal.valueOf(Math.pow(a, b));
        else
            return expBig(x);
    }
}
