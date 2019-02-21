#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, c;
int maxMin = 2000000000;
vector<int> cows;

void dfs(int cowsAdded, int busUsed, int maxWait) {
    if (busUsed <= m && cowsAdded == n) {
        if (maxWait < maxMin) {
            maxMin = maxWait;
        }
    } else {
        for (int i = 0; i < c; i++) {
            if (cowsAdded + i > n) {
                break;
            }

            int wait = cows[cowsAdded + i] - cows[cowsAdded];
            if (wait > maxWait) {
                dfs(cowsAdded + i + 1, busUsed + 1, wait);
            } else {
                dfs(cowsAdded + i + 1, busUsed + 1, maxWait);
            }
        }
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

    sort(cows.begin(), cows.end());
    dfs(0, 0, 0);

    fout << maxMin << '\n';
    return 0;
}
