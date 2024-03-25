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

    int k, n;
    cin >> k >> n;

    vector<pair<int, int>> pieces(k);
    for (int i = 0; i < k; i++) {
        cin >> pieces[i].first;
    }
    for (int i = 0; i < k; i++) {
        cin >> pieces[i].second;
    }

    array<array<vector<int>, 4>, 4> p;

    for (int i = 0; i < k; i++) {
        auto [b, a] = minmax(pieces[i].first, pieces[i].second);
        p[a][b].push_back(i + 1);
    }

    vector ans(n, array<int, 3>{});

    int left = 0;

    auto process3 = [&](int len) {
        for (auto c : p[3][len]) {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < 3; j++) {
                    ans[left + i][j] = c;
                }
            }
            left += len;
        }
    };

    process3(3);
    process3(2);

    int left2 = left;
    for (auto c : p[2][2]) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ans[left2 + i][j] = c;
            }
        }
        left2 += 2;
    }

    // place as many as we can right side up, then lay down
    for (auto c : p[2][1]) {
        if (left2 == n) {
            ans[left][2] = c;
            ans[left+1][2] = c;
            left += 2;
        } else {
            ans[left2][0] = c;
            ans[left2][1] = c;
            left2++;
        }
    }

    // place as many as we can right side up, then lay down
    for (auto c : p[3][1]) {
        if (left2 == n) {
            ans[left][2] = c;
            ans[left+1][2] = c;
            ans[left+2][2] = c;
            left += 3;
        } else {
            ans[left2][0] = c;
            ans[left2][1] = c;
            ans[left2][2] = c;
            left2++;
        }
    }

    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < n; i++) {
            if (ans[i][j] == 0) {
                ans[i][j] = p[1][1].back();
                p[1][1].pop_back();
            }
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
