#include <iostream>
#include <fstream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int B, E, P, N, M;
vector<vector<bool>> connect;
vector<int> distB;
vector<int> distE;
vector<int> distP;

int main() {
    ifstream fin("piggyback.in");
    ofstream fout("piggyback.out");

    int B, E, P, N, M;
    vector<vector<bool>> connect;
    vector<int> distB;
    vector<int> distE;
    vector<int> distP;

    fin >> B >> E >> P >> N >> M;
    connect = vector<vector<bool>>(N, vector<bool>(N, false));

    for (int i = 0; i < M; i++) {
        int x, y; fin >> x >> y;
        connect[x - 1][y - 1] = true;
        connect[y - 1][x - 1] = true;
    }

    vector<int> q = {0};
    int curDist = 1;
    distB = vector<int>(N, -1);
    distB[0] = 0;
    while (q.size() > 0) {
        vector<int> q2;
        for (auto x : q) {
            if (distB[x] == -1) {
                distB[x] = curDist;
                q2.push_back(x);
            }
        }

        q = q2;
        curDist++;
    }

    q = {1};
    curDist = 1;
    distE = vector<int>(N, -1);
    distE[1] = 0;
    while (q.size() > 0) {
        vector<int> q2;
        for (auto x : q) {
            if (distE[x] == -1) {
                distE[x] = curDist;
                q2.push_back(x);
            }
        }

        q = q2;
        curDist++;
    }

    q = {N - 1};
    curDist = 1;
    distP = vector<int>(N, -1);
    distB[N - 1] = 0;
    while (q.size() > 0) {
        vector<int> q2;
        for (auto x : q) {
            if (distP[x] == -1) {
                distP[x] = curDist;
                q2.push_back(x);
            }
        }

        q = q2;
        curDist++;
    }

    int minDist = INF;
    for (int i = 0; i < N; i++) {
        if (distB[i] > -1 && distE[i] > -1 && distP[i] > -1) {
            int total = distB[i] * B + distE[i] * E + distP[i] * P;
            minDist = minDist < total ? minDist : total;
        }
    }

    cout << minDist << '\n';
    return 0;
}
