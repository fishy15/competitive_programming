/*
ID: aaryan.1
TASK: cowtour
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <queue>
#include <cstdio>

#define ll long long 
#define inf 3 * 141422.0

using namespace std;

typedef struct point point;
struct point {
    ll x, y;
    int num;
    double diam;
};

int n;
vector<point> points;
vector<string> connect;
vector<bool> visited;
vector<vector<int> > field; // vectors of what points are connected
double field1Diam;
double field2Diam;

void fill(int, int);
double dist(int, int);
void findDiams(int);
void findFieldDiam();

int main() {
    ifstream fin("cowtour.in");
    FILE* fout = fopen("cowtour.out", "w");

    fin >> n;
    for (int i = 0; i < n; i++) {
        point p;
        fin >> p.x >> p.y;
        p.num = -1;
        p.diam = 0;
        points.push_back(p);
    }

    for (int i = 0; i < n; i++) {
        string s; fin >> s;
        connect.push_back(s);
    }

    visited = vector<bool>(n, false);

    int val = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            field.push_back(vector<int>());
            fill(i, val);
            val++;
        }
    }

    visited = vector<bool>(n, false);

    /*
    for (auto v : field) {
        for (int i : v) {
            cout << i << ' ';
        }
        cout<< endl;
    }
    */

    for (int i = 0; i < field.size(); i++) {
        findDiams(i);
    }

    findFieldDiam();

    /*
    for (int i = 0; i < n; i++) {
        cout << points[i].diam << endl;
    }
    */

    double minDiam = inf; // 100000 * sqrt(2)

    for (int i = 0; i < field.size(); i++) {
        for (int j = i + 1; j < field.size(); j++) {
            for (int f : field[i]) {
                for (int s : field[j]) {
                    double res = points[f].diam + points[s].diam + dist(f, s);
                    //cout << f << ' ' << s << ' ' << points[f].diam << ' ' << points[s].diam << ' ' << dist(f, s) << endl;
                    minDiam = res < minDiam ? res : minDiam;
                }
            }
        }
    }

    if (field1Diam > minDiam && field1Diam > field2Diam) {
        minDiam = field1Diam;
    } else if (field2Diam > minDiam) {
        minDiam = field2Diam;
    }

    fprintf(fout, "%.6f\n", minDiam);
    return 0;
}

void fill(int pos, int val) {
    visited[pos] = true;
    points[pos].num = val;
    field[val].push_back(pos);

    for (int i = 0; i < n; i++) {
        if (connect[pos][i] == '1' && !visited[i]) {
            fill(i, val);
        }
    }
}

double dist(int ind2, int ind1) {
    int x = points[ind2].x - points[ind1].x;
    int y = points[ind2].y - points[ind1].y;

    return sqrt(x*x + y*y);
}

// pos is number of field you are looking at
void findDiams(int pos) {
    int n = (int)(field[pos].size());
    vector<vector<double>> distV(n, vector<double>(n, inf));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos1 = field[pos][i];
            int pos2 = field[pos][j];

            if (connect[pos1][pos2] == '1' || pos1 == pos2) {
                distV[i][j] = dist(pos1, pos2);
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int pos1 = field[pos][i];
                int pos2 = field[pos][j];
                int posk = field[pos][k];

                if (distV[i][k] + distV[j][k] < distV[i][j]) {
                    distV[i][j] = distV[i][k] + distV[j][k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        double maxDiam = 0;
        for (int j = 0; j < n; j++) {
            if (distV[i][j] > maxDiam) {
                maxDiam = distV[i][j];
            }
        }

        points[field[pos][i]].diam = maxDiam;
    }
}

void findFieldDiam() {
    for (int f : field[0]) {
        field1Diam = points[f].diam > field1Diam ? points[f].diam : field1Diam;
    }

    for (int f : field[1]) {
        field2Diam = points[f].diam > field2Diam ? points[f].diam : field2Diam;
    }
}
