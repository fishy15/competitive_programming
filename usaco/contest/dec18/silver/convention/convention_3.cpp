#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> cows;

typedef struct bus bus;
struct bus {
    int start;
    int end;

    int wait() {
        return cows[end] - cows[start];
    }
};

int n, m, c;
int extra;
vector<bus> buses;


void split(int pos) {
    int beg = buses[pos].start;
    int end = buses[pos].end;

    int minNewWait = 2000000000;
    int pos2 = -1;
    for (int i = 0; i < c - 1; i++) {
        int wait1 = cows[beg + i] - cows[beg];
        int wait2 = cows[end] - cows[beg + i + 1];
        int maxWait = wait1 > wait2 ? wait1 : wait2;
        if (minNewWait > maxWait) {
            minNewWait = maxWait;
            pos = i;
        }
    }

    buses[pos].end = beg + pos2;
    bus b;
    b.start = beg + pos2 + 1;
    b.end = end;
    buses.push_back(b);
}

int main() {
    ifstream fin("convention.in");
    ofstream fout("convention.out");

    fin >> n >> m >> c;
    extra = n - m*c;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        cows.push_back(x);
    }

    sort(cows.begin(), cows.end());
    for (int i = 0; i < m; i++) {
        bus b;
        b.start = i*c;
        b.end = i*(c + 1) - 1;
        buses.push_back(b);
    }

    int maxWait = -1;
    int maxPos = -1;
    while (extra > 0) {
        maxWait = -1;
        maxPos = -1;
        for (int i = 0; i < buses.size(); i++) {
            if (buses[i].wait() > maxWait) {
                maxWait = buses[i].wait();
                maxPos = i;
            }
        }

        extra--;
    }

    maxWait = 0;
    for (int i = 0; i < buses.size(); i++) {
        if (maxWait < buses[i].wait()) {
            maxWait = buses[i].wait();
        }
    }

    fout << maxWait << '\n';
    return 0;
}
