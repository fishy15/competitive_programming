#include <iostream>
#include <cmath>
#include <set>

#define ll long long 

using namespace std;

int main() {
    int n; cin >> n;
    set<ll> ans;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ll num = n / i; 
            ans.insert((num - 1) * (num) / 2 * i + num);

            if (i * i != n) {
                ll num2 = i;
                ll i2 = n / i;
                ans.insert((num2 - 1) * (num2) / 2 * i2 + num2);
            }
        }
    }

    for (ll i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}
