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

int factor(int n) {
    int ans = 1;
    if (n % 2 == 0) {
        int cnt = 0;
        while (n % 2 == 0) {
            cnt++;
            n /= 2;
        }
        
        ans *= (cnt + 1);
    }

    for (int i = 3; i <= sqrt(n); i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }

            ans *= (cnt + 1);
        }
    }

    if (n != 1) {
        ans *= 2;
    }

    return ans;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        cout << factor(n) << '\n';
    }

    return 0;
}
