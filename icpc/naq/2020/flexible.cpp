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

int w, p;
int part[101];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> w >> p;
    for (int i = 1; i <= p; i++) {
        cin >> part[i];
    }
    part[p + 1] = w;

    set<int> ans;
    for (int i = 0; i <= p + 1; i++) {
        for (int j = i + 1; j <= p + 1; j++) {
            ans.insert(part[j] - part[i]);
        }
    }

    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
