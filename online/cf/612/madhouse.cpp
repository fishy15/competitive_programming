/*
 * For the first subtask, we can query [1, n] and [2, n]. After doing each query, we can store the counts
 * of each letter in each substring returned. Then, we can remove the corresponding count in the first query
 * for each substring in the second query. The remaining queries are counts for prefixes of various lengths,
 * so we can build the string using that. This fits within the (n + 1)^2 limit, but not the 0.777(n + 1)^2.
 * limit for the second subtask.
 *
 * For the second subtask, we use the strategy from the previous part to solve the first half of the string.
 * We also query [1, n] to get information for the entire string. For an individual letter, we notice that
 * for some given length len < n / 2, it will be counted one more time over all of the substrings of length
 * len + 1 compared to the substrings of length len unless the letter is in the first len - 1 or last 
 * len - 1 numbers. Summing the counts for each length and taking the difference, we can compute the counts
 * for each letter within some range [i, n - i + 1] for various values of i. Using this information as well
 * as the first half computed earlier, we can restore the rest of the string. Overall, this fits within
 * 0.75(n + 1)^2, so this works for full points.
 */
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct response {
    int maxlen;
    vector<string> strs;
    vector<vector<array<int, 26>>> cnts;
    vector<array<int, 26>> tot_cnt;

    response(int n) : maxlen(n) {
        cnts.resize(n + 1);
        tot_cnt.resize(n + 1);
    }

    void add_cnt(int len, array<int, 26> &&cnt) {
        cnts[len].push_back(cnt);
        for (int i = 0; i < 26; i++) {
            tot_cnt[len][i] += cnt[i];
        }
    }

    void add_str(string &&s) {
        strs.push_back(s);
    }
};

response create_response(int l, int r) {
    int sz = (r - l + 2) * (r - l + 1) / 2;
    response res(r - l + 1);

    cout << "? " << l << ' ' << r << endl;

    for (int i = 0; i < sz; i++) {
        string s; cin >> s;
        if (s == "-") exit(0); // immediate quit

        int len = s.size();
        array<int, 26> cnt{};

        for (char c : s) {
            cnt[c - 'a']++;
        }

        res.add_cnt(len, move(cnt));
        res.add_str(move(s));
    }

    return res;
}

void answer(const string &s) {
    cout << "! " << s << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    if (n == 1) {
        auto res = create_response(1, 1);
        answer(res.strs[0]);
        return 0;
    }

    
    int half_round_up = (n + 1) / 2;
    auto half = create_response(1, half_round_up);
    string ans;

    if (n == 2) {
        ans = half.strs[0];
    } else {
        auto half_less = create_response(2, half_round_up);
        vector<array<int, 26>> best(half_round_up + 1, array<int, 26>{});
        for (int len = 1; len < half_round_up; len++) {
            for (auto &arr : half.cnts[len]) {
                auto cur = half.cnts[len];
                auto other = half_less.cnts[len];
                if (count(cur.begin(), cur.end(), arr) - count(other.begin(), other.end(), arr) == 1) {
                    best[len] = arr;
                    break;
                }
            }
        }

        best[half_round_up] = half.cnts[half_round_up][0];
        for (int i = 1; i <= half_round_up; i++) {
            for (int c = 0; c < 26; c++) {
                if (best[i][c] - best[i - 1][c] == 1) {
                    ans += ('a' + c);
                }
            }
        }
    }

    auto full = create_response(1, n);
    vector<array<int, 26>> cnt_within(n / 2 + 1); // cnt_within[i] = from [i, n - i - 1]
    for (int i = 0; i <= n / 2; i++) {
        for (int c = 0; c < 26; c++) {
            cnt_within[i][c] = full.tot_cnt[i + 1][c] - full.tot_cnt[i][c];
        }
    }

    for (int i = half_round_up; i < n; i++) {
        int rev = n - i - 1;
        for (int c = 0; c < 26; c++) {
            int diff = cnt_within[rev][c] - cnt_within[rev + 1][c];
            if (ans[rev] == ('a' + c)) diff--;
            if (diff == 1) ans += ('a' + c);
        }
    }

    answer(ans);

    return 0;
}
