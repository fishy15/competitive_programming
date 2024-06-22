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

auto up(const string &s) { return s.substr(0, 2); }
auto right(const string &s) { return s.substr(2, 2); }
auto down(const string &s) { return s.substr(4, 2); }
auto left(const string &s) { return s.substr(6, 2); }

vector<string> gen(const string &s) {
    string a = s.substr(0, 2);
    string b = s.substr(2, 2);
    string c = s.substr(4, 2);
    string d = s.substr(6, 2);

    return {
        a+b+c+d,
        b+c+d+a,
        c+d+a+b,
        d+a+b+c,
        d+c+b+a,
        c+b+a+d,
        b+a+d+c,
        a+d+c+b,
    };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> words;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (auto w : gen(s)) {
            words.push_back(w);
        }
    }

    sort(words.begin(), words.end());
    words.erase(unique(words.begin(), words.end()), words.end());

    int sz = words.size();

    // [n+0, n+26) = up/right square is +, down/left square is -
    // [n+26, n+52) = up/right square is -, down/left square is +
    vector<vector<int>> adj(sz + 52);

    for (int i = 0; i < sz; i++) {
        const auto &w = words[i];

        if (down(w)[1] == '+') {
            adj[i].push_back(sz + down(w)[0] - 'A');
        } else if (down(w)[1] == '-') {
            adj[i].push_back(sz + down(w)[0] - 'A' + 26);
        }
        if (left(w)[1] == '+') {
            adj[i].push_back(sz + left(w)[0] - 'A');
        } else if (left(w)[1] == '-') {
            adj[i].push_back(sz + left(w)[0] - 'A' + 26);
        }

        if (up(w)[1] == '-') {
            adj[sz + up(w)[0] - 'A'].push_back(i);
        } else if (up(w)[1] == '+') {
            adj[sz + up(w)[0] - 'A' + 26].push_back(i);
        }
        if (right(w)[1] == '-') {
            adj[sz + right(w)[0] - 'A'].push_back(i);
        } else if (right(w)[1] == '+') {
            adj[sz + right(w)[0] - 'A' + 26].push_back(i);
        }
    }

    /*
    for (int i = 0; i < sz + 52; i++) {
        if (!adj[i].empty()) {
            cout << "node " << i << endl;
            if (i < sz) cout << words[i] << endl;
            for (auto x : adj[i]) {
                cout << "\tto" << x << endl;
            }
        }
    }
    */

    vector<int> state(sz+52);
    bool ans = false;

    auto dfs = [&](auto &&self, int v) -> void {
        state[v] = 1;
        for (auto e : adj[v]) {
            if (state[e] == 0) {
                self(self, e);
                if (ans) return;
            } else if (state[e] == 1) {
                ans = true;
                return;
            }
        }
        state[v] = 2;
    };

    for (int i = 0; i < sz + 52; i++) {
        if (state[i] == 0) {
            dfs(dfs, i);
        }
    }

    if (ans) {
        cout << "unbounded\n";
    } else {
        cout << "bounded\n";
    }

    return 0;
}
