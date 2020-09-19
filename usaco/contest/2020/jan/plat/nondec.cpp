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
#define MAXN 5000

using namespace std;

int n, k;
int nums[MAXN];
ll st[4 * MAXN][20][20];

struct s {
    ll arr[20][20];
};

void build(int v, int l, int r) {
    if (l == r) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                st[v][i][j] = 0;
            }
        }
        st[v][nums[l]][nums[l]] = 1;
        return;
    }

    int mid = l + (r - l) / 2;
    build(2 * v, l, mid);
    build(2 * v + 1, mid + 1, r);

    for (int lo = 0; lo < k; lo++) {
        for (int hi = lo; hi < k; hi++) {
            for (int m = lo; m <= hi; m++) {
                for (int m2 = m; m2 <= hi; m2++) {
                    st[v][lo][hi] += st[2 * v][lo][m] * st[2 * v + 1][m2][hi];
                    st[v][lo][hi] %= MOD;
                }
            }

            st[v][lo][hi] += st[2 * v][lo][hi];
            if (st[v][lo][hi] > MOD) st[v][lo][hi] -= MOD;
            st[v][lo][hi] += st[2 * v + 1][lo][hi];
            if (st[v][lo][hi] > MOD) st[v][lo][hi] -= MOD;
        }
    }
}

s query(int v, int x, int y, int l, int r) {
    s ans;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            ans.arr[i][j] = 0;
        }
    }

    if (x <= l && r <= y) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                ans.arr[i][j] = st[v][i][j];
            }
        }

        return ans;
    }

    if (r < x || l > y) {
        return ans;
    }

    int mid = l + (r - l) / 2;
    s left = query(2 * v, x, y, l, mid);
    s right = query(2 * v + 1, x, y, mid + 1, r);

    for (int lo = 0; lo < k; lo++) {
        for (int hi = lo; hi < k; hi++) {
            for (int m = lo; m <= hi; m++) {
                for (int m2 = m; m2 <= hi; m2++) {
                    ans.arr[lo][hi] += left.arr[lo][m] * right.arr[m2][hi];
                    ans.arr[lo][hi] %= MOD;
                }
            }

            ans.arr[lo][hi] += left.arr[lo][hi];
            if (ans.arr[lo][hi] > MOD) st[v][lo][hi] -= MOD;
            ans.arr[lo][hi] += right.arr[lo][hi];
            if (ans.arr[lo][hi] > MOD) st[v][lo][hi] -= MOD;
        }
    }

    return ans;
}

int main() {
    ifstream fin("nondec.in");
    ofstream fout("nondec.out");

    fin >> n >> k;

    for (int i = 0; i < n; i++) {
        fin >> nums[i];
        nums[i]--;
    }

    build(1, 0, n - 1);

    int q; fin >> q;
    for (int i = 0; i < q; i++) {
        ll ans = 0;
        int l, r; fin >> l >> r;
        s ss = query(1, l - 1, r - 1, 0, n - 1);
        for (int lo = 0; lo < k; lo++) {
            for (int hi = lo; hi < k; hi++) {
                ans += ss.arr[lo][hi];
                if (ans > MOD) ans -= MOD;
            }
        }
        fout << ans + 1 << '\n';
    }

    return 0;
}
