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

int cnt;
set<int> a, b, c, d;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 0; i < 8; i++) {
        string s; cin >> s;
        for (int j = 0; j < 8; j++) {
            if (s[j] == '*') {
                cnt++;
                a.insert(i);
                b.insert(j);
                c.insert(i + j);
                d.insert(i - j);
            }
        }
    }

    if (cnt == 8 && a.size() == 8 && b.size() == 8 && c.size() == 8 && d.size() == 8) {
        cout << "valid\n";
    } else {
        cout << "invalid\n";
    }

    return 0;
}
