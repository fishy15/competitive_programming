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

#define ll unsigned long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000

using namespace std;

using u64 = unsigned long long;

u64 flip(u64 x) {
    char repr[8];
    memcpy(repr, &x, 8);

    reverse(begin(repr), end(repr));

    u64 ans;
    memcpy(&ans, repr, 8);
    return ans;
}

u64 pad(u64 x) {
    // xxxxxxx1 ... xxxxxxx0
    // so we need to shift every bit up by 1
    // and then top 7 bits up by 1
    x = x << 1;

    auto mask_bottom = (1ull << (8 * 7)) - 1;
    auto mask_top = ~mask_bottom;
    x = (x & mask_bottom) | ((x & mask_top) << 1);
    x ^= 1ull << 56;

    return x;
}

u64 fix(u64 x) {
    if ((x & 1) != 0) {
        return flip(x);
    }
    return x;
}

u64 unpad(u64 x) {
    auto mask_bottom = (1ull << (8 * 7)) - 1;
    auto mask_top = ~mask_bottom;

    x ^= 1ull << 56; // unset the bit
    x = (x & mask_bottom) | ((x & mask_top) >> 1);

    x = x >> 1;
    return x;
}

vector<u64> encode(int n, vector<u64> nums) {
    vector<int> lowest_bit(n);

    for (int i = 0; i < n; i++) {
        auto differ_from_flip = nums[i] ^ flip(nums[i]);
        if (differ_from_flip != 0) {
            auto lsb = differ_from_flip & -differ_from_flip;
            if (lsb & nums[i]) {
                lowest_bit[i] = 1;
            }
        }
    }

    vector<u64> output(MAXN + 24);
    for (int i = 0; i < n; i++) {
        output[i] = nums[i];
    }

    output[MAXN] = pad(n);
    for (int i = 0; i < n; i += 62) {
        u64 num = 0;
        for (int j = 0; i + j < min(n, i+62); j++) {
            if (lowest_bit[i + j]) {
                num ^= 1ull << j;
            }
        }
        output[MAXN+1+i/62] = pad(num);
    }

    return output;
}

vector<u64> decode(int n, vector<u64> nums) {
    n = unpad(fix(nums[MAXN]));

    vector<int> lowest_bit(n);
    for (int i = 0; i < n; i += 62) {
        u64 num = unpad(fix(nums[MAXN+1+i/62]));
        for (int j = 0; i + j < min(n, i+62); j++) {
            if (num & (1ull << j)) {
                lowest_bit[i + j] = 1;
            }
        }
    }

    vector<u64> ans(n);
    for (int i = 0; i < n; i++) {
        auto differ_from_flip = nums[i] ^ flip(nums[i]);
        if (differ_from_flip != 0) {
            auto lsb = differ_from_flip & -differ_from_flip;
            if (((lsb & nums[i]) > 0) != lowest_bit[i] == 1) {
                ans[i] = flip(nums[i]);
            } else {
                ans[i] = nums[i];
            }
        } else {
            ans[i] = nums[i];
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string typ;
    cin >> typ;

    int n;
    cin >> n;

    /*
    int seed = 0;
    while (true) {
        cout << seed << endl;

        vector<u64> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = rand();
        }

        auto res = encode(n, nums);
        for (auto &x : res) {
            if (rand() % 2) {
                x = flip(x);
            }
        }

        auto res2 = decode(res.size(), res);
        if (nums != res2) {
            cout << "broke :(\n";
            break;
        }

        seed++;
    }
    */

    vector<u64> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    vector<u64> res;
    if (typ == "encode") {
        res = encode(n, nums);
    } else {
        res = decode(n, nums);
    }

    if (typ == "encode") cout << res.size() << '\n';
    for (auto x : res) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
