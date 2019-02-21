/*
ID: aaryan.1
TASK: stamps
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");

    int m, n; fin >> m >> n;
    int maxStamp = 0;
    vector<int> stamps;
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        stamps.push_back(x);
        maxStamp = x > maxStamp ? x : maxStamp;
    }

    vector<int> vals(m * maxStamp + 1);
    vals[0] = 0;
    int num = 1;
    bool works = true;
    while (works) {
        int minSum = 200000000;
        for (int i = 0; i < n; i++) {
            if (num - stamps[i] >= 0) {
                int moves = vals[num - stamps[i]] + 1;
                if (moves < minSum) {
                    minSum = moves;
                }
            }
        }

        if (minSum <= m) {
            vals[num] = minSum;
            num++;
        } else {
            works = false;
        }
    }

    fout << num - 1 << '\n';
    return 0;
}
