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
#include <unordered_map>
#include "lang.h"
#include "grader.h"

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 70000

using namespace std;

// replace this back when submit
const int LEN = 100;
const int LANGS = 56;

struct hash_pair {
    template <class T, class U>
    size_t operator() (const pair<T, U> &p) const {
        auto h1 = p.first;
        auto h2 = p.second;
        return h1 + (1 << 16) * h2;
    }
};

using mm = unordered_map<pair<int, int>, int, hash_pair>;

struct val {
    int tot;
    mm freq;
    val() : tot(0) {}
    ld qry(const mm &f) {
        if (tot == 0) return INFLL;
        ld ans = 0;
        for (auto p : f) {
            ld actual_f = 1.0 * freq[p.first] / tot;
            ld given_f = 1.0 * p.second / LEN;
            ld val = fabs(actual_f - given_f) * 100;
            ans += val * val;
        }
        return ans;
    }
    void upd(int arr[LEN]) {
        tot += LEN;
        for (int i = 0; i < LEN - 1; i++) {
            freq[{arr[i], arr[i + 1]}]++;
        }
    }
};

val langs[LANGS];

void excerpt(int arr[LEN]) {
    ld min_val = INFLL;
    int ans = 0;
    mm cnt;
    for (int i = 0; i < LEN - 1; i++) {
        cnt[{arr[i], arr[i + 1]}]++;
    }
    for (int i = 0; i < LANGS; i++) {
        ld val = langs[i].qry(cnt);
        if (val < min_val) {
            min_val = val;
            ans = i;
        }
    }

    int correct = language(ans);
    langs[correct].upd(arr);
}
