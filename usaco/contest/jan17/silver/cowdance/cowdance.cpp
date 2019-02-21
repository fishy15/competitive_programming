/* great
 * *xxxxxxxxx
*/

#include <iostream>
#include <fstream>
#include <queue>

#define MAX_N 10000

using namespace std;

int N, T;
int cows[MAX_N];

int works(int x) {
    priority_queue<int, vector<int>, greater<int> > p;

    for (int i = 0; i < x; i++) {
        p.push(cows[i]);
    }

    for (int i = x; i < N; i++) {
        p.push(p.top() + cows[i]);
        p.pop();
    }

    for (int i = 0; i < x - 1; i++) {
        p.pop();
    }

    return p.top() <= T;
}

int main() {
    ifstream fin("cowdance.in");
    ofstream fout("cowdance.out");

    fin >> N >> T;

    for (int i = 0; i < N; i++) {
        fin >> cows[i];
    }

    /*
    for (int i = 1; i <= N; i++) {
        printf("%d\n", works(i));
    }
    //*/

    int min = 1;
    int max = N;
    while (min < max) {
        //printf("%d %d\n", min, max);
        int mid = (min + max) / 2;

        if (works(mid)) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }

    //printf("%d\n", min);
    fout << min << '\n';
    return 0;
}
