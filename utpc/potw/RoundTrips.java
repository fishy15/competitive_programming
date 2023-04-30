package round_trips;

import java.io.*;
import java.util.*;

public class RoundTrips {
    static HashSet<Integer>[] graph;
    static int[] visited;
    static boolean[] onStack;
    static int[] lowlink;
    static ArrayDeque<Integer> stack = new ArrayDeque<>();
    static int sccIndex = 0;
    static int sccNum = 0;
    static int[] sccs;
    static HashSet<Integer>[] dag;
    static int[] nodesPerScc;
    static ArrayDeque<Integer> topoSort = new ArrayDeque<>();

    public static void main(String[] args) throws IOException {
        Kattio io;
        String fileName = "";
        if (fileName.equals("") == false) {
            io = new Kattio(fileName);
        } else {
            io = new Kattio();
        }
        int townNum = io.nextInt();
        int roadNum = io.nextInt();
        graph = new HashSet[townNum];
        for (int i = 0; i < townNum; i++) {
            graph[i] = new HashSet<>();
        }
        for (int i = 0; i < roadNum; i++) {
            graph[io.nextInt()].add(io.nextInt());
        }
        visited = new int[townNum];
        onStack = new boolean[townNum];
        lowlink = new int[townNum];
        sccs = new int[townNum];
        Arrays.fill(visited, -1);
        for (int i = 0; i < townNum; i++) {
            if (visited[i] == -1) {
                strongConnect(i);
            }
        }
        dag = new HashSet[sccNum];
        nodesPerScc = new int[sccNum];
        for (int i = 0; i < sccNum; i++) {
            dag[i] = new HashSet<>();
        }
        long remove = 0;
        for (int i = 0; i < townNum; i++) {
            nodesPerScc[sccs[i]]++;
            for (int j : graph[i]) {
                if (sccs[i] != sccs[j]) {
                    dag[sccs[i]].add(sccs[j]);
                    remove++;
                }
            }
        }
        visited = new int[sccNum];

        for (int i = 0; i < sccNum; i++) {
            topoSort(i);
        }
        long total = 0;
        int totalNodes = townNum;
        for (int v : topoSort) {
            totalNodes -= nodesPerScc[v];
            total += (long) totalNodes * nodesPerScc[v];
        }
        io.println(total - remove);
        io.close();
    }

    static void topoSort(int v) {
        if (visited[v] == 2) {
            return;
        }
        if (visited[v] == 1) {
            throw new IllegalArgumentException();
        }
        visited[v] = 1;
        for (int next : dag[v]) {
            topoSort(next);
        }
        visited[v] = 2;
        topoSort.addFirst(v);
    }

    static void strongConnect(int v) {
        visited[v] = sccIndex;
        lowlink[v] = visited[v];
        sccIndex++;
        stack.add(v);
        onStack[v] = true;
        for (int next : graph[v]) {
            if (visited[next] == -1) {
                strongConnect(next);
                lowlink[v] = Math.min(lowlink[v], lowlink[next]);
            } else if (onStack[next] == true) {
                lowlink[v] = Math.min(lowlink[v], visited[next]);
            }
        }
        if (visited[v] == lowlink[v]) {
            int node = -1;
            while (node != v) {
                node = stack.removeLast();
                onStack[node] = false;
                sccs[node] = sccNum;
            }
            sccNum++;
        }
    }
}

class Kattio extends PrintWriter {
    private BufferedReader r;
    private StringTokenizer st = new StringTokenizer("");
    private String token;
    private String line;

    // standard input
    public Kattio() {
        this(System.in, System.out);
    }

    public Kattio(InputStream i, OutputStream o) {
        super(o);
        r = new BufferedReader(new InputStreamReader(i));
    }

    // USACO-style file input
    public Kattio(String problemName) throws IOException {
        super(new FileWriter(problemName + ".out"));
        r = new BufferedReader(new FileReader(problemName + ".in"));
    }

    private String peek() {
        if (token == null)
            try {
                while (!st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null)
                        return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) {
            }
        return token;
    }

    public boolean hasMoreTokens() {
        return peek() != null;
    }

    public String next() {
        String ans = peek();
        token = null;
        return ans;
    }

    public IoTokenizer nextLineTokenizer() {
        String nextLine = nextLine();
        if (nextLine == null)
            return null;
        else
            return new IoTokenizer(nextLine);
    }

    public String nextLine() {
        peek();
        token = null;
        st = new StringTokenizer("");
        return line;
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public double nextDouble() {
        return Double.parseDouble(next());
    }

    public long nextLong() {
        return Long.parseLong(next());
    }
}

class IoTokenizer extends StringTokenizer {

    public IoTokenizer(String str, String delim) {
        super(str, delim);
    }

    public IoTokenizer(String str, String delim, boolean returnDelims) {
        super(str, delim, returnDelims);
    }

    public IoTokenizer(String str) {
        super(str);
    }

    public int nextInt() {
        return Integer.parseInt(nextToken());
    }
}
