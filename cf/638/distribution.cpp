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

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    int cnt[26];
    for (int i = 0; i < 26; i++) cnt[i] = 0;
    for (char c : s) {
        cnt[c - 'a']++;
    }

    int mini = 26;
    int maxi = -1;
    bool zero = true;
    int tot = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i]) {
            mini = min(mini, i);
            maxi = max(maxi, i);
            tot++;
        }

        if (cnt[i] % k != 0) zero = false;
    }

    if (mini == maxi) {
        int len = ceil(1.0 * n / k);
        for (int i = 0; i < len; i++) {
            cout << (char)(mini + 'a');
        } cout << '\n';
    } else {
        if (cnt[mini] < k) {
            int qq = 0;
            for (int i = mini; i < 26; i++) {
                qq += cnt[i];
                if (qq >= k) {
                    cout << (char)(i + 'a') << '\n';
                    return;
                }
            }
        } else {
            if (tot == 2 && cnt[mini] == k) {
                for (int i = 0; i < cnt[mini] / k; i++) {
                    cout << (char)(mini + 'a');
                }
                for (int i = 0; i < ceil(1.0 * cnt[maxi] / k); i++) {
                    cout << (char)(maxi + 'a');
                }
                cout << '\n';
                return;
            }
            cout << (char)(mini + 'a');
            cnt[mini] -= k;
            for (int i = mini; i <= maxi; i++) {
                for (int j = 0; j < cnt[i]; j++) {
                    cout << (char)(i + 'a');
                }
            }
            cout << '\n';
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
