#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");

    int N, K; fin >> N >> K;
    int r = 1;
   
    vector<int> points(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i];
    }

    sort(points.begin(), points.end());
    while (true) {
        int maxCov = -1;
        int index = 0;
        for (int i = 0; i < K; i++) {
            maxCov = points[index] + 2 * r;
            while (points[index] <= maxCov) {
                index++;
                if (index == N) {
                    fout << r << '\n';
                    return 0;
                }
            }
        }

        r++;
    }
}
