// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakfin:
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
// :pray: :hyafinth:
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
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

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
#define MAXN 200 

using namespace std;

int n, m;
vector<string> grid;
int down_max[MAXN][MAXN];
int right_max[MAXN][MAXN];


int main() {
    ifstream fin("fortmoo.in");
    ofstream fout("fortmoo.out");

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; fin >> s;
        grid.push_back(s);
    }

    bool allbad = true;

    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                cur++;
                right_max[i][j] = cur;
                allbad = false;
            } else {
                cur = 0;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int cur = 0;
        for (int i = 0; i < n; i++) {
            if (grid[i][j] == '.') {
                cur++;
                down_max[i][j] = cur;
                allbad = false;
            } else {
                cur = 0;
            }
        }
    }

    if (allbad) {
        fout << 0 << '\n';
        return 0;
    }

    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int a = i; a < n; a++) {
                for (int b = j; b < m; b++) {
                    if (right_max[i][b] >= b - j && down_max[a][b] >= a - i
                            && right_max[a][b] >= b - j && down_max[a][j] >= a - i) {
                        ans = max(ans, (b - j + 1) * (a - i + 1));
                    }
                }
            }
        }
    }

    fout << ans << '\n';
    return 0;
}
