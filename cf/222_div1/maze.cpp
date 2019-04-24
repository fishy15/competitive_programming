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

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

#define MAXN 100000

using namespace std;

int n, m, k;
int dot_need, dot_count;

int dot_x = -1;
int dot_y = -1;

vector<string> grid;

void dfs(int x, int y) {
    if (dot_count == dot_need) return;
    grid[x][y] = '.';
    dot_count++;
    
    if (x > 0 && grid[x - 1][y] == 'X') {
        dfs(x - 1, y);
    }
    
    if (x < n - 1 && grid[x + 1][y] == 'X') {
        dfs(x + 1, y);
    }
    
    if (y > 0 && grid[x][y - 1] == 'X') {
        dfs(x, y - 1);
    }
    
    if (y < m - 1 && grid[x][y + 1] == 'X') {
        dfs(x, y + 1);
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '.') {
                dot_need++;
                s[j] = 'X';
                
                if (dot_x == -1) {
                    dot_x = i;
                    dot_y = j;
                }
            }
        }
        
        grid.push_back(s);
    }
    
    dot_need -= k;
    
    dfs(dot_x, dot_y);
    
    for (string s : grid) {
        cout << s << '\n';
    }
}
