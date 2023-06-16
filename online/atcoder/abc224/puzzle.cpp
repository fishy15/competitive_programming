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

ll conv(array<int, 9> arr) {
    ll res = 0;
    for (int i : arr) {
        res *= 10;
        res += i;
    }
    return res;
}

struct mm {
    map<ll, int> m;

    int &operator[](const array<int, 9> a) {
        return m[conv(a)];
    }

    int count(const array<int, 9> a) {
        return m.count(conv(a));
    }
};

int m;
vector<int> adj[10];
array<int, 9> start;
mm dist;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    start.fill(8);
    for (int i = 0; i < 8; i++) {
        int x; cin >> x;
        start[x - 1] = i;
    }

    dist[start] = 0;
    queue<array<int, 9>> q;
    q.push(start);

    while (!q.empty()) {
        auto t = q.front(); 
        q.pop();

        for (int i = 0; i < 9; i++) {
            if (t[i] == 8) {
                for (int j : adj[i]) {
                    auto nxt = t;
                    swap(nxt[i], nxt[j]);
                    if (!dist.count(nxt)) {
                        dist[nxt] = dist[t] + 1;
                        q.push(nxt);
                    }
                }
            }
        }
    }

    array<int, 9> end;
    iota(end.begin(), end.end(), 0);

    if (!dist.count(end)) {
        cout << "-1\n";
    } else {
        cout << dist[end] << '\n';
    }


    return 0;
}
