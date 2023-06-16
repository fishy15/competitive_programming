#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <queue>

#define ll long long
#define MOD 1000000007
#define MAXN 110

using namespace std;

struct mi {
    ll v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}

    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }

    mi operator+(const mi &m2) const {
        mi m = *this;
        return m += m2;
    }

    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }

    mi operator*(const mi &m2) const {
        mi m = *this;
        return m *= m2;
    }
};

bool has_cycle(int n, const vector<string> &grid) {
    vector<int> out_deg(n);
    vector<bool> done(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                out_deg[i]++;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (out_deg[i] == 0) {
            q.push(i);
        }    
    }

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        done[t] = true;
        for (int i = 0; i < n; i++) {
            if (grid[i][t] == '1') {
                out_deg[i]--;
                if (out_deg[i] == 0) q.push(i);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!done[i]) return true;
    }

    return false;
}

void rem_one_path(int n, vector<string> &grid, int x, int y) {
    vector<int> prev(n, -1);
    queue<int> q;

    q.push(x);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        if (t == y) break;

        for (int i = 0; i < n; i++) {
            if (grid[t][i] == '1' && prev[i] == -1) {
                prev[i] = t;
                q.push(i);
            }
        }
    }

    int cur = y;
    while (cur != x && cur != -1) {
        grid[prev[cur]][cur] = '0';
        cur = prev[cur];
    }
}

mi get_num_paths(int n, const vector<string> &grid, int x, int y) {
    vector<mi> path(n);
    vector<bool> vis(n);

    queue<int> q;
    q.push(x);
    path[x] = 1;

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        if (vis[t]) continue;
        vis[t] = true;
        for (int i = 0; i < n; i++) {
            if (grid[t][i] == '1' && !vis[i]) {
                path[i] += path[t];
                q.push(i);
            }
        }
    }

    return path[y];
}

void solve() {
    int n, k; 
    cin >> n >> k;

    string sr; 
    cin >> sr;

    vector<string> grid(n);
    vector<int> pass(n);
    array<int, 2> cyc = {-1, -1};
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    mi mul = 1;
    if (k == 1 && has_cycle(n, grid)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (grid[i][j] == '1') {
                    cyc = {i, j};
                }
            }
        }
        mul = get_num_paths(n, grid, cyc[1], cyc[0]);
        rem_one_path(n, grid, cyc[1], cyc[0]);
        grid[cyc[0]][cyc[1]] = '0';
    }

    mi ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                pass[i]++;
            }
        }

        if (sr[i] == 'R') {
            pass[i]++;
        }

        for (int j = 1; j <= pass[i]; j++) {
            ans *= j;
        }
    }

    if (k == 1 && cyc[0] != -1) {
        mi tot = pass[cyc[0]] + pass[cyc[1]] + pass[cyc[0]] * pass[cyc[1]];
        ans *= tot * mul;
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
