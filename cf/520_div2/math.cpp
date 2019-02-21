#include <iostream>
#include <cmath>

using namespace std;
int maxPrimePow(int);

int prod = 1;
int minCount;

int main() {
    int n; cin >> n;
    int pow = 0;
    int maxPow = maxPrimePow(n);
    //cout << maxPow << endl;

    while ((1 << pow) < maxPow) {
        //cout << "pow: " << (1 << pow) << endl;
        pow++;
    }

    //cout << pow << endl;
    //cout << maxPow << ' ' << minCount << endl;
    if (n == 1) {
        cout << "1 0\n";
    } else if (maxPow == minCount && (1<<pow) == maxPow) {
        cout << prod << ' ' << pow << '\n';
    } else {
        cout << prod << ' ' << pow + 1 << '\n';
    }
}

int maxPrimePow(int n) {
    int maxCount = 0;
    int count = 0;

    if (n % 2 == 0) {
        prod = 2;
    }

    while (n % 2 == 0) {
        count++;
        n /= 2;
    }

    maxCount = count;
    if (count == 0) {
        minCount = 2000000;
    } else {
        minCount = count;
    }

    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        if (n % i == 0) {
            prod *= i;
        }

        while (n % i == 0) {
            count++;
            n /= i;
        }

        maxCount = count > maxCount ? count : maxCount;
        if (count > 0 && count < minCount) {
            minCount = count;
        }
    }

    if (n > 2) {
        if (maxCount == 0) {
            maxCount = 1;
        }

        if (minCount > 1 || minCount == 0) {
            minCount = 1;
        }
        prod *= n;
    }

    return maxCount;
}
