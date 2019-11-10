// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    string s; int q; cin >> s >> q;
    int n = (int)(s.size());
    int sz = (int)(sqrt(s.size()));

    vector<vector<int>> decomp;

    for (int i = 0; i < n; i += sz) {
        vector<int> smth(26);
        for (int j = i; j < min(i + sz, n); j++) {
            smth[s[j] - 'a'] = 1;
        }
        decomp.push_back(smth);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int pos; 
            char c; 
            cin >> pos >> c;
            s[pos - 1] = c;
            int start = (pos - 1) / sz;

            vector<int> smth(26);
            for (int j = start * sz; j < min(start * sz + sz, n); j++) {
                smth[s[j] - 'a'] = 1;
            }

            decomp[start] = smth;
        } else {
            int l, r; cin >> l >> r;
            l--; r--;
            vector<int> smth(26);
            int start = l / sz + 1;
            int end = r / sz;
            if (end + 1 == start) {
                for (int i = l; i <= r; i++) {
                    smth[s[i] - 'a'] = 1;
                }
            } else {
                for (int i = l; i < min(start * sz, n); i++) {
                    smth[s[i] - 'a'] = 1;
                }
                for (int i = start; i <= end; i++) {
                    for (int j = 0; j < 26; j++) {
                        if (decomp[i][j]) {
                            smth[j] = 1;
                        }
                    }
                }
                for (int i = end * sz; i <= r; i++) {
                    smth[s[i] - 'a'] = 1;
                }
            }

            int ans = 0;
            for (int i : smth) {
                ans += i;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
