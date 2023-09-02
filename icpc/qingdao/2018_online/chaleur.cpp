#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int solve(int n, const vector<int> &deg) {
    int end = 0;
    for (int k = n; k >= 1; k--) {
        while (end < n && deg[end] >= k - 1) {
            end++;
        }
        
        if (end >= k) {
            return end - k + 1;
        }
    }
    
    return -1;
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        deg[a]++;
        deg[b]++;
    }
    
    sort(deg.rbegin(), deg.rend());
    int ans1 = solve(n, deg);
    
    for (int &x : deg) {
        x = n - 1 - x;
    }
    reverse(deg.begin(), deg.end());
    int ans2 = solve(n, deg);
    
    cout << ans1 << ' ' << ans2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
}
