vector<int> adj[MAXN];
int par[MAXN];
int sz[MAXN];
int in[MAXN];
int head[MAXN];
int d[MAXN];
int t;

void dfs_size(int v, int p) {
    sz[v] = 1;
    for (int &e : adj[v]) {
        if (e != p) {
            d[e] = d[v] + 1;
            par[e] = v;
            dfs_size(e, v);
            sz[v] += sz[e];
            if (sz[e] > sz[adj[v][0]] || adj[v][0] == p) swap(e, adj[v][0]);
        }
    }
}

void dfs_hld(int v, int p) {
    in[v] = t++;
    for (int e : adj[v]) {
        if (e != p) {
            if (e == adj[v][0]) {
                head[e] = head[v];
            } else {
                head[e] = e;
            }
            dfs_hld(e, v);
        }
    }
}

void op_path(int x, int y, function<void(int,int)> op) {
    while (head[x] != head[y]) {
        if (d[head[x]] > d[head[y]]) swap(x, y);
        op(in[head[y]], in[y]);
        y = par[head[y]];
    }
    if (d[x] > d[y]) swap(x, y);
    op(in[x], in[y]); // if vals in edges, add 1 to in[x] to exclude parent edge
}

void op_subtree(int x, function<void(int,int)> op) {
    op(in[x], in[x] + sz[x] - 1); // if vals in edges, add 1 to in[x] to exclude parent edge
}
