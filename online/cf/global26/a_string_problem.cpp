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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

vector<int> prefix(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

// 1. how to turn into a binary string
// 2. once it is a binary string, how do you solve? check every divisor of (# of bs)
// figure out left <= k1, right <= k2, left + right <= k2

// gap size between consecutive appearances of "b"
ll solve_binary(const vector<int> &gaps) {
    int n = gaps.size();
    int cnt = n - 1;

    auto process_len = [&](int k) -> ll {
        vector<int> in_between;
        int left = gaps[0];
        int right = gaps[n-1];
        int between = INF;

        for (int group = 0; group * k < cnt; group++) {
            for (int j = 0; j < k-1; j++) {
                auto idx = group*k + j + 1;
                if ((int) in_between.size() <= j) {
                    in_between.push_back(gaps[idx]);
                } else if (gaps[idx] != in_between[j]) {
                    return 0;
                }
            }
        }

        for (int group = 1; group * k < cnt; group++) {
            auto idx = group*k;
            ckmin(between, gaps[idx]);
        }

        ll ans = 0;
        for (int l = 0; l <= left; l++) {
            int right_end = min(right, between - l);
            if (right_end >= 0) {
                ans += right_end + 1;
            }
        }
        
        return ans;
    };

    ll ans = 0;
    for (int d = 1; d <= cnt; d++) {
        if (cnt % d == 0) {
            ans += process_len(d);
        }
    }

    return ans;
}

optional<vector<int>> create_gaps(string s, string sub) {
    auto pi = prefix(sub + "#" + s);
    int n = s.size();
    int len = sub.size();

    vector<int> gaps;
    int i = 0;
    int cur = 0;
    while (i < n) {
        if (i + len <= n && pi[i + 2*len] == len) {
            gaps.push_back(cur);
            cur = 0;
            i += len;
        } else if (s[i] == 'a') {
            cur++;
            i++;
        } else {
            return optional<vector<int>>{};
        }
    }

    gaps.push_back(cur);
    return gaps;
}

ll solve(string s) {
    int n = s.size();
    if (all_of(s.begin(), s.end(), [](char c) { return c == 'a'; })) {
        return n - 1;
    }

    array<int, 26> tot_cnts{};
    for (char c : s) {
        tot_cnts[c - 'a']++;
    }

    array<int, 26> cnt{};

    string sub;
    optional<vector<int>> gaps;
    for (char c : s) {
        if (c == 'a') {
            if (!sub.empty()) sub += 'a';
        } else {
            sub += c;
            cnt[c - 'a']++;

            bool ok = true;
            int want = -1;
            for (int i = 1; i < 26; i++) {
                if (tot_cnts[i]) {
                    if (cnt[i] == 0 || tot_cnts[i] % cnt[i] != 0) {
                        ok = false;
                        break;
                    } else {
                        int got = tot_cnts[i] / cnt[i];
                        if (want == -1) {
                            want = got;
                        } else if (want != got) {
                            ok = false;
                            break;
                        }
                    }
                }
            }

            if (ok) {
                auto res = create_gaps(s, sub);
                if (res) {
                    gaps = res;
                    goto done;
                }
            }
        }
    }

done:
    return solve_binary(*gaps);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        auto ans = solve(s);
        cout << ans << '\n';
    }

    return 0;
}
