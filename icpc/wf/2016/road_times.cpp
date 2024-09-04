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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

using vi = vector<int>;

typedef double T;
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
    int m, n;
    vi N, B;
    vvd D;

    LPSolver(const vvd& A, const vd& b, const vd& c) :
        m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
            rep(i,0,m) rep(j,0,n) D[i][j] = A[i][j];
            rep(i,0,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
            rep(j,0,n) { N[j] = j; D[m][j] = -c[j]; }
            N[n] = -1; D[m+1][n] = 1;
        }

    void pivot(int r, int s) {
        T *a = D[r].data(), inv = 1 / a[s];
        rep(i,0,m+2) if (i != r && abs(D[i][s]) > eps) {
            T *b = D[i].data(), inv2 = b[s] * inv;
            rep(j,0,n+2) b[j] -= a[j] * inv2;
            b[s] = a[s] * inv2;
        }
        rep(j,0,n+2) if (j != s) D[r][j] *= inv;
        rep(i,0,m+2) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool simplex(int phase) {
        int x = m + phase - 1;
        for (;;) {
            int s = -1;
            rep(j,0,n+1) if (N[j] != -phase) ltj(D[x]);
            if (D[x][s] >= -eps) return true;
            int r = -1;
            rep(i,0,m) {
                if (D[i][s] <= eps) continue;
                if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
                             < MP(D[r][n+1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    T solve(vd &x) {
        int r = 0;
        rep(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
        if (D[r][n+1] < -eps) {
            pivot(r, n);
            if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
            rep(i,0,m) if (B[i] == -1) {
                int s = 0;
                rep(j,1,n+1) ltj(D[i]);
                pivot(i, s);
            }
        }
        bool ok = simplex(1); x = vd(n);
        rep(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
        return ok ? D[m][n+1] : inf;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector d(n, vector(n, 0));
    vector<int> d_flat;
    vector<pair<int, int>> edges_ord;
    rep(i, 0, n) {
        rep(j, 0, n) {
            cin >> d[i][j];
            edges_ord.push_back({i, j});
            d_flat.push_back(d[i][j]);
        }
    }

    auto get_path = [&](int src, int dest) {
        vector<int> p(n, -1);
        vector<int> cur_d(n, INF);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});
        cur_d[src] = 0;

        while (!pq.empty()) {
            auto [dd, u] = pq.top();
            pq.pop();

            if (dd != cur_d[u]) {
                continue;
            }

            rep(v, 0, n) {
                if (d[u][v] != -1) {
                    auto nd = dd + d[u][v];
                    if (nd < cur_d[v]) {
                        cur_d[v] = nd;
                        p[v] = u;
                        pq.push({nd, v});
                    }
                }
            }
        }

        vector<int> edge_idxs;
        int cur = dest;
        while (cur != src) {
            auto e = pair{p[cur], cur}; 
            auto idx = p[cur] * n + cur;
            edge_idxs.push_back(idx);
            cur = p[cur];
        }

        return edge_idxs;
    };

    int vars = sz(edges_ord);
    vvd A;
    vd B;

    // construct restrictions on speed on each edge
    // variable is how much extra over the min peed limit we are
    int idx = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (d[i][j] != -1) {
                vd pos(vars, 0);
                pos[idx] = 1;

                A.push_back(pos);
                B.push_back(d[i][j]);
            }
            idx++;
        }
    }

    int r;
    cin >> r;

    rep(i, 0, r) {
        int s, d, t;
        cin >> s >> d >> t;

        auto edges = get_path(s, d);
        vd pos(vars, 0);
        vd neg(vars, 0);
        int sum_base = 0;
        for (auto x : edges) {
            pos[x] = 1;
            neg[x] = -1;
            sum_base += d_flat[x];
        }

        A.push_back(pos);
        B.push_back(t - sum_base);

        A.push_back(neg);
        B.push_back(-t + sum_base);
    }

    int q;
    cin >> q;

    cout << fixed << setprecision(15);


    while (q--) {
        int s, d;
        cin >> s >> d;

        auto edges = get_path(s, d);
        vd pos(vars, 0);
        vd neg(vars, 0);
        int sum_base = 0;
        for (auto x : edges) {
            pos[x] = 1;
            neg[x] = -1;
            sum_base += d_flat[x];
        }

        LPSolver for_max(A, B, pos);
        LPSolver for_min(A, B, neg);

        vd x1(sz(edges));
        vd x2(sz(edges));
        auto max_ans = for_max.solve(x1) + sum_base;
        auto min_ans = -for_min.solve(x2) + sum_base;

        cout << s << ' ' << d << ' ' << min_ans << ' ' << max_ans << '\n';
    }

    return 0;
}
