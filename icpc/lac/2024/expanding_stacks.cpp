#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for (int i = (a); i < (b); i++)

struct TwoSat {
    int N;
    vector<vi> gr;
    vi values;

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    void either(int f, int j) {
        f = max(2*f, -1-2*f);
        j = max(2*j, -1-2*j);
        gr[f].push_back(j^1);
        gr[j].push_back(f^1);
    }

    void setValue(int x) { either(x, x); }

    vi val, comp, z; int time = 0;
    int dfs(int i) {
        int low = val[i] = ++time, x; z.push_back(i);
        for(int e : gr[i]) if (!comp[e])
            low = min(low, val[e] ?: dfs(e));
        if (low == val[i]) do {
            x = z.back(); z.pop_back();
            comp[x] = low;
            if (values[x>>1] == -1)
                values[x>>1] = x&1;
        } while (x != i);
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2*N, 0); comp = val;
        rep(i,0,2*N) if (!comp[i]) dfs(i);
        rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<array<int, 2>> times(n);
    for (int i = 0; i < 2 * n; i++) {
        int x;
        cin >> x;

        if (x < 0) {
            times[-x - 1][1] = i;
        } else {
            times[x - 1][0] = i;
        }
    }

    TwoSat ts(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto bef1 = times[i][0] < times[j][0] && times[j][0] < times[i][1] && times[i][1] < times[j][1];
            auto bef2 = times[j][0] < times[i][0] && times[i][0] < times[j][1] &&times[j][1] < times[i][1];
            if (bef1 || bef2) {
                ts.either(i, j);
                ts.either(~i, ~j);
            }
        }
    }

    if (ts.solve()) {
        for (int i = 0; i < n; i++) {
            if (ts.values[i]) {
                cout << 'G';
            } else {
                cout << 'S';
            }
        }
        cout << '\n';
    } else {
        cout << "*\n";
    }

    return 0;
}
