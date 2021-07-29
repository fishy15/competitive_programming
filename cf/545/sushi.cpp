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
// :pray: :vmaddur:
// :pray: :dorijanko:

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int n;
vector<int> nums;

int main() {
    cin >> n;
    int len = 0;
    int prev = 0;                                                                                                    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x != prev) {
            //cerr << len << endl;
            if (len != 0) nums.push_back(len);
            prev = x;
            len = 1;
        } else {
            len++;
        }
    }

    nums.push_back(len);
    int ans = 0;

    for (int i = 0; i < nums.size() - 1; i++) {
        int val = min(nums[i], nums[i + 1]) * 2;
        ans = val > ans ? val : ans;
    }

    cout << ans << '\n';
}

