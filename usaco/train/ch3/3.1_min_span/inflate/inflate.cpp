/*
ID: aaryan.1
TASK: inflate
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct prob prob;
struct prob {
    int points;
    int time; 
};

int main() {
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");

    int m, n; fin >> m >> n;
    vector<prob> cats;
    vector<int> times(m + 1, 0);

    for (int i = 0; i < n; i++) {
        prob p; 
        fin >> p.points >> p.time;
        cats.push_back(p);
    }

    for (int t = 1; t <= m; t++) {
        int maxVal = 0;
        for (prob p : cats) {
            if (t - p.time >= 0) {
                int newVal = times[t - p.time] + p.points;
                maxVal = newVal > maxVal ? newVal : maxVal;
            }
        }

        times[t] = maxVal;
    }

    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = times[i] > ans ? times[i] : ans; 
    }

    fout << ans << '\n';
    return 0;
}
