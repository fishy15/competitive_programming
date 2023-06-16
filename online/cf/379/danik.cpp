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

    int n; 
    string s;
    cin >> n;
    cin >> s;
    int x = 0;

    for (char c : s) {
        if (c == 'A') {
            x++;
        }
    }

    if (x > n - x) {
        cout << "Anton\n";
    } else if (x == n - x) {
        cout << "Friendship\n";
    } else {
        cout << "Danik\n";
    }

    return 0;
}
