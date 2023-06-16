/*
 * First, let's consider the case where L = 1. If R is a power of 2, then we can have a starting node (1), an 
 * ending node (n), and nodes representing powers of 2 (from 2^0 to 2^(n - 3)). We can then connect each power
 * to each of the smaller powers of 2 with a length equal to that power. This specifically enumerates all of
 * the paths from 1 to 2^(n - 2). For dealing with non-powers of 2, the final node can only connect to 
 * the nodes that have 1 in the binary representation of R, and the weight of the path is the sum of all of 
 * the higher powers of 2 that are in the binary representation of R. Finally, if L > 1, then we can include
 * one final node and path of length L - 1.
 */

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

int l, r;
int d;
vector<array<int, 3>> ans;
int n;

void solve(int d) {
    int p = 0;
    while ((1 << p) < d) p++;
    ans.push_back({1, p + 2, 1});
    for (int i = 0; i < p; i++) {
        int loc = p + 1 - i;
        ans.push_back({1, loc, 1});
        if ((1 << (i + 1)) <= d) {
            for (int nxt = loc + 1; nxt <= p + 2; nxt++) {
                ans.push_back({loc, nxt, 1 << i});
            }
        } else {
            int s = 1 << i;
            for (int j = i - 1; j >= 0; j--) {
                if ((1 << j) & d) {
                    ans.push_back({loc, p + 1 - j, s - (1 << j)});
                    s += 1 << j;
                }
            }
        }
    }
    n = p + 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> l >> r;
    int d = r - l + 1;
    solve(d);

    if (l > 1) {
        ans.push_back({n, n + 1, l - 1});
        n++;
    }

    cout << "YES\n";
    cout << n << ' ' << ans.size() << '\n';
    for (auto [a, b, c] : ans) {
        cout << a << ' ' << b << ' ' << c << '\n';
    }

    return 0;
}
