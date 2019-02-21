#include <iostream>
#include <vector>

#define ll long long 

using namespace std;

ll find(ll, ll);

int main() {
    ll n, k; cin >> n >> k;
    if (n == 1 && k == 1) {
        cout << "2\n";
        return 0;
    }

    cout << find(n, k) << '\n';
    return 0;
}

ll find(ll n, ll k) {
    if (n == 1) {
        return (1 << k) - 1;
    }

    ll maxExpBelow = 0;

    while ((1 << maxExpBelow) <= n) {
        maxExpBelow++;
    }
    maxExpBelow--;
    
    ll checkVal = 1;
    checkVal <<= k;
    checkVal -= 1;
    checkVal <<= maxExpBelow - k + 1;
    //cout << maxExpBelow << endl;
    //cout << checkVal << endl;
    if (checkVal <= n) {
        //cout << ((1 << (maxExpBelow + 1)) + (1 << (k - 1)) - 1) << '\n';
        return (1 << (maxExpBelow + 1)) + (1 << (k - 1)) - 1;    
    }

    int newVal = 1 << maxExpBelow;
    return newVal + find(n - newVal, k - 1);
}
