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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

bool cmp(const string &a, const string &b) {
    if (a.size() > b.size()) return true;
    if (b.size() > a.size()) return false;

    for (int i = 0; i < (int)(a.size()); i++) {
        if (a[i] > b[i]) {
            return true;
        } else if (a[i] < b[i]) {
            return false;
        }
    }

    return false;
}

string add(string s) {
    reverse(s.begin(), s.end());
    int carry = 1;
    for (int i = 0; i < (int)(s.size()); i++) {
        s[i] += carry;
        if (s[i] > '9') {
            s[i] = '0';
            carry = 1;
        } else {
            carry = 0;
        }
    }

    if (carry) s += '1';
    reverse(s.begin(), s.end());
    return s;
}

bool check_substr(const string &a, const string &b) {
    if (a.size() < b.size()) return false;
    for (int i = 0; i < (int)(b.size()); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n; cin >> n;
    vector<string> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    string cur = nums[0];
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (nums[i].size() > cur.size()) {
            cur = nums[i];
        } else {
            if (cmp(nums[i], cur.substr(0, nums[i].size()))) {
                ans += cur.size() - nums[i].size();
                while (nums[i].size() < cur.size()) {
                    nums[i] += '0';
                }
                cur = nums[i];
            } else if (cmp(cur.substr(0, nums[i].size()), nums[i])) {
                ans += 1 + cur.size() - nums[i].size();
                while (nums[i].size() < cur.size() + 1) {
                    nums[i] += '0';
                }
                cur = nums[i];
            } else {
                auto res = add(cur);
                if (check_substr(res, nums[i])) {
                    ans += res.size() - nums[i].size();
                    cur = res;
                } else {
                    ans += 1 + cur.size() - nums[i].size();
                    while (nums[i].size() < cur.size() + 1) {
                        nums[i] += '0';
                    }
                    cur = nums[i];
                }
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
