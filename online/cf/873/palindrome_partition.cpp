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

struct eertree {
    constexpr static int sigma = 26;
     
    vector<int> s, len, link, even_cnt;
    vector<array<int, sigma>> to;
     
    int n, last, sz;
     
    eertree(int maxn) : s(maxn), len(maxn), link(maxn), even_cnt(maxn), to(maxn), n{}, last{}
    {
        s[n++] = -1;
        link[0] = 1;
        len[1] = -1;
        sz = 2;
    }
     
    int get_link(int v)
    {
        while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
        return v;
    }
     
    void add_letter(int c)
    {
        s[n++] = c;
        last = get_link(last);
        if(!to[last][c])
        {
            len[sz] = len[last] + 2;
            link[sz] = to[get_link(link[last])][c];
            even_cnt[sz] = even_cnt[link[sz]] + (1 - len[sz] % 2);
            to[last][c] = sz++;
        }
        last = to[last][c];
    }
};

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    eertree t(n + 10);
    for (auto c : s) {
        t.add_letter(c - 'a');
    }

    for (int i = 0; i < t.sz; i++) {
        cout << t.link[i] << ' ' << t.len[i] << ' ' << t.even_cnt[i] << '\n';
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
