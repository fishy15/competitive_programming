/*
 * this gets 8/10 cases
 * times out on 9 and 10
 * ********tt
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define LOW -1
#define NORMAL 0
#define HIGH 1

using namespace std;

int high, low, normal;

typedef struct cow cow;
struct cow {
    int low, high;
    int state;

    cow(int low, int high) {
        this->low = low;
        this->high = high;
        this->state = LOW;
    }

    int milk(int temp) {
        if (temp < this->low) {
            return LOW;
        } else if (temp > this->high) {
            return HIGH;
        }

        return NORMAL;
    }
};

int N;
vector<cow> cows;
vector<int> nums;

int conv(int num);

int main() {
    ifstream fin("milktemp.in");
    ofstream fout("milktemp.out");

    fin >> N >> low >> normal >> high;

    for (int i = 0; i < N; i++) {
        int x, y; fin >> x >> y;
        cows.push_back(cow(x, y));
        nums.push_back(x);
        //nums.push_back(y);
    }

    sort(nums.begin(), nums.end());
   
    int max = 0;
    int total = N * low;
    //int total = N * low;
    for (int i = 0; i < N; i++) {
        int temp = nums[i];

        for (int j = 0; j < N; j++) {
            if (cows[j].milk(temp) != cows[j].state) {
                cows[j].state++;
                if (cows[j].state == NORMAL) {
                    total += normal;
                    total -= low;
                } else {
                    total += high;
                    total -= normal;
                }
            }
        }

        //cout << total << endl;
        max = total > max ? total : max;
    }

    fout << max << '\n';

    return 0;
}

int conv(int num) {
    if (num == LOW) {
        return low;
    } else if (num == HIGH) {
        return high;
    } 

    return normal;
}
