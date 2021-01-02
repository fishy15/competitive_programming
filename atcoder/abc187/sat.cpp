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
vector<string> good;
set<string> bad;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (s[0] == '!') {
            bad.insert(s.substr(1, s.size() - 1));
        } else {
            good.push_back(s);
        }
    }

    for (string &s : good) {
        if (bad.count(s)) {
            cout << s << '\n';
            return 0;
        }
    }

    cout << "satisfiable\n";


    return 0;
}
