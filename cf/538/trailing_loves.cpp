// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:

#include <iostream>
#include <vector>

#define ll long long

using namespace std;

vector<ll> primes;
vector<ll> nums;
vector<ll> count;

ll calcNum(ll n, ll b) {
    ll ans = 0;
    
    while (n > 0) {
        ans += n / b;
        n /= b;
    }
    
    return ans;
}

void factor(ll n) {
    if (n % 2 == 0) {
        primes.push_back(2);
        nums.push_back(1);
        
        n /= 2;
        while (n % 2 == 0 && n > 1) {
            n /= 2;
            nums[nums.size() - 1]++;
        }
    }
    
    ll cur = 3;
    while (n > 1) {
        if (n % cur == 0) {
            primes.push_back(cur);
            nums.push_back(1);
            
            n /= cur;
            while (n % cur == 0 && n > 0) {
                n /= cur;
                nums[nums.size() - 1]++;
            }
        }
        
        cur += 2;
    }
}

int main() {
    ll n, b; cin >> n >> b;
    ll ans = 0;

    ll min = 0x3f3f3f3f3f3f3f3f;
    
    for (ll i = 2; i <= b; i++) {
        if (i * i > b) {
            i = b;
        }
        
        int count = 0;
        while (b % i == 0) {
            count++;
            b /= i;
        }
        
        if (count == 0) {
            continue;
        }
        
        ll val = calcNum(n, i);
        if (val / count < min) {
            min = val / count;
        }
    }
    
    cout << min << '\n';
    return 0;
}