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
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

template<typename F>
auto timeit(F f) {
    auto start = chrono::system_clock::now();
    f();
    auto end = chrono::system_clock::now();
    return end - start;
}

template<class F>
std::vector<int> smawck(F f, const std::vector<int> &rows, const std::vector<int> &cols) {
    std::vector<int> ans(rows.size(), -1);
    if((int) std::max(rows.size(), cols.size()) <= 2) {
        for(int i = 0; i < (int) rows.size(); i++) {
            for(auto j : cols) {
                if(ans[i] == -1 || f(rows[i], ans[i], j)) {
                    ans[i] = j;
                }
            }
        }
    } else if(rows.size() < cols.size()) {
        // reduce
        std::vector<int> st;
        for(int j : cols) {
            while(1) {
                if(st.empty()) {
                    st.push_back(j);
                    break;
                } else if(f(rows[(int) st.size() - 1], st.back(), j)) {
                    st.pop_back();
                } else if(st.size() < rows.size()) {
                    st.push_back(j);
                    break;
                } else {
                    break;
                }
            }
        }
        ans = smawck(f, rows, st);
    } else {
        std::vector<int> newRows;
        for(int i = 1; i < (int) rows.size(); i += 2) {
            newRows.push_back(rows[i]);
        }
        auto otherAns = smawck(f, newRows, cols);
        for(int i = 0; i < (int) newRows.size(); i++) {
            ans[2*i+1] = otherAns[i];
        }
        for(int i = 0, l = 0, r = 0; i < (int) rows.size(); i += 2) {
            if(i+1 == (int) rows.size()) r = (int) cols.size();
            while(r < (int) cols.size() && cols[r] <= ans[i+1]) r++;
            ans[i] = cols[l++];
            for(; l < r; l++) {
                if(f(rows[i], ans[i], cols[l])) {
                    ans[i] = cols[l];
                }
            }
            l--;
        }
    }
    return ans;
}

// max smawck
// F(i, j, k) checks if M[i][j] <= M[i][k]
// another interpretations is: 
// F(i, j, k) checks if M[i][k] is at least as good as M[i][j]
// higher == better
// when comparing 2 columns as vectors
// for j < k, column j can start better than column k
// as soon as column k is at least as good, it's always at least as good
template<class F>
std::vector<int> smawck(F f, int n, int m) {
    std::vector<int> rows(n), cols(m);
    for(int i = 0; i < n; i++) rows[i] = i;
    for(int i = 0; i < m; i++) cols[i] = i;
    return smawck(f, rows, cols);
}

template<class T>
std::vector<T> MaxConvolutionWithConvexShape(std::vector<T> anyShape, const std::vector<T> &convexShape) {
    if((int) convexShape.size() <= 1) return anyShape;
    if(anyShape.empty()) anyShape.push_back(0);
    int n = (int) anyShape.size(), m = (int) convexShape.size();
    auto function = [&](int i, int j) {
        return anyShape[j] + convexShape[i-j];
    };
    auto comparator = [&](int i, int j, int k) {
        if(i < k) return false;
        if(i - j >= m) return true;
        return function(i, j) >= function(i, k);
    };
    const std::vector<int> best = smawck(comparator, n + m - 1, n);
    std::vector<T> ans(n + m - 1);
    for(int i = 0; i < n + m - 1; i++) {
        ans[i] = function(i, best[i]);
    }
    return ans;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), b(m);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, m) {
        cin >> b[i];
    }

    vector<ll> popcnt(1 << m);
    rep(i, 1, 1<<m) {
        popcnt[i] = popcnt[i/2];
        if (i & 1) {
            popcnt[i]++;
        }
    }

    vector<vector<int>> masks(m+1);
    rep(i, 0, 1<<m) {
        ll cur = (1 << 30) - 1;
        rep(j, 0, m) {
            if (i & (1 << j)) {
                cur &= b[j];
            }
        }
        masks[popcnt[i]].push_back(cur);
    }

    for (auto &v : masks) {
        sort(all(v));
        v.erase(unique(all(v)), end(v));
    }

    vector<vector<ll>> best_arrs(n);
    chrono::nanoseconds inner = 0s;
    chrono::nanoseconds outer = 0s;
    rep(i, 0, n) {
        rep(j, 0, m+1) {
            int best = a[i];
            inner += timeit([&] {
                for (auto msk : masks[j]) {
                    ckmin(best, a[i] & msk);
                }
            });
            best_arrs[i].push_back(best);
        }
    }

    auto solve = [&](auto &&self, int l, int r) -> vector<ll> {
        vector<ll> res;
        if (l + 1 == r) {
            res = best_arrs[l];
        } else {
            int m = (l + r) / 2;
            auto left = self(self, l, m);
            auto right = self(self, m, r);
            res = MaxConvolutionWithConvexShape(left, right);
        }
        return res;
    };

    auto dp = solve(solve, 0, n);

    cout << dp[k] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
