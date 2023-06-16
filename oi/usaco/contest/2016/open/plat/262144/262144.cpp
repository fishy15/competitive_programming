// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 262144
#define MAXX 70

using namespace std;

int n;
int step[MAXN][MAXX];
int nums[MAXN];

int main() {
    ifstream fin("262144.in");
    ofstream fout("262144.out");

    int n; fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
        step[i][nums[i]] = 1;
    }

    for (int i = 1; i < n; i++) {
        int dist = 1; 
        int num = nums[i];
        while (i - dist >= 0 && step[i - dist][num] > 0) {
            dist += step[i - dist][num];
            num++;
            step[i][num] = dist;
        }
    }

    for (int i = MAXX - 1; i > 0; i--) {
        for (int j = 0; j < n; j++) {
            if (step[j][i]) {
                fout << i << '\n';
                return 0;
            }
        }
    }

    return 0;
}
