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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    vector<string> cur = {"0", "1"};
    for (int i = 2; i <= n; i++) {
        vector<string> nxt;
        for (string s : cur) {
            nxt.push_back("0" + s);
        }
        for (auto it = cur.rbegin(); it != cur.rend(); it++) {
            nxt.push_back("1" + *it);
        }
        cur.swap(nxt);
    }

    for (string s : cur) {
        cout << s << '\n';
    }

    return 0;
}
