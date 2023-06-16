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
#include "molecules.h"

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

vector<int> find_subset(int l, int u, vector<int> w) {
    int n = (int)(w.size());
    vector<pair<int, int>> pos;
    for (int i = 0; i < n; i++) {
        pos.push_back({w[i], i});
    }

    sort(pos.begin(), pos.end());
    ll cur = 0;
    int back = 0;
    int p = 0;

    vector<int> ans;
    while (p < n) {
        while (p < n && cur < l) {
            cur += pos[p++].first;
        }

        while (back < p && cur > u) {
            cur -= pos[back++].first;
        }

        if (l <= cur && cur <= u) {
            for (int i = back; i < p; i++) {
                ans.push_back(pos[i].second);
            }
            return ans;
        }
    }

    return ans;
}
