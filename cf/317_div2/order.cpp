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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, s;
map<int, int> buy;
map<int, int> sell;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        char t; int p, q;
        cin >> t >> p >> q;
        if (t == 'B') {
            buy[p] += q;
        } else {
            sell[p] += q;
        }
    }

    int cnt = 0;
    vector<pair<int, int>> s1;
    for (auto it = sell.begin(); it != sell.end(); it++) {
        if (cnt == s) break;
        s1.push_back(*it);
        cnt++;
    }

    cnt = 0;
    vector<pair<int, int>> b1;
    for (auto it = buy.rbegin(); it!= buy.rend(); it++) {
        if (cnt == s) break;
        b1.push_back(*it);
        cnt++;
    }

    sort(s1.rbegin(), s1.rend());

    for (auto p : s1) {
        cout << "S " << p.first << ' ' << p.second << '\n';
    }

    for (auto p : b1) {
        cout << "B " << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
