#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

constexpr int INF = 1e9;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, w;
    cin >> n >> w;
    w++;

    vector<string> words(n);
    vector<int> lens(n);
    rep(i, 0, n) {
        cin >> words[i];
        lens[i] = sz(words[i]) + 1;
    }

    // uses i words
    vector dp(n+1, pair{INF, -1});

    auto check = [&](int lines) {
        fill(all(dp), pair{INF, -1});
        dp[0] = {0, -1};
        rep(i, 0, n) {
            int max_width = 0;
            if (dp[i].first > w) return false;
            rep(j, i+1, min(i+lines+1, n+1)) {
                max_width = max(max_width, lens[j-1]);
                ckmin(dp[j], {dp[i].first + max_width, i});
            }
        }
        return dp[n].first <= w;
    };

    int l = 1;
    int r = n;
    int ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            r = m - 1;
            ans = m;
        } else {
            l = m + 1;
        }
    }

    // rerun on the answer
    check(ans);

    vector<int> cols;
    vector<int> ends;
    int cur = n;
    int max_lines = 0;
    int width_used = 0;
    while (cur > 0) {
        auto [w2, p] = dp[cur];
        auto w1 = dp[p].first;
        auto diff = w2 - w1;
        max_lines = max(max_lines, cur - p);
        width_used += diff;
        cols.push_back(diff);
        ends.push_back(cur);
        cur = p;
    }

    width_used--;

    reverse(all(cols));
    reverse(all(ends));

    int cur_col = 0;
    int from_left = 0;
    int pos = 0;
    vector grid(max_lines, string(width_used, ' '));
    rep(i, 0, n) {
        if (i == ends[cur_col]) {
            from_left += cols[cur_col];
            pos = 0;
            cur_col++;
        }

        rep(j, 0, sz(words[i])) {
            grid[pos][from_left + j] = words[i][j];
        }
        pos++;
    }

    cout << max_lines << ' ' << sz(cols) << '\n';
    for (auto x : cols) {
        cout << x - 1 << ' ';
    }
    cout << '\n';
    for (const auto &s : grid) {
        cout << s << '\n';
    }

    return 0;
}

