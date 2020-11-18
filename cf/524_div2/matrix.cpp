/*
 * For each pair of a left bound and a right bound for the submatrix, we can create an array of arrays. Each
 * subarray contains 26 elements that stores the counts for each character. If two elements have an odd count
 * in a subarray, then that subarray is invalid. Now, we can use Manacher's to find the number of palindromes
 * (making sure to ignore the invalid subarrays instead of treating them as part of palindrome).
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
#define MAXN 255

using namespace std;

int n, m;
string mat[MAXN];
array<int, 26> pre[MAXN][MAXN];
ll ans;

void pali(const vector<array<int, 26>> &arr) {
    vector<int> d1(n);
    vector<int> d2(n);

    int l = 0;
    int r = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i][0] == -1) continue;
        int k = 1;
        if (i <= r) k = min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && arr[i - k][0] != -1 
               && arr[i + k][0] != -1 && arr[i - k] == arr[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    l = 0;
    r = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i][0] == -1) continue;
        int k = 0;
        if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && arr[i - k - 1][0] != -1
               && arr[i + k][0] != -1 && arr[i - k - 1] == arr[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    for (int i : d1) ans += i;
    for (int i : d2) ans += i;
}

void fix(array<int, 26> &arr) {
    int cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (arr[i] % 2 == 1) cnt++;
    }
    if (cnt > 1) {
        for (int i = 0; i < 26; i++) arr[i] = -1;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pre[i][j + 1] = pre[i][j];
            pre[i][j + 1][mat[i][j] - 'a']++;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = i; j < m; j++) {
            vector<array<int, 26>> cur;
            for (int k = 0; k < n; k++) {
                array<int, 26> arr;
                for (int a = 0; a < 26; a++) {
                    arr[a] = pre[k][j + 1][a] - pre[k][i][a];
                }
                fix(arr);
                cur.push_back(arr);
            }
            pali(cur);
        }
    }

    cout << ans << '\n';

    return 0;
}
