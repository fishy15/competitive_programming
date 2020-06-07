#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstring>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, q;

const int maxn = 101;

struct M{
	ll m[maxn][maxn];
 
	M(){
		memset(m, 0, sizeof(m));
	}
 
	static M I(){
		M ret;
		for(int i = 0; i < maxn; i++) ret.m[i][i] = 1;
		return ret;
	}
 
	friend M operator*(M a, M b){
		M ret;
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		for(int k = 0; k < n; k++){
			(ret.m[i][j] += a.m[i][k] * b.m[k][j] ) %= MOD;
		}
		return ret;
	}

    friend M operator^(M a, M b) {
        M ret;
		for(int i = 0; i < 1; i++)
		for(int j = 0; j < n; j++)
		for(int k = 0; k < n; k++){
			(ret.m[i][j] += a.m[i][k] * b.m[k][j] ) %= MOD;
		}
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ret.m[i][(i + j) % n] = ret.m[0][j];
            }
        }
        return ret;
    }
 
	M pow(int e){
		M ret = I(), b;
		memcpy(b.m, m, sizeof(m));
		for(; e; e >>= 1){
			if(e & 1) ret = ret ^ b;
			b = b ^ b;
		}
		return ret;
	}
};

M cur;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cur.m[0][i] = x;
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int k, t; cin >> k >> t;
        M mm = M::I();
        /* M mmm = M::I(); */
        for (int i = 0; i < n; i++) {
            int pos = i + k;
            if (pos >= n) pos -= n;
            mm.m[i][pos]++;
            /* mmm.m[i][pos]++; */
        }
        /* for (int i = 1; i < 10; i++) { */
        /*     for (int j = 0; j < n; j++) { */
        /*         for (int k = 0; k < n; k++) { */
        /*             cout << mm.m[j][k] << ' '; */
        /*         } */
        /*         cout << '\n'; */
        /*     } */
        /*     cout << "--\n"; */
        /*     mm = mm * mmm; */
        /* } */
        mm = mm.pow(t);
        cur = cur * mm;
    }

    for (int i = 0; i < n; i++) {
        cout << cur.m[0][i] << ' ';
    }
    cout << '\n';

    return 0;
}
