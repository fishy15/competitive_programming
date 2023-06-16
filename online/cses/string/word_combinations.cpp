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
#include <cstring>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

struct node {
    node *child[26];
    int cnt;
    node() : cnt(0) { memset(child, 0, sizeof child); }
};

node *trie = new node;
string word;
int n;
ll dp[MAXN];

void insert(const string &s) {
    int sz = (int)(s.size());
    node *cur = trie;
    for (int i = 0; i < sz; i++) {
        int c = s[i] - 'a';
        if (!cur->child[c]) cur->child[c] = new node;
        cur = cur->child[c];
    }
    cur->cnt++;
}

void inc(int x) {
    node *cur = trie;
    int i = 1;
    int sz = (int)(word.size());
    for (;;) {
        if (i + x > sz) break;
        int c = word[i + x - 1] - 'a';
        if (!cur->child[c]) break;
        cur = cur->child[c];
        dp[i + x] += dp[x] * cur->cnt % MOD;
        if (dp[i + x] >= MOD) dp[i + x] -= MOD;
        i++;
    }
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> word;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        insert(s);
    }

    dp[0] = 1;
    int sz = (int)(word.size());
    for (int i = 0; i < sz; i++) {
        inc(i);
    }

    cout << dp[sz] << '\n';

    return 0;
}
