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

#define int ll

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    string s;
    cin >> s;

    array<int, 3> m_cnt{};
    array<array<int, 3>, 3> me_cnt{};

    for (int i = 0; i < 3; i++) {
        m_cnt[i] = 0;
        for (int j = 0; j < 3; j++) {
            me_cnt[i][j] = 0;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'M') {
            m_cnt[a[i]]++;
        } else if (s[i] == 'E') {
            for (int m = 0; m < 3; m++) {
                me_cnt[m][a[i]] += m_cnt[m];
            }
        } else {
            for (int m = 0; m < 3; m++) {
                for (int e = 0; e < 3; e++) {
                    int x = a[i];

                    int mex = 0;
                    while (mex == m || mex == e || mex == x) {
                        mex++;
                    }

                    ans += (ll) me_cnt[m][e] * mex;
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
