// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:
// :pray: :coolguy:

#include <iostream>
#include <fstream>
#include <vector>
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
#define MAXN 1000

using namespace std;

int m, n;
vector<string> arr;
int height[MAXN][MAXN];
int part[MAXN][MAXN];
int tall[MAXN][MAXN];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        arr.push_back(s);
    }

    for (int i = 0; i < n; i++) {
        int cur = 1;
        char c = 0;
        for (int j = m - 1; j >= 0; j--) {
            if (c == arr[j][i]) {
                cur++;
            } else {
                c = arr[j][i];
                cur = 1;
            }

            height[j][i] = cur;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i + 2 * height[i][j] < m) {
                int gap = height[i][j];
                if (height[i][j] == height[i + gap][j] && height[i][j] <= height[i + 2 * gap][j]) {
                    part[i][j]++; 
                    height[i][j] = gap * 3;
                    if (j > 0 && arr[i][j] == arr[i][j - 1] 
                            && arr[i + gap][j] == arr[i + gap][j - 1] 
                            && arr[i + 2 * gap][j] == arr[i + 2 * gap][j - 1] 
                            && height[i][j] == height[i][j - 1]) {
                        part[i][j] += part[i][j - 1];
                    }
                }
            }
        }
    }

    ll sum = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum += part[i][j];
            //cout << part[i][j] << ' ';
        }
        //cout << '\n';
    }

    /* for (int i = 0; i < m; i++) { */
    /*     for (int j = 0; j < n; j++) { */
    /*         cout << height[i][j] << ' '; */
    /*     } */

    /*     cout << '\n'; */
    /* } */

    cout << sum << '\n'; 
    return 0;
}
