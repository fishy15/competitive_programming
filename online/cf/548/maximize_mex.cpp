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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 5000

using namespace std;

int n, m, d;

// 0-4999 is potential, 5000-9999 is club
vector<int> graph[2 * MAXN]; 
array<int, 2> edge[MAXN];
vector<int> ord;
bool before[MAXN];

// for kuhn's algorithm
bool used[2 * MAXN];
int match[2 * MAXN];
int ans[MAXN];

bool dfs(int v) {
    if (used[v]) {
        return false;
    } else {
        used[v] = true;
        for (int e : graph[v]) {
            if (match[e] == -1 || dfs(match[e])) {
                match[e] = v;
                return true;
            }
        }
        return false;
    }
}

bool check(int v) {
    fill(used, used + 2 * MAXN, false);
    return dfs(v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        edge[i][0] = p;
    }

    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        c--;
        edge[i][1] = c + MAXN;
    }

    fill(before, before + n, true);
    cin >> d;
    for (int i = 0; i < d; i++) {
        int x; cin >> x;
        x--;
        ord.push_back(x);
        before[x] = false;
    }

    reverse(ord.begin(), ord.end());
    for (int i = 0; i < n; i++) {
        if (before[i]) {
            auto [a, b] = edge[i];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
    }

    int cur_pos = 0;
    fill(match, match + 2 * MAXN, -1);
    for (int i = 0; i < d; i++) {
        while (cur_pos < m && check(cur_pos)) cur_pos++;
        ans[i] = cur_pos;

        auto [a, b] = edge[ord[i]];
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = d - 1; i >= 0; i--) {
        cout << ans[i] << '\n';
    }

    return 0;
}
