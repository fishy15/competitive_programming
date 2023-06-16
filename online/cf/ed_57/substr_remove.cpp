#include <iostream>
#include <string>

#define ll long long 
#define MOD 998244353 

using namespace std;

int main() {
    int sz; cin >> sz;
    string s; cin >> s;

    ll before = 0;
    ll after = 0;

    char first = s[0];
    int index = 0;
    while (s[index] == first) {
        index++;
        before++;
    }

    char last = s[sz - 1];
    index = sz - 1;
    while (s[index] == last) {
        index--;
        after++;
    }


    //cout << after << ' ' << before << '\n';
    if (first == last) {
        ll val = (before + 1) * (after + 1) % MOD;
        cout << val << '\n'; 
    } else {
        ll val = before + after + 1;
        val %= MOD;
        cout << val << '\n';
    }

    return 0;
}
