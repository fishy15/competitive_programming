#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>

#define sq(x) (x) * (x)
using namespace std;

int n; 
vector<int> vals;
vector<int> size;
vector<pair<int, int>> coord;

typedef struct path path;
struct path {
    int x, y;

    int dist() {
        return sq(coord[x].first - coord[y].first) + sq(coord[x].second - coord[y].second);
    }
};

bool comp(path &p1, path &p2) {
    return p1.dist() > p2.dist();
}

int find(int a) {
    if (a == vals[a]) {
        return a;
    }

    return (vals[a] = find(vals[a]));
}

void join(int a, int b) {
    if ((a = find(a)) != (b = find(b))) {
        if (size[a] > size[b]) {
            vals[b] = vals[a];
            size[a] += size[b];
        } else {
            vals[a] = vals[b];
            size[b] += size[a];
        }
    }
}

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        coord.push_back({x - 1, y - 1});
        vals.push_back(i);
        size.push_back(1);
    }

    priority_queue<path, vector<path>, decltype(&comp)> pq(comp);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            path p;
            p.x = i;
            p.y = j;
            pq.push(p);
        }
    }

    int max = 0;
    int edges = 0;

    while (edges < n - 1) {
        path p = pq.top();
        pq.pop();

        max = p.dist();

        if (find(p.x) != find(p.y)) {
            join(p.x, p.y);
            edges++;
        }
    }

    fout << max << '\n';
    return 0;
}
