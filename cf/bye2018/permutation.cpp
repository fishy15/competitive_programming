#include <iostream>

#define ll long long
#define MOD 998244353 

using namespace std;

ll facts[100001];

void calcFact() {
    ll cur = 1;
    for (int i = 1; i <= 1000000; i++) {
        cur *= i;
        cur %= MOD;
        if (i % 10 == 0) {
            facts[i / 10] = cur;
        }
    }
}

ll getMod(int n) {
    if (n % 10 == 0) {
        return facts[n / 10];
    }

    ll val = facts[n / 10];
    for (ll i = n - n%10 + 1; i <= n; i++) {
        val *= i;
        val %= MOD;
    }

    return val;
}

ll calc(ll n) {
    if (n == 1) {
        return 1;
    }

    ll val1 = getMod(n - 1);
    ll val2 = calc(n - 1);
    //cout << "num: " << n << endl;
    //cout << "val1: " << val1 << endl;
    //cout << "val2: " << val2 << endl;
    return (val1 + val2 - 1) * n % MOD;
}

int main() {
    calcFact();
    int n; cin >> n;
    cout << calc(n) << '\n';
}

