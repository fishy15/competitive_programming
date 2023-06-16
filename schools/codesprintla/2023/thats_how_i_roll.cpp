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
#include <bitset>

#define ll long long
#define ld double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int l;
    cin >> l;

    bitset<26> one_char{};
    array<bitset<26>, 26> two_char{};

    for (int i = 0; i < l; i++) {
        string s;
        cin >> s;

        one_char[s[0] - 'a'] = true;
        if (s.size() > 1) {
            two_char[s[0] - 'a'][s[1] - 'a'] = true;
        }
    }
    
    bitset<26> cur_mask{};
    pair<ld, array<int, 6>> ans = {0, {0, 1, 2, 3, 4, 5}};

    auto calc = [&](const array<int, 6> &nums) {
        ld exp = 0;
        for (int i = 0; i < 6; i++) {
            if (one_char[nums[i]]) {
                auto cnt = (two_char[nums[i]] & cur_mask).count();
                exp += max<ld>(1, (ld) cnt / 3);
            }
        }

        exp /= 6;

        if (exp - ans.first > eps) {
            ans = {exp, nums};
        } else if (fabs(exp - ans.first) < eps && ans.second > nums) {
            ans.second = nums;
        }
    };

    array<int, 6> nums;

    auto add = [&](int x, int pos) {
        cur_mask[x] = true;
        nums[pos] = x;
    };

    auto rem = [&](int x, int pos) {
        cur_mask[x] = false;
    };

    for (int a = 0; a < 26; a++) {
        add(a, 0);
        for (int b = a + 1; b < 26; b++) {
            add(b, 1);
            for (int c = b + 1; c < 26; c++) {
                add(c, 2);
                for (int d = c + 1; d < 26; d++) {
                    add(d, 3);
                    for (int e = d + 1; e < 26; e++) {
                        add(e, 4);
                        for (int f = e + 1; f < 26; f++) {
                            add(f, 5);
                            calc(nums);
                            rem(f, 5);
                        }
                        rem(e, 4);
                    }
                    rem(d, 3);
                }
                rem(c, 2);
            }
            rem(b, 1);
        }
        rem(a, 0);
    }

    for (int x : ans.second) {
        cout << (char) (x + 'a');
    }
    cout << '\n';
    cout << ans.first << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    cout << fixed << setprecision(20);

    while (t--) {
        solve();
    }

    return 0;
}
