#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct cow cow;
struct cow {
    int come;
    int eat;
    int senior;
};

int main() {
    ifstream fin("convention2.in");
    ofstream fout("convention2.out");

    int n; fin >> n;
    vector<cows> cows;

    for (int i = 0; i < n; i++) {
        cow c;
        fin >> c.come >> c.eat;
        c.senior = i;
        cows.push_back(c);
    }

    int time = 0;
    int done = 0;
    vector<bool> done(n, false);

    while (done < n) {

    }

    return 0;
}
