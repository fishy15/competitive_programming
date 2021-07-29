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
#include <algorithm>
#include <utility>
#include <set>
#include <vector>

#define ll long long

using namespace std;

int n;
int nums[200001];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    int cur = nums[n - 1] + 1;
    for (int i = n - 1; i >= 0; i--) {
        //cout << cur << '\n';
        if (cur == 0) break;
        if (nums[i] < cur) {
            ans += nums[i];
            cur = nums[i];
        } else {
            ans += cur - 1;
            cur--;
        }
    }
    
    cout << ans << '\n';
}
