#include "Brunolib.h"
#define ll long long

long long Bruno(int N, int A[]){
    int d = 0;
    ll ans = 0;

    for (int i = 0; i < N; i += 3) {
        if (d > 60) break;
        int v = 4 * A[i] + 2 * A[i + 1] + A[i + 2];
        if (v == 1) {
            ans += 1LL << d;
            d++;
        } else if (v == 2) {
            d++;
        } else if (v == 3) {
            ans += 1LL << d;
            d += 2;
        } else if (v == 4) {
            d += 2;
        } else if (v == 5) {
            ans += 2LL << d;
            d += 2;
        } else if (v == 6) {
            ans += 1LL << d;
            d++;
        } else if (v == 7) {
            ans += 3LL << d;
            d += 2;
        }
    }

    return ans;
}
