#include <iostream>
#include <fstream>
#include <vector>

#define ll long long

using namespace std;

vector<int> pList[1000001];

int main() {
    ifstream fin("cufar.in");
    ofstream fout("cufar.out");

    for (int i = 2; i <= 1e6; i++) {
        if (pList[i].size() == 0) {
            for (int j = i; j <= 1e6; j += i) {
                pList[j].push_back(i);
            }
        }
    }
   
    int p, n; fin >> p >> n;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        sum += pList[x][y - 1];
    }

    fout << sum << '\n';
    return 0;
}
