#pragma GCC optimize ("Ofast")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef string str;

typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef pair<double, double> pd;
typedef pair<ld,ld> pld;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define rsz resize
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int) (x).size()
#define sor(x) sort(all(x))

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

template <typename T> inline T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
template <typename T> inline T lcm(T a, T b) { return a / gcd(a, b) * b; }
template <class T> void ckmin(T& a, T b) { a = min(a, b); }
template <class T> void ckmax(T& a, T b) { a = max(a, b); }

// (Integer/Long).bitCount(x)
int pct(int x) { return __builtin_popcount(x); }
int pctll(ll x) { return __builtin_popcountll(x); }

void setIn(string s) { freopen(s.c_str(),"r",stdin); }
void setOut(string s) { freopen(s.c_str(),"w",stdout); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
void setIO(string s = "") {
	unsyncIO();
	if (sz(s)) { setIn(s+".in"), setOut(s+".out"); }
}

ll pow(ll b, ll e, ll m = 0LL, ll ans = 1LL) { while (e) { if (e & 1LL) { ans *= b; if (m) ans %= m; } b *= b, e >>= 1LL; if (m) b %= m; } return ans; }
template <typename T> vector<T> readVector(int n) { vector<T> res(n); for (int i = 0 ; i < n ; i++) cin >> res[i]; return res; }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// shuffle(x.begin(), x.end(), rng);
// int y = uniform_int_distribution<int>(0, x)(rng); // [0, x]
// double y = uniform_real_distribution<double>(0, 1)(rng); // [0, 1]

const int MOD1 = 1e9+7; // 998244353;
const int MOD2 = 1e9+9;
const int MOD3 = 1e9+11;
const int mxN = 2e5+5;
const int INF = 2e9;
const ll INFLL = 1e18;
const ld PI = acos((ld)-1);
const ld EPS = 1e-12;
const int dx4[4] = {1, 0, -1, 0}, dy4[4] = {0, 1, 0, -1};
const int dx8[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const char nl = '\n';



void precomp() {
	setIO("");

}

void solve(int tcn) {
	int equationNum, variableNum;
	cin >> equationNum >> variableNum;
	if (equationNum == 0) {
		cout << variableNum << nl;
		F0R(i, variableNum) {
			int j = 0;
			for (; j < i; ++j) {
				cout << j + 1 << " ";
			}
			for (; j < variableNum; ++j) {
				cout << i + 1 << " ";
			}
			cout << nl;
		}
		return;
	}
	vector<vector<ll>> matrix1(equationNum, vector<ll>(variableNum, 0));
	vector<vector<ll>> matrix2(equationNum, vector<ll>(variableNum, 0));
	vector<vector<ll>> matrix3(equationNum, vector<ll>(variableNum, 0));
	set<int> unusedRows;
	vector<int> firstRow(variableNum, 0);
	F0R(i, equationNum) {
		F0R(j, variableNum) {
			cin >> matrix1[i][j];
			matrix2[i][j] = matrix1[i][j];
			matrix3[i][j] = matrix1[i][j];
			if (i == 0) {
				firstRow[j] = matrix1[0][j];
			}
		}
		unusedRows.ins(i);
	}
	set<int> Free;
	F0R(col, variableNum) {
		int pivotRow = -1;
		trav(row, unusedRows) {
			if (matrix1[row][col] != 0 && matrix2[row][col] != 0 && matrix3[row][col] != 0) {
				pivotRow = row;
				break;
			}
		}
		if (pivotRow == -1) {
			Free.ins(col);
			continue;
		}
		unusedRows.erase(pivotRow);
		trav(row, unusedRows) {
			if (matrix1[row][col] != 0 && matrix2[row][col] != 0 && matrix3[row][col] != 0) {
				ll factor1 = matrix1[row][col] * pow(matrix1[pivotRow][col], MOD1 - 2, MOD1) % MOD1;
				ll factor2 = matrix2[row][col] * pow(matrix2[pivotRow][col], MOD2 - 2, MOD2) % MOD2;
				ll factor3 = matrix3[row][col] * pow(matrix3[pivotRow][col], MOD3 - 2, MOD3) % MOD3;
				FOR(i, col, variableNum) {
					matrix1[row][i] -= factor1 * matrix1[pivotRow][i] % MOD1;
					matrix1[row][i] += MOD1;
					matrix1[row][i] %= MOD1;
					matrix2[row][i] -= factor2 * matrix2[pivotRow][i] % MOD2;
					matrix2[row][i] += MOD2;
					matrix2[row][i] %= MOD2;
					matrix3[row][i] -= factor3 * matrix3[pivotRow][i] % MOD3;
					matrix3[row][i] += MOD3;
					matrix3[row][i] %= MOD3;
				}
			}
		}
	}
	cout << sz(Free) << nl;
	trav(freeVar, Free) {
		F0R(i, variableNum) {
			if (i == freeVar) {
				cout << firstRow[i] + 1 << " ";
			} else {
				cout << firstRow[i] << " ";
			}
		}
		cout << nl;
	}
}

int main() {
	precomp();
    int t = 1; // cin >> t;
	for (int i = 1; i <= t; ++i) {
		//cout << "Case #" << i << ": ";
		solve(i);
	}
	return 0;
}
