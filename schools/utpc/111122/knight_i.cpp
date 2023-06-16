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
#include <cassert>

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
	if (n) assert(sz(A[0]) == m);
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

int km(int a, int b, int x, int y) {
    return (abs(a - x) == 1 && abs(b - y) == 2) 
        || (abs(a - x) == 2 && abs(b - y) == 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, x, y;
    cin >> n >> x >> y;

    vector<vd> mat(n * n, vd(n * n));
    vd ans(n * n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == x && j == y) {
                int k1 = i * n + j;
                mat[k1][k1] = 1;
                ans[k1] = 0;
            } else {
                int k1 = i * n + j;
                mat[k1][k1] = 1;
                ld cnt = 0;
                for (int a = 0; a < n; a++) {
                    for (int b = 0; b < n; b++) {
                        if (km(i, j, a, b)) {
                            int k2 = a * n + b;
                            mat[k1][k2] = -1;
                            cnt++;
                        }
                    }
                }

                if (cnt != 0) {
                    for (int k = 0; k < n * n; k++) {
                        if (k != k1) {
                            mat[k1][k] /= cnt;
                        }
                    }
                }
            }
        }
    }

    auto mat2 = mat;

    vd qq(n * n);
    solveLinear(mat, ans, qq);
    
    ld tot = 0;
    ld cnt = 0;
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (km(x, y, a, b)) {
                tot += qq[a * n + b];
                cnt++;
            }
        }
    }


    cout << fixed << setprecision(12) << tot / cnt + 1 << '\n';

    return 0;
}
