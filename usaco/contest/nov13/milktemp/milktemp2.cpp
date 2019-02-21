#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

#define LOW -1
#define NORMAL 0
#define HIGH 1

using namespace std;

int N;
int high, low, normal;
vector<pair<int, int> > temp;

int main() {
    ifstream fin("milktemp.in");
    ofstream fout("milktemp.out");

    fin >> N >> low >> normal >> high;

    for (int i = 0; i < N; i++) {
        int x, y; fin >> x >> y;
        temp.push_back(make_pair(x, LOW));
        temp.push_back(make_pair(y, HIGH));
    }

    sort(temp.begin(), temp.end());

    int max = 0;
    int total = N * low;
    for (int i = 0; i < N * 2; i++) {
        if (temp[i].second == LOW) {
            total += normal;
            total -= low;
        } else {
            total += high;
            total -= normal;
        }

        max = total > max ? total : max;
    }

    fout << max << '\n';

    return 0;
}


