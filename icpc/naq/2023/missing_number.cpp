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

void solve() {
    string s;
    cin >> s;

    int n = s.size();

    set<int> ans;
    for (int a = 1; a <= 5; a++) {
        if (n < a) break;
        int cur = stoi(s.substr(0, a));
        int st = cur;

        bool valid = true;
        bool skipped = false;
        int val_skipped = -1;

        int p = a;
        while (p < n) {
            cur++;
            if (cur >= 100'000) {
                valid = false;
                break;
            }

            auto rep = to_string(cur);
            if (p + (int) rep.size() <= n) {
                auto ss = s.substr(p, rep.size());
                if (ss == rep) {
                    p += rep.size();
                } else {
                    if (skipped) {
                        valid = false;
                        break;
                    } else {
                        skipped = true;
                        val_skipped = cur;
                    }
                }
            } else {
                valid = false;
                break;
            }
        }

        if (valid) {
            if (skipped) {
                ans.insert(val_skipped);
            } else {
                if (st - 1 >= 1) {
                    ans.insert(st - 1);
                } 

                if (cur + 1 < 100'000) {
                    ans.insert(cur + 1);
                }
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
