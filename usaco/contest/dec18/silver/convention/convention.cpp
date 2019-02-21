#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, c;
vector<int> cows;
int minMax = 2000000000;

void dfs(int cowAdd, int bus, int maxWait) {
    cout << cowAdd << ' ' << bus << ' ' << maxWait << endl;
    if (bus == m - 1) {
        cout << "up is done" << endl;
        int needed = n - cowAdd + 1;
        if (c >= needed) {
            cout << "up works bc " << (int)needed << endl;
            if (maxWait < minMax) {
                minMax = maxWait;
            }
        }
    } else {
        for (int i = c; i <= c; i++) {

            if (cowAdd + i > n) {
                break;
            }

            int wait = cows[cowAdd + i] - cows[cowAdd];
            cout << "wait: " << wait << endl;
            if (wait > maxWait) {
                dfs(cowAdd + i, bus + 1, wait);
            } else {
                dfs(cowAdd + i, bus + 1, maxWait);
            }
        }
        cout << endl;
    }
}

int main() {
    ifstream fin("convention.in");
    ofstream fout("convention.out");

    fin >> n >> m >> c;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        cows.push_back(x);
    }

    cows.push_back(0);
    sort(cows.begin(), cows.end());

    for (int i : cows) {
        cout << i << endl;
    }
    
    dfs(1, 0, 0);
    cout << minMax << '\n';
    return 0;
}
