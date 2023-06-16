/*
 * For each left bound, we want to calculate the rightmost number we can include in the interval for the 
 * interval to be valid, which we can do using two pointers. First, to calculate the prime factorization of
 * any number, we pre-calculate the sieve up until 1e6, and we can recurse down this to get the prime 
 * factorization. Then, for each prime factorization, we can store its count in the interval. In addition,
 * we can store the count of the count of each prime factor in the interval. To check if the current
 * range is valid, we need to check if cnt[r - l] or cnt[r - l + 1] are greater than 0 (corresponding to
 * removing 1 number and removing no numbers). We can then easily answer each query by comparing it with
 * the pre-calculated bounds.
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000010

using namespace std;

int n, q;
int nums[MAXN];
int p[MAXN];
int p_cnt[MAXN]; // counts how many times each prime appears
int cnt[MAXN]; // counts how many times each occurrence appears
int rr[MAXN];
bool added[MAXN];
string ans;

vector<int> get_factor(int cur) {
    vector<int> factor;
    while (cur != 1) {
        int pp = p[cur];
        factor.push_back(pp);
        while (cur % pp == 0) cur /= pp;
    }
    return factor;
}

int main() {
    ifstream fin("deletegcd.in");
    ofstream fout("deletegcd.out");

    fin >> n >> q;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
    }

    for (ll i = 2; i < MAXN; i++) {
        if (!p[i]) {
            p[i] = i;
            cnt[0]++;
            for (ll j = i * i; j < MAXN; j += i) {
                p[j] = i;
            }
        }
    }

    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n) {
            if (!added[r]) {
                added[r] = true;
                vector<int> factor = get_factor(nums[r]);
                for (int x : factor) {
                    cnt[p_cnt[x]]--;
                    p_cnt[x]++;
                    cnt[p_cnt[x]]++;
                }
            }

            if (cnt[r - l] == 0 && cnt[r - l + 1] == 0) {
                break;
            }

            r++;
        }

        rr[l] = r;

        vector<int> to_rem = get_factor(nums[l]);
        for (int x : to_rem) {
            cnt[p_cnt[x]]--;
            p_cnt[x]--;
            cnt[p_cnt[x]]++;
        }
    }

    while (q--) {
        int l, r; fin >> l >> r;
        l--; r--;
        if (rr[l] > r) {
            ans += '1';
        } else {
            ans += '0';
        }
    }

    fout << ans << '\n';

    return 0;
}
