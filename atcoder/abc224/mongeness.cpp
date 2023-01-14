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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int h, w;
int nums[100][100];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> nums[i][j];
        }
    }

    for (int a = 0; a < h; a++) {
        for (int b = a + 1; b < h; b++) {
            for (int c = 0; c < w; c++) {
                for (int d = c + 1; d < w; d++) {
                    if (nums[a][c] + nums[b][d] > nums[a][d] + nums[b][c]) {
                        cout << "No\n";
                        return 0;
                    }
                }
            }
        }
    }

    cout << "Yes\n";

    return 0;
}
