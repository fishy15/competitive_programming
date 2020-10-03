/*
 * We can prove that if [i..j] is the optimal sequence, then either 0 <= i < 3 or n - 3 <= i < n
 * This can be proven with casework
 * Assume that [i..j] is the optimal sequence, but it satisfies neither of the other conditions
 * Case 1: [i..j] is only one letter
 *      - Subcase 1: i != j
 *          In this case, we can add a neighboring value to [i..j] cannot be optimal
 *      - Subcase 2: i == j
 *          In this case, the answer is of size 1, so we can pick any segment of length 1 in the range as well
 * Case 2: [i..j] is more than one letter
 *      In this case, we can show that there is some way to fill B, S, C values to the three indices to the left adn three indices to the right to get a better answer, [i..j] cannot be optimal (full proof in editorial)
 * We can use prefix sums to then check all the ranges that satisfy these constraints.
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

int n;
string w;
int b[MAXN];
int s[MAXN];
int c[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> w;
    for (int i = 0; i < n; i++) {
        if (w[i] == 'B') {
            b[i + 1]++;
        } else if (w[i] == 'S') {
            s[i + 1]++;
        } else {
            c[i + 1]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
        s[i] += s[i - 1];
        c[i] += c[i - 1];
    }

    int ans = 0;
    array<int, 3> v;
    set<int> ss;
    // check case where beginning is in first 3
    for (int i = 0; i <= 3; i++) {
        for (int j = i + 1; j <= n; j++) {
            v = {b[j] - b[i], s[j] - s[i], c[j] - c[i]};
            bool works = true;
            for (int i = 0; i < 3 && works; i++) {
                for (int j = i + 1; j < 3; j++) {
                    if (v[i] && v[j] && v[i] == v[j]) {
                        works = false;
                        break;
                    }
                }
            }
            if (works) {
                ans = max(ans, j - i);
            }
        }
    }

    // check case where beginning is in last 3
    for (int j = n - 3; j <= n; j++) {
        for (int i = 0; i < j - 1; i++) {
            v = {b[j] - b[i], s[j] - s[i], c[j] - c[i]};
            bool works = true;
            for (int i = 0; i < 3 && works; i++) {
                for (int j = i + 1; j < 3; j++) {
                    if (v[i] && v[j] && v[i] == v[j]) {
                        works = false;
                        break;
                    }
                }
            }
            if (works) {
                ans = max(ans, j - i);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
