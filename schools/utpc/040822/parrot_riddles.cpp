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

int p[] = {2, 4, 3, 9, 5, 25, 7, 49, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int cnt = 0;
    for (int x : p) {
        cout << "? " << x << endl;
        string res; cin >> res;
        if (res == "yes") {
            cnt++;
        }
    }

    cout << "! " << (cnt <= 1 ? "prime" : "composite") << endl;

    return 0;
}
