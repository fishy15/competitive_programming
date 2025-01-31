#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs; vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        g[s].pb({t, sz(g[t]), 0, cap});
        g[t].pb({s, sz(g[s])-1, 0, rcap});
    }

    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].pb(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = sz(g); H[s] = v; ec[t] = 1;
        vi co(2*v); co[0] = v-1;
        rep(i,0,v) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) 
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
                        H[u] = H[e.dest]+1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        rep(i,0,v) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("trading.in", "r", stdin);
    freopen("trading.out", "w", stdout);

    int p, n, m;
    cin >> p >> n >> m;

    vector<string> resc(n);
    map<string, int> resc_to_int;
    rep(i, 0, n) {
        string r;
        cin >> r;
        resc[i] = r;
        resc_to_int[r] = i;
    }

    vector<string> build(m);
    map<string, int> build_to_int;
    vector build_needs(m, vector(n, 0));
    string sdlkfj;
    getline(cin, sdlkfj);
    rep(i, 0, m) {
        string line;
        getline(cin, line);
        stringstream ss(line); 

        string b;
        ss >> b;
        build[i] = b;
        build_to_int[b] = i;

        string trash;
        ss >> trash;

        while (true) {
            int num;
            string r;
            ss >> num >> r;
            if (!ss) break;

            if (r.back() == ',') {
                r = r.substr(0, sz(r) - 1);
            }

            build_needs[i][resc_to_int[r]] = num;
        }
    }

    vector<string> ppl(p);
    vector owned(p, vector(n, 0));
    vector<int> wanted(p);
    rep(i, 0, p) {
        string line;
        getline(cin, line);
        stringstream ss(line); 

        string name;
        ss >> name;
        ppl[i] = name;

        string trash;
        ss >> trash;

        string b;
        ss >> b;

        if (b.back() == ',') {
            b = b.substr(0, sz(b) - 1);
        }

        wanted[i] = build_to_int[b];

        // "has"
        ss >> trash;
        if (!ss) continue;

        while (true) {
            int num;
            string r;
            ss >> num >> r;
            if (!ss) break;

            if (r.back() == ',') {
                r = r.substr(0, sz(r) - 1);
            }

            owned[i][resc_to_int[r]] = num;
        }
    }
    
    auto my_resource = [&](int x) { return x; };
    auto trader = [&](int person) { return n + person; };
    int src = n + p;
    int sink = src + 1;

    PushRelabel g(sink + 1);

    int sum_wants = 0;
    rep(i, 0, n) {
        const auto &my_wants = build_needs[wanted[0]];
        g.addEdge(src, my_resource(i), owned[0][i]);
        g.addEdge(my_resource(i), sink, my_wants[i]);
        sum_wants += my_wants[i];
    }

    rep(o, 1, p) {
        const auto &they_have = owned[o];
        const auto &they_want = build_needs[wanted[o]];
        rep(r, 0, n) {
            int will_take = max(0, they_want[r] - they_have[r]);
            int will_give = max(0, they_have[r] - they_want[r]);
            g.addEdge(my_resource(r), trader(o), will_take);
            g.addEdge(trader(o), my_resource(r), will_give);
        }
    }

    auto fl = g.calc(src, sink);
    if (fl != sum_wants) {
        cout << "No way\n";
        return 0;
    }

    auto construct_path = [&] {
        vector<int> res;
        auto dfs = [&](auto &&self, int v) -> bool {
            res.push_back(v);
            for (auto &x : g.g[v]) {
                if (x.f > 0) {
                    x.f--;
                    self(self, x.dest);
                    return true;
                }
            }
            return false;
        };
        auto bb = dfs(dfs, src);
        return pair{res, bb};
    };

    while (true) {
        auto [v, bb] = construct_path();
        if (!bb) break;

        v = vector(begin(v) + 1, end(v) - 1);
        for (int i = 1; i < sz(v); i += 2) {
            int old_r = v[i - 1];
            int new_r = v[i + 1];
            int t = v[i] - n;
            cout << "trade with " << ppl[t] << ' ' << resc[old_r] << " for " << resc[new_r] << '\n';
        }
    }

    cout << "build " << build[wanted[0]] << '\n';

    return 0;
}
