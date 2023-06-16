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

using namespace std;

int n;
int nums[200001];

int main() {
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    sort(nums, nums + n);
    
    int l = 0;
    int r = 0;
    int ans = 0;
    
    while (l < n) {
        while (r < n && nums[r] <= nums[l] + 5) r++;
        if (r - l > ans) {
            ans = r - l;
            //cout << l << ' ' << r << ' ' << r - l + 1 << '\n';
        }
        
        l++;
    }
    
    cout << ans << '\n';
}