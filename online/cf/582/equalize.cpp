// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000 

using namespace std;

int n, k;
vector<int> nums;
int reach[MAXN + 1][2];
// first is # of times reached
// second is how many divs

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    int minop = INF;

    for (int exp = 0; exp <= 18; exp++) {
        for (int i = 0; i < n; i++) {
            if (nums[i] == -1) {
                continue;
            }

            int num = nums[i] / (1 << exp);
            reach[num][0]++;
            reach[num][1] += exp;

            if (num == 0) {
                nums[i] = -1;
            }

            if (reach[num][0] >= k) {
                minop = min(reach[num][1], minop);
            }
        }
    }

    cout << minop << '\n';

    return 0;
}
