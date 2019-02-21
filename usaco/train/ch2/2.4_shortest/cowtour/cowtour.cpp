/*
ID: aaryan.1
TASK: cowtour
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>

#define sq(X) (X)*(X)
#define INF 0x3f3f3f3f

using namespace std;

typedef struct pasture pasture;

struct pasture {
    int x, y;
    double d;
    bool first;

    pasture(int x, int y) {
        this->x = x;
        this->y = y;
        first = 0;
        d = 0.0;
    }

    double dist(pasture p2) {
        return sqrt(sq(this->x - p2.x) + sq(this->y - p2.y));
    }
};

int N;
vector<pasture> p;
vector<string> connect;
vector<bool> visited;
vector<vector<double> > dist;

void floodfill(int num);
void calcDiam(int num);

int main() {
    ifstream fin("cowtour.in");
    FILE *fout = fopen("cowtour.out", "w");

    fin >> N;
    for (int i = 0; i < N; i++) {
        int x, y; fin >> x >> y;
        p.push_back(pasture(x, y));
    }

    for (int i = 0; i < N; i++) {
        string s; fin >> s;
        connect.push_back(s);
    }

    visited = vector<bool>(N, false);
    dist = vector<vector<double> >(N, vector<double>(N, INF));
    floodfill(0);

    for (int i = 0; i < N; i++) {
        visited = vector<bool>(N, false);
        calcDiam(i);
    }
}

void floodfill(int num) {
    p[num].first = true;
    visited[num] = true;

    for (int i = 0; i < N; i++) {
        if (connect[num][i] == '1' && !visited[i]) {
            floodfill(i);
        }
    }
}

void calcDiam(int num) {
    priority_queue<pair<double, int> >;
    
    for (int i = 0; i < N; i++) {
        if (connect[num][i] == '1') {
            next.push_back(i);
        }
    }

    dist[num] = 0;
    for ()
}