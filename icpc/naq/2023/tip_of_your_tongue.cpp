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

struct mi {
    int v;
    mi(int _v) : v(_v) {
        if (v < 0) v += MOD;
        if (v >= MOD) v -= MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi &other) const { return mi(v + other.v); }
    mi operator*(const mi &other) const { return mi((ll) v * other.v); }
};


vector<int> get_hashes(const string &s) {
    mi cur = 0;
    vector<int> res;
    for (char c : s) {
        cur = cur * 31;
        cur = cur + (c - 'a');
        res.push_back(cur.v);
    }
    return res;
}

int h(const string &s) {
    mi cur = 0;
    for (char c : s) {
        cur = cur * 31;
        cur = cur + (c - 'a');
    }
    return cur.v;
}

struct info {
    map<int, int> pre_cnt;
    map<int, int> suf_cnt;
    map<ll, int> both_cnt;

    void add(int pre, int suf) {
        pre_cnt[pre]++;
        suf_cnt[suf]++;
        ll combo = (ll) pre * MOD + suf;
        both_cnt[combo]++;
    }

    int qand(int pre, int suf) {
        ll combo = (ll) pre * MOD + suf;
        return both_cnt[combo];
    }

    int qor(int pre, int suf) {
        ll combo = (ll) pre * MOD + suf;
        return pre_cnt[pre] + suf_cnt[suf] - both_cnt[combo];
    }

    int qxor(int pre, int suf) {
        ll combo = (ll) pre * MOD + suf;
        return pre_cnt[pre] + suf_cnt[suf] - 2 * both_cnt[combo];
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<info> ii(1'000'000 + 1);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        auto pre = get_hashes(s);
        reverse(s.begin(), s.end());
        auto suf = get_hashes(s);

        for (int j = 0; j < (int) pre.size(); j++) {
            ii[j + 1].add(pre[j], suf[j]);
        }
    }

    while (q--) {
        string s, a, b;
        cin >> s >> a >> b;
        reverse(b.begin(), b.end());

        auto pre = h(a);
        auto suf = h(b);
        auto &aa = ii[a.size()];
        int res;
        if (s == "AND") {
            res = aa.qand(pre, suf);
        } else if (s == "OR") {
            res = aa.qor(pre, suf);
        } else {
            res = aa.qxor(pre, suf);
        }
        cout << res << '\n';
    }

    return 0;
}
