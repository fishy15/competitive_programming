#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve() {
    int n;
    cin >> n;
    
    vector<int> pow_cnt(32);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        int cnt = 0;
        while (x > 1) {
            x /= 2;
            cnt++;
        }
        
        pow_cnt[cnt]++;
    }
    
    cout << *max_element(pow_cnt.begin(), pow_cnt.end()) << '\n';
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
