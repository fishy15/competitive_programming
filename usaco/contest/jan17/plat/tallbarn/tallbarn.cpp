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

ll n, k; 
vector<ll> nums;

ll need(double bound) {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        double sq = sqrt(1 + 4.0 * nums[i] / bound);
        ans += ceil((-1 + sq) / 2);
    }

    return ans;
}

double calc(double val) {
    double ans = 0;
    for (int i = 0; i < n; i++) {
        double sq = sqrt(1 + 4.0 * nums[i] / val);
        double c = ceil((-1 + sq) / 2);
        ans += nums[i] / c;
    }

    return ans;
}

int main() {
    ifstream fin("tallbarn.in");
    ofstream fout("tallbarn.out");

    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        ll x; fin >> x;
        nums.push_back(x);
    }

    double l = 0;
    double r = 1e12;
    double ans = -1;

    for (int i = 0; i < 200; i++) {
        double mid = l + (r - l) / 2;
        /* cout << mid << '\n'; */
        ll nn = need(mid);
        if (nn <= k) {
            ans = mid;
            r = mid;
        } else {
            l = mid;
        }
    }

    fout << (ll)round(calc(ans)) << '\n';

    return 0;
}
