#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef struct pile pile;
struct pile {
    int x, y;

    int dist(int tele) {
        int dist1 = abs(x) + abs(tele - y);
        int dist2 = abs(y) + abs(tele - x);
        int norm = abs(x - y);
        int teleDist = dist1 < dist2 ? dist1 : dist2;
        cout << dist1 << ' ' << dist2 << ' ' << norm << '\n';
        return min(teleDist, norm);

    }
};

vector<pile> p;

int calcDist(int tele) {
    int sum = 0;
    for (auto p2 : p) {
        sum += p2.dist(tele);
    }

    return sum;
}

int main() {
    ifstream fin("teleport.in");
    ofstream fout("teleport.out");

    int n; fin >> n;
    vector<int> loc;

    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        pile p2; 
        p2.x = x;
        p2.y = y;

        loc.push_back(x);
        loc.push_back(y);
        p.push_back(p2);
    }

    sort(loc.begin(), loc.end());

    int val = calcDist(loc[0]);

    for (int i = 1; i < 2 * n; i++) {
        int v = calcDist(loc[i]);
        val = min(val, v);
    }

    cout << val << '\n';
    return 0;
}
