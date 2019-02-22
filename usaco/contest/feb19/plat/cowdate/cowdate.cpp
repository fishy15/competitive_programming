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
#include <fstream>
#include <vector>

using namespace std;

int n;
double p_inv[1000000];
double p_frac[1000000];

int l = 0;
int r = 0;
double max = 0.0;
double prod = 1.0;
double sum = 0.0;

int main() {
    ifstream fin("cowdate.in");
    ofstream fout("cowdate.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        double p = x * 0.000001;
        p_inv[i] = 1 - p;
        p_frac[i] = p / (1 - p);
    }

    if (n > 4000) {
        for (; l < n; l++) {
            double prev = 0;
            while (r < n) {
                //cout << "mult " << r << '\n';
                prod *= p_inv[r];
                sum += p_frac[r];

                double p = prod * sum;
                //cout << l << ' ' << r << ' ' << prod << '\n';
                if (p > ::max) {
                    ::max = p;
                    //cout << l << ' ' << r << endl;
                }

                if (p < prev) {
                    r++;
                    break;
                }

                prev = p;
                r++;
            }

            double p = prod * sum;
            if (p > ::max) {
                ::max = p;
                //cout << l << ' ' << r << endl;
            }

            //cout << "div " << l << '\n';
            prod /= p_inv[l];
            sum -= p_frac[l];
        }
    } else {
        for (; l < n; l++) {
            double prod = 1;
            double sum = 0;

            for (int r = l; r < n; r++) {
                prod *= p_inv[r];
                sum += p_frac[r];

                double p = prod * sum;
                if (p > ::max) {
                    ::max = p;
                }
            }
        }
    }

    fout << (int)(1000000 * ::max) << '\n';
}