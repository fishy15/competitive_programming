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
#include <future>

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

struct testcase {
    int n, m;
    vector<ll> a;
    vector<ll> b;
    int ans;
    
    static testcase read() {
        int n, m;
        cin >> n >> m;

        vector<ll> a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }

        vector<ll> b(m);
        rep(i, 0, m) {
            cin >> b[i];
        }

        return testcase{n, m, a, b};
    }

    void solve() {
        ans = 0;

        map<ll, int> score_cnt;
        for (auto x : a) {
            score_cnt[x]++;
        }

        vector<int> scores;
        for (auto [_, c] : score_cnt) {
            scores.push_back(c);
        }

        sort(all(b));
        vector<ll> need(m + 1);

        auto check = [&](int start) {
            fill(all(need), 0);

            rep(i, start, sz(scores)) {
                if (i - start + 1 > m) {
                    return false;
                }
                need[i - start + 1] += scores[i];
            }

            for (int i = m - 1; i >= 0; i--) {
                need[i] += need[i + 1];
            }

            ll have = 0;
            for (int i = m; i > 0; i--) {
                have += b[i - 1];
                if (need[i] > have) {
                    return false;
                }
                have -= need[i];
            }

            return true;
        };

        int l = 0;
        int r = sz(scores);
        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m)) {
                r = m - 1;
                ans = accumulate(begin(scores) + m, end(scores), 0);
            } else {
                l = m + 1;
            }
        }
    }
};

vector<testcase> tests;

const int PARALLEL=8;
void paralleltests(int l=0, int r=PARALLEL-1) {
    if (l==r) {
        for(int i=l;i<(int)tests.size();i+=PARALLEL) {
            tests[i].solve();
        }
        return;
    }
    ll mid = (l+r)/2;
    auto handle = std::async(launch::async,paralleltests, l,mid);
    paralleltests(mid+1,r);
    handle.wait();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    rep(i, 0, t) {
        tests.push_back(testcase::read());
    }

    paralleltests();

    rep(i, 0, t) {
        cout << "Case #" << i + 1 << ": " << tests[i].ans << '\n';
    }

    return 0;
}
