/*
ID: aaryan.1
TASK: cowtour
LANG: C++11
*/

// uses dijkstra to find closest pairs
// idk why it doesnt work so i use FW 
// on the next program

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <queue>
#include <cstdio>

#define ll long long 

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

void fill(int, int);
double dist(int, int);
void findDiams(int);

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

    /*
    for (int i = 0; i < n; i++) {
        cout << points[i].diam << endl;
    }
    */

    double minDiam = 141422.0 * 3; // 100000 * sqrt(2)

    for (int i = 0; i < field.size(); i++) {
        for (int j = i + 1; j < field.size(); j++) {
            for (int f : field[i]) {
                for (int s : field[j]) {
                    double res = points[f].diam + points[s].diam + dist(f, s);
                    cout << f << ' ' << s << ' ' << points[f].diam << ' ' << points[s].diam << ' ' << dist(f, s) << endl;
                    minDiam = res < minDiam ? res : minDiam;
                }
            }
        }
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

    for (int past = 0; past < field[pos].size(); past++) {
        // first == dist, second = pasture #
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        visited = vector<bool>(n, false);

        int tot = 0;
        pq.push({0, field[pos][past]});
        double maxDist = 0;

        while (tot < field[pos].size()) {
            double distance = pq.top().first;
            int num = pq.top().second;
            pq.pop();

            if (visited[num]) {
                continue;
            }

            tot++;
            visited[num] = true;

            //cout << field[pos][past] << ' ' << num << ' ' << distance << endl;
            //cout << "size: " << tot << ' ' << field[pos].size() << endl;

            for (int i = 0; i < n; i++) {
                if (connect[num][i] == '1' && !visited[i]) {
                    pq.push({distance + dist(num, i), i});
                }
            }

            maxDist = distance > maxDist ? distance : maxDist;
        }

        points[field[pos][past]].diam = maxDist;
    }
}
