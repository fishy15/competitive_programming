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

bool operator<(const cow &c1, const cow &c2) {
    return c1.senior > c2.senior;
}

int main() {
    ifstream fin("convention2.in");
    ofstream fout("convention2.out");

    int n; fin >> n;
    vector<cow> cows;

    for (int i = 0; i < n; i++) {
        cow c;
        fin >> c.come >> c.eat;
        c.senior = i;
        cows.push_back(c);
    }

    priority_queue<cow> line;
    sort(cows.begin(), cows.end(), [](const cow &c1, const cow &c2) {
        return c1.come < c2.come;  
    });

    int pos = 0;
    int time = 0;
    int wait = 0;
    while (pos < n || !line.empty()) {
        //cout << wait << endl;
        if (time < cows[pos].come && line.empty()) {
            time = cows[pos].come;
        }

        while (pos < n && cows[pos].come <= time) {
            line.push(cows[pos]);
            pos++;
        }

        int cowWait = time - line.top().come;
        //cout << line.top().come << ' ' << time << ' ' << cowWait << '\n';
        if (wait < cowWait) {
            wait = cowWait;
        }

        time += line.top().eat;
        //cout << line.top().senior << '\n';
        line.pop();
    }

    fout << wait << '\n';
    return 0;
}
