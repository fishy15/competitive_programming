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
#define MAXN 200010

using namespace std;

int n, m;
int nums[MAXN];
int med[MAXN];
int medpone[MAXN];

struct bit {
    int n;
    vector<int> b;
    bit(int n) : n(n + 10) {
        b = vector<int>(n + 10);
    }
    void upd(int x, int v) {
        x++;
        while (x && x < n) {
            b[x] += v;
            x += x & -x;
        }
    }
    int qry(int x) {
        int res = 0;
        x++;
        while (x) {
            res += b[x];
            x -= x & -x;
        }
        return res;
    }
};

void calc(int mid, int* arr) {
    vector<int> cnt(n + 1);
    vector<pair<int, int>> pt = {{0, 0}};
    bit b(n + 1);
    for (int i = 0; i < n; i++) {
        cnt[i + 1] += cnt[i];
        if (nums[i] < mid) cnt[i + 1]++;
        pt.push_back({2 * cnt[i + 1] - i - 1, i + 1});
    }
    sort(pt.begin(), pt.end());
    for (auto p : pt) {
        arr[p.second] = b.qry(p.second);
        b.upd(p.second, 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    calc(m, med);
    calc(m + 1, medpone);

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += medpone[i] - med[i];
    }
    cout << ans << '\n';

    return 0;
}
