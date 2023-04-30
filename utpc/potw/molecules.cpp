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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

using vi = vector<int>;
typedef vector<double> vd;
const double eps = 1e-12;
#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		double v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (fabs(b[j]) > eps) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,i+1,n) {
			double fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i) b[j] -= A[j][i] * b[i];
	}
	return rank; // (multiple solutions if rank < m)
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> pts(n);

    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }

    vector<vd> matrix(n, vd(n));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (pts[a].first == -1) matrix[a][b]++;
        if (pts[b].first == -1) matrix[b][a]++;
    }

    for (int i = 0; i < n; i++) {
        auto s = accumulate(all(matrix[i]), 0.0);
        if (s != 0) {
            for (auto &x : matrix[i]) {
                x /= s;
            }
        }

        if (pts[i].first == -1) {
            matrix[i][i] = -1;
        } else {
            matrix[i][i] = 1;
        }
    }

    auto copy1 = matrix;
    auto copy2 = matrix;

    vd x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = max(0, pts[i].first);
        y[i] = max(0, pts[i].second);
    }

    vd ans1(n), ans2(n);
    solveLinear(copy1, x, ans1);
    solveLinear(copy2, y, ans2);
    cout << fixed << setprecision(12);
    for (int i = 0; i < n; i++) {
        cout << fabs(ans1[i]) << ' ' << fabs(ans2[i]) << '\n';
    }

    return 0;
}
