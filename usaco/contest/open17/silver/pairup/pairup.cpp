#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct group group;
struct group {
    int output;
    int number;
};

int main() {
    ifstream fin("pairup.in");
    ofstream fout("pairup.out");

    int n; fin >> n;
    vector<group> cows;
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        group g;
        g.output = y;
        g.number = x;
        cows.push_back(g);
    }

    sort(cows.begin(), cows.end(), [](const group &a, const group &b) {
        return a.output < b.output;
    });

    int max = 0;
    int i = 0;
    int j = n - 1;

    while (i <= j) {
        int val = cows[i].output + cows[j].output;
        max = val > max ? val : max;
        if (cows[i].number < cows[j].number) {
            cows[j].number -= cows[i].number;
            i++;
        } else if (cows[i].number > cows[j].number) {
            cows[i].number -= cows[j].number;
            j--;
        } else {
            i++;
            j--;
        }
    }

    fout << max << '\n';
    return 0;
}
