#include <iostream>
using namespace std;

const int LEN = 10;

void excerpt(int arr[LEN]);

int main() {
    int n; cin >> n;
    int arr[LEN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < LEN; j++) {
            cin >> arr[i];
        }
        excerpt(arr);
    }
}
