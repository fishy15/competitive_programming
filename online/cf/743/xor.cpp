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
    int n; cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i]; 
    }

    vector<pair<int, int>> compress;
    for (int c : nums) {
        if (compress.empty() || compress.back().first != c) {
            compress.push_back({c, 1});
        } else {
            compress.back().second++;
        }
    }

    int sz = compress.size();
    int first_pos = 0;
    vector<int> op;
    for (int i = 0; i < sz; i++) {
        if (compress[i].first == 1) {
            if (compress[i].second % 2 == 1) {
                if (i < sz - 2 && compress[i + 1] == pair<int, int>{0, 1}) {
                    op.push_back(first_pos + compress[i].second - 1);
                    compress[i].second--;
                    compress[i + 2].second--;
                    compress[i + 1].second += 2;
                } else {
                    cout << "NO\n";
                    return;
                }
            }
        }

        first_pos += compress[i].second;
    }

    { 
        vector<pair<int, int>> compress2;
        for (auto p : compress) {
            if (p.second > 0) {
                compress2.push_back(p);
            }
        }
        compress.swap(compress2);
    }

    sz = compress.size();
    first_pos = 0;
    for (int i = 0; i < sz; i++) {
        if (compress[i].first == 1) {
            int end = first_pos + compress[i].second;
            if (i > 0) {
                for (int j = first_pos - 1; j + 2 < end; j += 2) {
                    op.push_back(j);
                }
            } else {
                for (int j = end - 2; j >= first_pos; j -= 2) {
                    op.push_back(j);
                }
            }
        }

        first_pos += compress[i].second;
    }

    cout << "YES\n";
    cout << op.size() << '\n';
    if (!op.empty()) {
        for (int i : op) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
