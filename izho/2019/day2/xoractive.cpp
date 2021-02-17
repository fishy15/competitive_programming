/* 
 * We can ask for the first number. For the rest of the numbers, we can iterate through the bits and 
 * only include an index in get_pairwise_xor if there is a 1 in that position. We can ask this query twice,
 * once with index 1 and once without. The numbers that appear in the former but not the latter are the
 * result of the first index xor another index. Therefore, for each value, we know the bits that are marked
 * 1 in the index, which we can sum to get the index.
 */

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

#include "interactive.h"

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<int> guess(int n) {
    int one = ask(1);

    map<int, int> ans_m;
    for (int j = 0; j < 7; j++) {
        vector<int> cur;
        for (int i = 1; i < n; i++) {
            if ((i >> j) & 1) {
                cur.push_back(i + 1);
            }
        }

        if (cur.empty()) continue;
        auto set1 = get_pairwise_xor(cur);
        cur.push_back(1);
        auto set2 = get_pairwise_xor(cur);

        map<int, int> cnt;
        for (int i : set2) {
            if (i) {
                cnt[i ^ one]++;
            }
        }
        for (int i : set1) {
            if (i) {
                cnt[i ^ one]--;
            }
        }

        for (auto p : cnt) {
            if (p.second) {
                ans_m[p.first] += (1 << j);
            }
        }
    }

    vector<int> ans(n);
    ans[0] = one;
    for (auto p : ans_m) {
        ans[p.second] = p.first;
    }

    return ans;
}
