#include "Annalib.h"
#include <vector>
using namespace std;

void Anna(int N, long long X, int K, int P[]) {
    vector<bool> works(N, true);
    vector<bool> toset(N, false);
    
    for (int i = 0; i < K; i++) {
        works[P[i]] = false;
    }

    for (int i = 0; i < N; i += 3) {
        int cnt = works[i] + works[i + 1] + works[i + 2];
        if (cnt == 3) {
            int v = X % 4;
            if (v == 0) {
                toset[i] = 1;
            } else if (v == 1) {
                toset[i + 1] = 1;
                toset[i + 2] = 1;
            } else if (v == 2) {
                toset[i] = 1;
                toset[i + 2] = 1;
            } else {
                toset[i] = 1;
                toset[i + 1] = 1;
                toset[i + 2] = 1;
            }
            X >>= 2;
        } else if (cnt == 2) {
            if (!works[i]) {
                if (X & 1) {
                    toset[i + 2] = 1;
                } else {
                    toset[i + 1] = 1;
                }
                X >>= 1;
            } else if (!works[i + 1]) {
                if (X & 1) {
                    toset[i + 2] = 1;
                    X >>= 1;
                } else {
                    if (X % 4 == 0) {
                        toset[i] = 1;
                    } else {
                        toset[i] = 1;
                        toset[i + 2] = 1;
                    }
                    X >>= 2;
                }
            } else {
                if (X & 1) {
                    toset[i] = 1;
                    toset[i + 1] = 1;
                } else {
                    toset[i + 1] = 1;
                }
                X >>= 1;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        Set(i, toset[i]);
    }
}
