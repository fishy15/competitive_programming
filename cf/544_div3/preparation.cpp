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
// :pray: :wayne:
// :pray: :wu:

#include <iostream>
#include <cmath>

using namespace std;

int nums[101];
int n, k;

int main() {
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[x % k]++;
    }
    
    int ans = 0;
    for (int i = 0; i < k; i++) {
        int rev = (k - i) % k;
        if (rev < i) break;
        if (rev == i) {
            ans += nums[i] / 2;
        } else {
            ans += min(nums[i], nums[rev]);
        }
    }
    
    cout << 2 * ans << '\n';
}