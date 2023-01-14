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

int n;
array<ll, 2> points[400];

ll cross(array<ll, 2> a, array<ll, 2> b) {
    return a[0] * b[1] - a[1] * b[0];
}

bool triangle(int a, int b, int c) {
    array<ll, 2> v1 = {points[b][0] - points[a][0], points[b][1] - points[a][1]};
    array<ll, 2> v2 = {points[c][0] - points[b][0], points[c][1] - points[b][1]};

    return cross(v1, v2) != 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (triangle(i, j, k)) {
                    count++;
                }
            }
        }
    }

    cout << count << '\n';

    return 0;
}
