#include <iostream>
#include <fstream>
#include <vector>

#define max(a, b) (a) > (b) ? (a) : (b)

using namespace std;

int map(char c);
int maxArr(int arr[3]);

int main() {
    ifstream fin("hps.in");
    ofstream fout("hps.out");

    int N; fin >> N;
    vector<char> res;
    int before[3] = {0, 0, 0};
    int after[3] = {0, 0, 0};

    for (int i = 0; i < N; i++) {
        char c; fin >> c;
        res.push_back(c);
        after[map(c)]++;
    }

    int maxVal = maxArr(after);
    for (int i = 0; i < N; i++) {
        /*
        for (auto i : after) {
            cout << i << ' ';
        }
        */
        //cout << endl;
        before[map(res[i])]++;
        after[map(res[i])]--;

        int val = maxArr(after) + maxArr(before);
        maxVal = max(val, maxVal);
    }

    fout << maxVal << '\n';
    return 0;
}

int map(char c) {
    if (c == 'H') {
        return 0;
    } else if (c == 'P') {
        return 1;
    }

    return 2;
}

int maxArr(int arr[3]) {
    int maxVal = 0;

    for (int i = 0; i < 3; i++) {
        maxVal = max(arr[i], maxVal);
    }
    
    return maxVal;
}
