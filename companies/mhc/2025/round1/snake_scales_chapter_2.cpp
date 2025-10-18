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
    int n;
    vector<ll> a;
    ll ans;
    
    static testcase read() {
        int n;
        cin >> n;

        vector<ll> a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }

        return testcase{n, a};
    }

    void solve() {
        ans = 0;

        // min cost to get onto the ground
        ll min_ground = INF;
        ll min_ladder = 0;
        rep(i, 0, n) {
            min_ground = min(min_ground, max(min_ladder, a[i]));
            if (i < n-1) {
                min_ladder = max(min_ladder, abs(a[i+1]-a[i]));
            }
        }

        ll l = min_ground;
        ll r = INFLL;

        vector<bool> vis(n);
        auto check = [&](ll h) {
            queue<int> q;
            fill(all(vis), false);

            rep(i, 0, n) {
                if (a[i] <= h) {
                    vis[i] = true;
                    q.push(i);
                }
            }

            int done = 0;
            while (!q.empty()) {
                auto v = q.front();
                q.pop();
                done++;

                if (v > 0 && !vis[v-1] && abs(a[v-1] - a[v]) <= h) {
                    vis[v-1] = true;
                    q.push(v-1);
                }

                if (v < n-1 && !vis[v+1] && abs(a[v+1] - a[v]) <= h) {
                    vis[v+1] = true;
                    q.push(v+1);
                }
            }

            return done == n;
        };

        while (l <= r) {
            auto m = l + (r - l) / 2;
            if (check(m)) {
                ans = m;
                r = m - 1;
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
        cout << "Case #" << i + 1 << ": ";
        cout << tests[i].ans << '\n';
    }

    return 0;
}
