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

    int n, m;
    cin >> n >> m;

    vector<vector<int>> ords;
    ords.push_back(vector<int>(n, -1));
    
    vector<bool> placed(n);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        placed[a] = true;
        placed[b] = true;

        vector<vector<int>> new_ord;
        for (auto &ord : ords) {
            int idx1 = find(ord.begin(), ord.end(), a) - ord.begin();
            int idx2 = find(ord.begin(), ord.end(), b) - ord.begin();
            if (idx1 != n && idx2 != n) {
                if (idx1 - idx2 == c) {
                    new_ord.push_back(ord);
                }
            } else if (idx1 != n) {
                if (idx1 - c >= 0 && ord[idx1 - c] == -1) {
                    ord[idx1 - c] = b;
                    new_ord.push_back(ord);
                }
            } else if (idx2 != n) {
                if (idx2 + c < n && ord[idx2 + c] == -1) {
                    ord[idx2 + c] = a;
                    new_ord.push_back(ord);
                }
            } else {
                for (int i = 0; i + c < n; i++) {
                    if (ord[i] == -1 && ord[i + c] == -1) {
                        ord[i] = b;
                        ord[i + c] = a;
                        new_ord.push_back(ord);
                        ord[i] = -1;
                        ord[i + c] = -1;
                    }
                }
            }
        }

        ords = new_ord;
    }

    if (count(placed.begin(), placed.end(), false) == 1) {
        int missing = find(placed.begin(), placed.end(), false) - placed.begin();
        for (auto &ord : ords) {
            auto neg_one = find(ord.begin(), ord.end(), -1);
            *neg_one = missing;
        }
    }

    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
        int must_be = -2;
        for (auto &ord : ords) {
            if (must_be == -2) {
                must_be = ord[i];
            } else if (must_be != ord[i]) {
                must_be = -1;
            }
        }

        if (must_be != -1) {
            ans[must_be] = i + 1;
        }
    }

    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
