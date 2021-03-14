/*
 * Each player must travel on some monotone sequence, where Player 1 will move to a lower number and 
 * Player 2 will move to a higher number. They also ideally want to go on the longest subsequence possible.
 * If they don't, then the person who chose the longer subsequence will win (except potentially if their 
 * paths would intersect). This means that person 1 should choose one of the longest subsequences, and then
 * person 2 will either pick the same subsequence or a separate one of equal length.
 *
 * Additionally, note that player 1 must start at some position where both sides are potential directions 
 * to go. If not, then player 2 is able to block off player 1's movement and win directly.
 *
 * Suppose there is only 1 subsequence of the longest length. Then both player 1 and player 2 will be on 
 * this sequence. However, player 2 can then choose the farthest distance away on that subsequence that is
 * an odd number of moves away. If player 1 chooses to move in the opposite direction of the longest 
 * subsequence, then he will have at most X - 1 moves while player 2 will have at least X - 1 moves (where
 * X is the length of the maximum monotonic subsequence). Therefore, player 1 will always lose in this case.
 * In the case where there are at least 3 subsequences of the longest length, then player 2 can always 
 * choose another subsequence of the same length, so player 2 will win.
 *
 * In the case where there are 2 subsequences of the longest length, player 2 can pick another subsequence
 * if the two sequences are disjoint. If they have their greatest value in common, then player 1 will 
 * start at the greatest value and player 2 will be at one of the ends (if player 2 is any closer, player
 * 1 can move in the opposite side and win). If the number of moves between player 1 and 2 is even, then 
 * player 1 will win, otherwise player 2 will win. This can be the only location where player 1 can win,
 * so the answer is either 0 or 1.
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

int n;
int nums[MAXN];

struct person {
    int l[MAXN];
    int r[MAXN];
} p1;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    pair<int, int> best = {-1, -1};
    // solve for rightward movement
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] < nums[i]) {
            p1.r[i] = p1.r[i - 1] + 1;
        }
    }

    // solve for leftward movement
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] > nums[i + 1]) {
            p1.l[i] = p1.l[i + 1] + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (p1.l[i] > best.first) {
            best = {p1.l[i], 1};
        } else if (p1.l[i] == best.first) {
            best.second++;
        }

        if (p1.r[i] > best.first) {
            best = {p1.r[i], 1};
        } else if (p1.r[i] == best.first) {
            best.second++;
        }
    }

    if (best.second != 2) {
        cout << "0\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (p1.l[i] == best.first && p1.r[i]) {
            if (best.first % 2 == 0) {
                cout << "1\n";
            } else {
                cout << "0\n";
            }
            return 0;
        }
    }

    cout << "0\n";

    return 0;
}
