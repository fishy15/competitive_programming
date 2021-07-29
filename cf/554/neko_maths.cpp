// :pray: :fishy:

#include <iostream>
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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll a, b; cin >> a >> b;
    ll diff = abs(b - a);

    if (diff == 0) {
        cout << "0\n";
        return 0;
    }
    
    vector<int> factors;

    for (int i = 1; i <= sqrt(diff); i++) {
        if (diff % i == 0) {
            factors.push_back(i);
            factors.push_back(diff / i);
        }
    }
    
    ll min_k = INFLL;
    ll min_lcm = INFLL;
    for (int i = 0; i < (int)(factors.size()); i++) {
        ll k = (factors[i] - (a % factors[i])) % factors[i];
        ll lcm = (a + k) * (b + k) / factors[i];

        if (lcm == min_lcm) {
            min_k = min(min_k, k);
        } else if (lcm < min_lcm) {
            min_lcm = lcm;
            min_k = k;
        }
    }

    cout << min_k << '\n';

    return 0;
}
