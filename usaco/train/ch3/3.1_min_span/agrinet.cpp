/*
ID: aaryan.1
TASK: agrinet
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");

    int n; fin >> n;
    vector<vector<int>> connect;

    for (int i = 0; i < n; i++) {
        vector<int> row;
        for (int j = 0; j < n; j++) {
            int x; fin >> x;
            row.push_back(x);
        }

        connect.push_back(row);
    }

    vector<bool> added(n, false);
    vector<int> curEdge;

    int minVal = 2000000000;
    int minPoint[2];
    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (connect[i][j] < minVal) {
                minVal = connect[i][j];
                minPoint[0] = i;
                minPoint[1] = j;
            }
        }
    }

    added[minPoint[0]] = true;
    added[minPoint[1]] = true;
    curEdge.push_back(minPoint[0]);
    curEdge.push_back(minPoint[1]);
    total += minVal;

    while (curEdge.size() < n) {
        int minDist = 2000000000;
        int minDest = 0;
        for (int e : curEdge) {
            for (int i = 0; i < n; i++) {
                if (connect[e][i] < minDist && !added[i]) {
                    minDist = connect[e][i];
                    minDest = i;
                }
            }
        }

        total += minDist;
        curEdge.push_back(minDest);
        added[minDest] = true;
    }

    fout << total << '\n';
    return 0;
}
