// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define eps 1e-9

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int n; cin >> n;
        double min = 0.0;
        double max = n / 2.0;
        bool flag = false;
        int op = 0;
        
        while (max - min > -eps) {
            double mid = (min + max) / 2;
            double n1 = n / 2.0 + mid;
            double n2 = n / 2.0 - mid;
            double prod = n1 * n2;
            double sum = n1 + n2;
            
            if (abs(prod - n) < eps) {
                printf("Y %.9f %.9f\n", n1, n2);
                flag = true;
                break;
            } else if (prod - n > eps) {
                min = mid;
            } else {
                max = mid;
            }
            
            if (op > 3000) break;
            
            op++;
        }
        
        if (!flag) {
            printf("N\n");
        }
    }
}