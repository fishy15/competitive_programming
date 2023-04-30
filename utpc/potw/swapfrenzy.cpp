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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string n;
    int k;
    cin >> n >> k;

    int sz = n.size();

    vector<pair<string, int>> cur = {{n, k}};
    for (int i = 0; i < sz && k > 0; i++) {
        vector<pair<string, int>> nxt;
        for (auto [s, cnt] : cur) {
            if (cnt == 0) {
                nxt.push_back({s, cnt});
            } else {
                auto best_val = *max_element(s.begin() + i, s.end());
                if (best_val != s[i]) {
                    for (int j = i + 1; j < sz; j++) {
                        if (s[j] == best_val) {
                            swap(s[i], s[j]);
                            nxt.push_back({s, cnt - 1});
                            swap(s[i], s[j]);
                        }
                    }
                } else {
                    nxt.push_back({s, cnt});
                }
            } 
        }

        if (!nxt.empty()) {
            sort(nxt.begin(), nxt.end());
            nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
            cur.swap(nxt);
        }

        /* cout << "cur:\n"; */
        /* for (auto [s, c] : cur) { */
        /*     cout << s << ' ' << c << '\n'; */
        /* } */
    }

    string ans;

    for (auto [s, c] : cur) {
        if (c % 2 == 1) {
            // if anything the same, then swap that
            bool found_same = false;
            for (int i = 0; i < sz - 1; i++) {
                if (s[i] == s[i + 1]) {
                    found_same = true;
                    break;
                }
            }

            if (!found_same) {
                swap(s[sz - 2], s[sz - 1]);
            }
        }

        ans = max(ans, s);
    }

    cout << ans << '\n';

    return 0;
}
