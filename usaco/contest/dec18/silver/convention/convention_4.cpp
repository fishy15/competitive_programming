#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("convention.in");
    ofstream fout("convention.out");

    int n, m, k; fin >> n >> m >> k;
    int extra = n - m * k;
    vector<int> cows;
    
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        cows.push_back(x);
    }

    sort(cows.begin(), cows.end());

    vector<int> buses = {-1};
    int total = m;
    for (int i = 0; i < m; i++) {
        buses.push_back(i);
    }

    while (total < n) {
        int minWait = 2000000000;
        int minPos = 1;
        for (int i = 1; i <= m; i++) {
            int newLoc = buses[i] + 1;

            if (newLoc - buses[i - 1] <= k) {

                int newWait = cows[newLoc] - cows[buses[i - 1] + 1];

                if (newWait < minWait) {
                    minWait = newWait;
                    minPos = i;
                }
            }
        }

        for (int i = minPos; i <= m; i++) {
            buses[i]++;
        }

        total++;
    }

    int maxWait = 0;
    for (int i = 1; i <= m; i++) {
        int wait = cows[buses[i]] - cows[buses[i - 1] + 1]; 
        if (wait > maxWait) {
            maxWait = wait;
        }
    }

    fout << maxWait << '\n';
    return 0;
}
