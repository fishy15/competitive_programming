/*
 * We can sort the paintings by their value and sort the frames by their sizes. At any step, the actual size
 * of the picture does not matter, but only the size of the frame. Therefore, we can greedily place 
 * pictures. Iterating through the frames in reverse order, we should place the picture with the largest
 * value that fits in the frame. If no pictures fit the current frame, then no pictures will ever a later
 * frame since they only can decrease in size. In addition, it does not make sense to skip a frame since
 * any picture that can fit in a smaller frame can fit in the larger one as well. Every time we are able 
 * to place a picture, we can increment the answer to calculate the painting count.
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
#define MAXN 100010

using namespace std;

int n, m;
pair<int, int> paint[MAXN];
int frame[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> paint[i].first >> paint[i].second;
    }

    for (int i = 0; i < m; i++) {
        cin >> frame[i];
    }

    sort(paint, paint + n, [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.second == p2.second) return p1.first < p2.first;
        return p1.second < p2.second;
    });

    sort(frame, frame + m);

    int cur_p = n - 1;
    int ans = 0;
    for (int i = m - 1; i >= 0; i--) {
        while (cur_p >= 0 && paint[cur_p].first > frame[i]) cur_p--;
        if (cur_p >= 0) {
            ans++;
            cur_p--;
        }
    }

    cout << ans << '\n';

    return 0;
}
