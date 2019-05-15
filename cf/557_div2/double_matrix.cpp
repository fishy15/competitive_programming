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

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cstdlib>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

#define MAXN 50

using namespace std;

int n, m;
int mat1[MAXN][MAXN];
int mat2[MAXN][MAXN];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat1[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat2[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a = mat1[i][j];
            int b = mat2[i][j];
            mat1[i][j] = min(a, b);
            mat2[i][j] = max(a, b);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool flag = false;
            if (i > 0) {
                if (mat1[i - 1][j] >= mat1[i][j]) {
                    flag = true;
                }
                
                if (mat2[i - 1][j] >= mat2[i][j]) {
                    flag = true;
                }
            }
            
            if (j > 0) {
                if (mat1[i][j - 1] >= mat1[i][j]) {
                    flag = true;
                } 
                
                if (mat2[i][j - 1] >= mat2[i][j]) {
                    flag = true;
                }
            }
            
            if (flag) {
                cout << "Impossible\n";
                return 0;
            }
        }
    }
    
    cout << "Possible\n";
    return 0;
}
