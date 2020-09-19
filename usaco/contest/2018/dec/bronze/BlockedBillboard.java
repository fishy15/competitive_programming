import java.util.*;
import java.io.*; 

public class BlockedBillboard {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("billboard.in")); 
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("billboard.out"))); 
        StringTokenizer st1 = new StringTokenizer(in.readLine()); 
        StringTokenizer st2 = new StringTokenizer(in.readLine()); 
        StringTokenizer st3 = new StringTokenizer(in.readLine()); 

        // x1 y1 x2 y2 all arrays
        int[] bil1 = {Integer.parseInt(st1.nextToken()), Integer.parseInt(st1.nextToken()), Integer.parseInt(st1.nextToken()), Integer.parseInt(st1.nextToken())}; 
        int[] bil2 = {Integer.parseInt(st2.nextToken()), Integer.parseInt(st2.nextToken()), Integer.parseInt(st2.nextToken()), Integer.parseInt(st2.nextToken())}; 
        int[] truck = {Integer.parseInt(st3.nextToken()), Integer.parseInt(st3.nextToken()), Integer.parseInt(st3.nextToken()), Integer.parseInt(st3.nextToken())};
        int[] com1 = new int[4];
        int[] com2 = new int[4]; 

        com1[0] = max(bil1[0], truck[0]);
        com1[1] = max(bil1[1], truck[1]);
        com1[2] = min(bil1[2], truck[2]);
        com1[3] = min(bil1[3], truck[3]);

        com2[0] = max(bil2[0], truck[0]);
        com2[1] = max(bil2[1], truck[1]);
        com2[2] = min(bil2[2], truck[2]);
        com2[3] = min(bil2[3], truck[3]);

        out.println(area(bil1) + area(bil2) - area(com1) - area(com2));
        out.close(); 
    }

    public static int max(int x, int y) {
        if (x > y) {
            return x;
        }
        return y; 
    }

    public static int min(int x, int y) {
        if (x < y) {
            return x;
        }
        return y; 
    }

    public static int area(int[] x) {
        if (x[0] >= x[2] || x[1] >= x[3]) {
            return 0; 
        }
        return (x[2] - x[0]) * (x[3] - x[1]);
    }
}