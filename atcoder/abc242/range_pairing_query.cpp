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
#define MAXN 100010
#define MAXQ 1000010

using namespace std;

constexpr int BLOCK = 350;

int n, q;
int a[MAXN];

int cur_ans;
int cnt[MAXN];

int ans[MAXQ];
vector<array<int, 3>> qry[MAXN / BLOCK + 5];

int l = 0;
int r = 0;

void move_l(int d) {
    // move to the right
    while (l < d) {
        if (cnt[a[l]] % 2 == 0) {
            cur_ans--;
        }

        cnt[a[l]]--;
        l++;
    }

    // move to the left
    while (l > d) {
        cnt[a[l - 1]]++;
        if (cnt[a[l - 1]] % 2 == 0) {
            cur_ans++;
        }

        l--;
    }
}

void move_r(int d) {
    // move to the right
    while (r < d) {
        cnt[a[r]]++;
        if (cnt[a[r]] % 2 == 0) {
            cur_ans++;
        }

        r++;
    }

    // move to the left
    while (r > d) {
        if (cnt[a[r - 1]] % 2 == 0) {
            cur_ans--;
        }

        cnt[a[r - 1]]--;
        r--;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        array<int, 3> qr;
        cin >> qr[0] >> qr[1];

        qr[0]--;
        qr[2] = i;
        qry[qr[0] / BLOCK].push_back(qr);
    }

    for (auto &v : qry) {
        sort(v.begin(),  v.end(), [](const auto &a, const auto &b) {
            return a[1] < b[1];
        });
    }

    for (const auto &v : qry) {
        for (auto &[x, y, i] : v) {
            move_l(x);
            move_r(y);
            ans[i] = cur_ans;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
