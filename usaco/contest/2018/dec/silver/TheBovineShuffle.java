import java.util.*;
import java.io.*; 

public class TheBovineShuffle {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("shuffle.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shuffle.out"))); 
        int n = Integer.parseInt(in.readLine()); 
        byte[] pos = new byte[n + 1]; 
        int[] shuffle = new int[n + 1]; 
        StringTokenizer st = new StringTokenizer(in.readLine());
        for(int i = 1; i < n + 1; i++) {
            shuffle[i] = Integer.parseInt(st.nextToken());
        }
        int count = 0; 

        for (int i = 1; i < n + 1; i++) {
            if (pos[i] == 0) {
                ArrayList<Integer> cycle = new ArrayList<>();
                int loc = i; 
                boolean[] pos2 = new boolean[n + 1]; 
                for (int j = i; j < n + 1; j++) {
                    cycle.add(loc);
                    pos2[loc] = true; 
                    loc = shuffle[loc];
                    if (pos2[loc]) {
                        int index = cycle.indexOf(loc);
                        for (int k = 0; k < cycle.size(); k++) {
                            if (k < index) {
                                pos[cycle.get(k)] = -1;
                            } else {
                                pos[cycle.get(k)] = 1;
                            }
                        }
                        break;
                    }
                } 
            }
        }

        for (int i = 1; i < n + 1; i++) {
            if (pos[i] == 1) {
                count++;
            }
        }
        //for (int i : pos) System.out.println(i);
        out.println(count);
        out.close();
    }
}