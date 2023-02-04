struct SCC {
    int sz;
    vector<vector<int>> adj;
    vector<vector<int>> radj;
    vector<int> comp;
    vector<bool> vis;
    vector<int> ord;
    vector<int> cur_comp;

    SCC(int m) : sz(m), adj(m), radj(m), comp(m), vis(m) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    void dfs_ord(int v) {
        vis[v] = true;
        for (int e : adj[v]) {
            if (!vis[e]) {
                dfs_ord(e);
            }
        }
        ord.push_back(v);
    }

    void dfs_scc(int v) {
        vis[v] = true;
        cur_comp.push_back(v);
        for (int e : radj[v]) {
            if (!vis[e]) {
                dfs_scc(e);
            }
        }
    }

    void find_scc() {
        for (int i = 0; i < sz; i++) {
            if (!vis[i]) {
                dfs_ord(i);
            }
        }

        fill(vis.begin(), vis.end(), false);
        reverse(ord.begin(), ord.end());

        int cnt = 0;
        for (int v : ord) {
            if (!vis[v]) {
                cur_comp = {};
                dfs_scc(v);
                for (int i : cur_comp) {
                    comp[i] = cnt;
                }
                cnt++;
            }
        }
    }
};
