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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, m;
vector<int> adj[MAXN];
int in[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[b].push_back(a);
        in[a]++;
    }

    priority_queue<int> zero;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (!in[i]) zero.push(i);
    }

    int cnt = 0;
    while (!zero.empty()) {
        int cur = zero.top();
        zero.pop();

        cnt++;
        ans.push_back(cur);
        for (int i : adj[cur]) {
            in[i]--;
            if (!in[i]) zero.push(i);
        }
    }

    reverse(ans.begin(), ans.end());

    if (cnt == n) {
        for (int i : ans) {
            cout << i + 1 << ' ';
        } 
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
