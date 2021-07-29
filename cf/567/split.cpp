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

int n;
string s;

vector<pair<int, int>> opt;

string sum(string a, string b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    while (a.size() < b.size()) a += '0';
    while (b.size() < a.size()) b += '0';

    string ans;
    int carry = 0;
    int sz = a.size();
    for (int i = 0; i < sz; i++) {
        int cur = a[i] + b[i] + carry - '0' - '0';
        ans += to_string(cur % 10);
        carry = cur / 10;
    }

    if (carry) ans += to_string(carry);
    reverse(ans.begin(), ans.end());
    return ans;
}

string cmp(string a, string b) {
    if (a.size() > b.size()) return b;
    if (a.size() < b.size()) return a;

    int sz = a.size();
    for (int i = 0; i < sz; i++) {
        if (a[i] < b[i]) {
            return a;
        } else if (a[i] > b[i]) {
            return b;
        }
    }

    return a;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> s;
    for (int i = 0; i < n - 1; i++) {
        if (s[i + 1] != '0') {
            opt.push_back({max(i + 1, n - i - 1), i});
        }
    }

    sort(opt.begin(), opt.end());

    string ans;
    for (auto [sz, pos] : opt) {
        if (sz > opt[0].first + 1) break;
        string a = s.substr(0, pos + 1);
        string b = s.substr(pos + 1, n - pos - 1);
        string res = sum(a, b);

        if (ans == "") {
            ans = res;
        } else {
            ans = cmp(ans, res);
        }
    }

    cout << ans << '\n';

    return 0;
}
