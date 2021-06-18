/* 
ID: aaryan.1
PROG: gift1
LANG: JAVA
*/

import java.util.*;
import java.io.*;

public class gift1 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("gift1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gift1.out")));
        int NP = Integer.parseInt(in.readLine()); 
        String[] names = new String[NP];
        int[] money = new int[NP];
        for (int i = 0; i < NP; i++) {
            names[i] = in.readLine(); 
        }

        String giver; 
        StringTokenizer st;
        int amt;
        int NG;

        for (int j = 0; j < NP; j++) {
            giver = in.readLine();
            st = new StringTokenizer(in.readLine());
            amt = Integer.parseInt(st.nextToken());
            NG = Integer.parseInt(st.nextToken());
            if (NG != 0) {
                money[find(names, giver)] = money[find(names, giver)] - amt + (amt % NG);
                for (int i = 0; i < NG; i++) {
                    String n = in.readLine(); 
                    money[find(names, n)] += (amt / NG); 
                } 
            }
        }
        
        for (int i = 0; i < NP; i++) {
            out.println(names[i] + " " + money[i]);
        }

        out.close();
    }

    public static int find(String[] names, String name) {
        for (int i = 0; i < names.length; i++) {
            if (names[i].equals(name)) {
                return i; 
            }
        }

        return -1; 
    }
}