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
#define MAXN 1000000

using namespace std;

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

void solve() {
    int n;
    cin >> n;

    vector<int> step(n);
    for (int i = 0; i < n; i++) {
        cin >> step[i];
    }

    vector<bool> main_path(n);
    vector<int> main_ord;
    int cur = 0;
    bool self_loop = false;
    while (true) {
        main_path[cur] = true;
        main_ord.push_back(cur);
        cur += step[cur];

        if (cur < 0 || cur >= n) {
            break;
        } else if (main_path[cur]) {
            self_loop = true;
            break;
        }
    }

    vector<int> leads_to(n + 1);
    vector<bool> vis(n);

    auto get_escape = y_combinator([&](auto self, int x) -> int {
        if (!vis[x]) {
            // set for self-loop
            vis[x] = true;
            leads_to[x] = -1;
            
            auto nxt = x + step[x];
            if (nxt < 0 || nxt >= n) {
                leads_to[x] = n;
            } else if (main_path[nxt]) {
                leads_to[x] = nxt; 
            } else {
                leads_to[x] = self(nxt);
            }
        }

        return leads_to[x];
    });

    vector<int> count_leads_to(n + 1);

    for (int i = 0; i < n; i++) {
        auto dst = get_escape(i);
        if (dst != -1) {
            count_leads_to[dst]++;
        }
    }

    if (self_loop) {
        // n + 1 immediately escape
        int num_go = n + 1 + count(leads_to.begin(), leads_to.end(), n);
        int on_main_path = count(main_path.begin(), main_path.end(), true);
        cout << (ll) on_main_path * num_go << '\n';
    } else {
        int on_main_path = count(main_path.begin(), main_path.end(), true);

        // something else can change to anything
        ll ans = (ll) (n - on_main_path) * (2 * n + 1);

        int sz = main_ord.size();
        int swap_to = n + 1 + count_leads_to[n];
        for (int i = sz - 1; i >= 0; i--) {
            ans += swap_to - 1;
            swap_to += count_leads_to[main_ord[i]];
        }

        cout << ans << '\n';
    }
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
