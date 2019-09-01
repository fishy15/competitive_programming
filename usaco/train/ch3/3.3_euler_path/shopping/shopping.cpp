/*
ID: aaryan.1
TASK: shopping
LANG: C++11
*/

// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct offer {
    int price;
    vector<pair<int, int>> codes;
};

struct prod {
    int code;
    int num;
    int price;
};

int s;
int b;
vector<offer> offers;
vector<prod> products;
map<int, int> pos;
map<int, int> rev;

int dp[6][6][6][6][6];
int needed[6];

int main() {
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");

    fin >> s;
    for (int i = 0; i < s; i++) {
        int n; fin >> n;
        offer off;
        for (int j = 0; j < n; j++) {
            int x, y; fin >> x >> y;
            off.codes.push_back({x, y});
        }

        fin >> off.price;
        offers.push_back(off);
    }

    fin >> b;
    for (int i = 0; i < b; i++) {
        prod p;
        fin >> p.code >> p.num >> p.price;
        products.push_back(p);
        pos[p.code] = i;
        rev[i] = p.code;
        needed[i] = p.num;
    }

    if (b == 0) {
        fout << "0\n";
        return 0;
    }

    for (int a = 0; a < 6; a++) {
        for (int b = 0; b < 6; b++) {
            for (int c = 0; c < 6; c++) {
                for (int d = 0; d < 6; d++) {
                    for (int e = 0; e < 6; e++) {
                        dp[a][b][c][d][e] = INF;
                    }
                }
            }
        }
    }

    dp[0][0][0][0][0] = 0;

    for (int i = 0; i < s; i++) {
        int change[] = {0, 0, 0, 0, 0};

        for (pair<int, int> prod : offers[i].codes) {
            if (!pos.count(prod.first)) {
                continue;
            } 

            change[pos[prod.first]] += prod.second;
        }

        /* for (int i = 0; i < 5; i++) { */
        /*     cout << change[i] << '\n'; */
        /* } */

        for (int a = 0; a <= 5; a++) {
            if (a + change[0] > 5) {
                break;
            }

            for (int b = 0; b <= 5; b++) {
                if (b + change[1] > 5) {
                    break;
                }

                for (int c = 0; c <= 5; c++) {
                    if (c + change[2] > 5) {
                        break;
                    }

                    for (int d = 0; d <= 5; d++) {
                        if (d + change[3] > 5) {
                            break;
                        }

                        for (int e = 0; e <= 5; e++) {
                            if (e + change[4] > 5) {
                                break;
                            }

                            int new_a = a + change[0];
                            int new_b = b + change[1];
                            int new_c = c + change[2];
                            int new_d = d + change[3];
                            int new_e = e + change[4];

                            dp[new_a][new_b][new_c][new_d][new_e] = \
                                min(dp[new_a][new_b][new_c][new_d][new_e], \
                                dp[a][b][c][d][e] + offers[i].price);
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    for (int a = 0; a <= needed[0]; a++) {
        for (int b = 0; b <= needed[1]; b++) {
            for (int c = 0; c <= needed[2]; c++) {
                for (int d = 0; d <= needed[3]; d++) {
                    for (int e = 0; e <= needed[3]; e++) {
                        int cost = dp[a][b][c][d][e] \
                            + (needed[0] - a) * products[0].price \
                            + (needed[1] - b) * products[1].price \
                            + (needed[2] - c) * products[2].price \
                            + (needed[3] - d) * products[3].price \
                            + (needed[4] - e) * products[4].price;
                        ans = min(ans, cost);
                    }
                }
            }
        }
    }

    fout << ans << '\n';

    return 0;
}
