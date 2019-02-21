#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("maxcross.in");
    ofstream fout("maxcross.out");

    int N, K, B; fin >> N >> K >> B;
    vector<int> pos; 

    for (int i = 0; i < B; i++) {
        int x; fin >> x;
        pos.push_back(x);
    }

    sort(pos.begin(), pos.end());

    int begin = 0;
    int end = K - 1;
    int badFront = 0;
    int badBack = 0;

    while (badFront < B) {
        if (pos[badFront] > end) {
            break;
        }

        badFront++;
    }

    int min = badFront - badBack + 1;
    while (end < N) {
       begin++;
       end++;

       if (pos[badFront] == end) {
           badFront++;
       }

       if (pos[badBack] < begin) {
           badBack++;
       }

       int val = badFront - badBack;
       
       //cout << "from " << begin << " to " << end << '\n';
       //cout << badFront << ' ' << badBack << '\n';
       min = val < min ? val : min;
    }

    fout << min << '\n';
    return 0;
}
