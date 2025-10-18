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
    vector<int> a;
    int ans;
    
    static testcase read() {
        int n;
        cin >> n;

        vector<int> a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }

        return testcase{n, a};
    }

    void solve() {
        ans = 0;
        rep(i, 0, n-1) {
            ans = max(ans, abs(a[i+1]-a[i]));
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
