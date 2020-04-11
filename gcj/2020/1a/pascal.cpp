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
    int n; cin >> n;

    for (int row = 1; row <= 31; row++) {
        int nn = n - row;

        vector<int> rem;
        for (int j = row - 1; j > 0; j--) {
            if ((1 << j) - 1 <= nn) {
                rem.push_back(j + 1); 
                nn -= (1 << j) - 1;
            }
        }

        if (nn > 40) continue;
        reverse(rem.begin(), rem.end());
        bool l = true;
        int cur = 0;

        for (int i = 1; i <= row; i++) {
            if (cur < rem.size() && rem[cur] == i) {
                if (l) {
                    for (int j = 1; j <= i; j++) {
                        cout << i << ' ' << j << '\n';
                    }
                } else {
                    for (int j = i; j >= 1; j--) {
                        cout << i << ' ' << j << '\n';
                    }
                }

                l = !l;
                cur++;
                n -= (1 << (i - 1));
            } else {
                if (l) {
                    cout << i << ' ' << 1 << '\n';
                } else {
                    cout << i << ' ' << i << '\n';
                }
                n--;
            }
        }

        for (int i = 1; i <= n; i++) {
            if (l) {
                cout << row + i << ' ' << 1 << '\n';
            } else {
                cout << row + i << ' ' << row + i << '\n';
            }
        }

        return;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }

    return 0;
}
