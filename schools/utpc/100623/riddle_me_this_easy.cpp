#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<int, int> cnts;
    int bad = 0;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;

        vector<int> nums(s);
        for (auto &x : nums) {
            cin >> x;
        }

        vector<int> wanted(s);
        iota(wanted.begin(), wanted.end(), 1);
        int ans = -1;
        for (int i = 0; i < s; i++) {
            if (nums == wanted) {
                ans = i;
                break;
            }

            rotate(nums.begin(), nums.begin() + 1, nums.end());
        }

        if (ans != -1) {
            cnts[ans]++;
        } else {
            bad++;
        }
    }

    int leftover = 0;
    int tot = 0;
    for (auto [_, c] : cnts) {
        tot += c / 2 * 2;
        if (c % 2 == 1) {
            leftover++;
        }
    }

    int wbad = min(bad, leftover);
    tot += wbad;
    leftover -= wbad;
    tot += leftover / 2;
    cout << tot << '\n';

    return 0;
}
