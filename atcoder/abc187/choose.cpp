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
#define MAXN 200010

using namespace std;

int n;
int vote[MAXN][2];
vector<ll> benefit;
ll cur = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> vote[i][0] >> vote[i][1];
        cur -= vote[i][0];
        benefit.push_back(2LL * vote[i][0] + vote[i][1]);
    }

    sort(benefit.begin(), benefit.end(), greater<ll>());

    for (int i = 0; i < n; i++) {
        cur += benefit[i];
        if (cur > 0) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    return 0;
}
