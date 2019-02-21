// this one has results *****x**** so far
// other one doesn't work

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

#define min(x, y) (x) < (y) ? (x) : (y)
#define maxi(x, y) (x) > (y) ? (x) : (y)

using namespace std;

int N, M, R;
vector<int> cows;
vector<bool> milked;
vector<pair<int, int> > buy;
vector<int> rent;
int buyIndex;
int rentIndex;
int cowIndex;
long long total;

void buyMilk(int gallons);

int main() {
    ifstream fin("rental.in");
    ofstream fout("rental.out");

    fin >> N >> M >> R;
    cowIndex = N - 1;

    for (int i = 0; i < N; i++) {
        int x; fin >> x;
        cows.push_back(x);
    }

    sort(cows.rbegin(), cows.rend());

    for (int i = 0; i < M; i++) {
        int x, y; fin >> x >> y;
        buy.push_back(make_pair(y, x));
    }

    sort(buy.rbegin(), buy.rend());

    for (int i = 0; i < R; i++) {
        int x; fin >> x;
        rent.push_back(x);
    }

    sort(rent.rbegin(), rent.rend());

    milked = vector<bool>(N, false);
    while (cowIndex >= 0) {
        //cout << cows[cowIndex] << '\n';
        if (rentIndex == R) {
            buyMilk(cows[cowIndex]);
            milked[cowIndex] = true;
            //cout << cowIndex << " milked\n";
            //cout << total << endl;
        } else {
            //cout << cowIndex << " rented\n";
            //cout << total << endl;
            total += rent[rentIndex];
            rentIndex++;
        }

        cowIndex--;
    }

    //cout << total << '\n';
    long long max = total;
    cowIndex = 0;

    while (cowIndex < N) {
        if (rentIndex == 0) {
            break;
        }

        if (milked[cowIndex]) {
            cowIndex++;
            continue;
        }

        total -= rent[rentIndex - 1];
        buyMilk(cows[cowIndex]);
        milked[cowIndex] = true;

        cowIndex++;
        rentIndex--;

        max = maxi(max, total);
    }

    fout << max << '\n';

    return 0;
}

void buyMilk(int gallons) {
    while (gallons > 0) {
        if (buyIndex == M) {
            break;
        } 

        if (buy[buyIndex].second == 0) {
            buyIndex++;
        }

        int milk = min(gallons, buy[buyIndex].second);
        total += milk * buy[buyIndex].first;
        buy[buyIndex].second -= milk;
        gallons -= milk;

        //cout << "gallons: " << milk << endl;
    }
}

// the greedy approach doesn't work
// try a different approach
// hidden for length
/*
for (int i = 0; i < N; i++) {
    if (buyIndex == M && rentIndex == R) {
        break;
    } else if (buyIndex == M) {
        for (int j = i; j < N; j++) {
            total += rent[rentIndex];
            rentIndex++;

            if (rentIndex == R) {
                break;
            }
        }
        break;
    } else if (rentIndex == R) {
        for (int j = i; j < N; j++) {
            int milk = min(cows[i], buy[buyIndex].second);
            total += milk * buy[buyIndex].first;
            buy[buyIndex].second -= milk;

            if (buy[buyIndex].second == 0) {
                buyIndex++;
            }

            if (buyIndex == M) {
                break;
            }
        }

        break;
    }

    while (cows[i] > 0) {
        int milk = min(cows[i], buy[buyIndex].second);
        int buyTotal = milk * buy[buyIndex].first;
        int rentTotal = rent[rentIndex];
        bool lock = false;

        if (lock || buyTotal > rentTotal) {
            cout << "buy " << milk << " from " << i << '\n';
            total += buyTotal;
            buy[buyIndex].second -= milk;

            if (buy[buyIndex].second == 0) {
                buyIndex++;
            }

            cows[i] -= milk;
            lock = true;
        } else {
            cout << "rent " << rentTotal << '\n';
            total += rentTotal;
            rentIndex++;
            cows[i] = 0;
        }
    }
}
*/