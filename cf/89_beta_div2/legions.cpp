#include <iostream>
#include <vector>

#define ll long long
#define MOD 100000000

using namespace std;

// num seg, num foot
ll foot[101][101];

// num seg, num horse
ll horse[101][101];

int main() {
	int n1, n2, k1, k2; cin >> n1 >> n2 >> k1 >> k2;
	foot[0][0] = 1;
	horse[0][0] = 1;
	
	for (int i = 1; i <= n1; i++) {
		for (int diff = 1; diff <= k1; diff++) {
			for (int loc = 0; loc <= n1; loc++) {
				if (loc - diff >= 0) {
					foot[i][loc] += foot[i - 1][loc - diff];
					
					if (foot[i][loc] >= MOD) {
						foot[i][loc] -= MOD;
					}
				}
			}
		}
	}
	
	for (int i = 1; i <= n2; i++) {
		for (int diff = 1; diff <= k2; diff++) {
			for (int loc = 0; loc <= n2; loc++) {
				if (loc - diff >= 0) {
					horse[i][loc] += horse[i - 1][loc - diff];
					
					if (horse[i][loc] >= MOD) {
						horse[i][loc] -= MOD;
					}
				}
			}
		}
	}
	
	ll ans = 0;
	
	for (int numSeg = 1; numSeg <= n1; numSeg++) {
		if (numSeg - 1 > 0) {
			ans += foot[numSeg][n1] * horse[numSeg - 1][n2];
		}
		
		ans += 2 * foot[numSeg][n1] * horse[numSeg][n2];
		
		if (numSeg + 1 <= n2) {
			ans += foot[numSeg][n1] * horse[numSeg + 1][n2];
		}
		
		ans %= MOD;
	}
	
	cout << ans << '\n';
}