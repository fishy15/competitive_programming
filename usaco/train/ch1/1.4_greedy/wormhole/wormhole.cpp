/*
ID: aaryan.1
TASK: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iostream> 
#include <fstream>
#include <map>
#include <utility> 
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> points;
ll ans  = 0;

bool check(vector<ll> pairing) {
        for (int i = 1; i < pairing.size(); i++) {
                int reach = 0;
                //cout << "start\n";
                int loc = i;
                for (int j = 0; j < 24; j++) {
                        //cout << loc << endl;
                        loc = pairing[loc];
                        //cout << loc << endl;
                        if (loc == i) {
                                //cout << "done\n";
                                reach++;
                                //cout << "r" << reach << endl;
                        } 
                        
                        if (loc == pairing.size() - 1 || points[loc] != points[loc + 1]) {
                                break;
                        }

                        loc++;

                        if (loc == i) {
                                //cout << "done\n";
                                reach++;
                                //cout << "r" << reach << endl;
                        }

                        if (reach >= 2) {
                          //cout << "done for sure\n";
                          return true;
                        }
                }
        }

        return false;
}

void permutation(vector<ll> permutation, vector<bool> picked) {
	bool allTrue = true;
	for (ll i = 0; i < picked.size(); i++) {
		if (!picked[i]) {
			allTrue = false;
		}
	}

	if (allTrue) {
		if (check(permutation)) {
			ans++;
			
			for (ll i : permutation) {
				cout << i << " ";
			}
			cout << "\n";
			//*/
		}
	} else {
		for (ll i = 1; i < permutation.size() - 1; i++) {
			bool firstTime = false;
			for (ll j = i + 1; j < permutation.size(); j++) {
				if (!picked[i] && !picked[j]) {
					firstTime = true;
					vector<ll> newperm(permutation);
					vector<bool> newpick(picked);
					newperm[i] = j;
					newperm[j] = i;
					newpick[i] = true;
					newpick[j] = true;
					::permutation(newperm, newpick);
				}
			}
			
			if (firstTime) {
				break;
			}
		}
	}
}

ll fact(ll n) {
	if (n == 1) {
		return 1;
	}

	return n * fact(n - 1);
}


int main() {
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");
	//ofstream sorted("sorted.txt");

	ll n; fin >> n;

	map<ll, ll> rows;
	for (ll i = 0; i < n; i++) {
		ll x, y; fin >> x >> y;
		// ignore x value
		auto loc = rows.find(y);
		if (loc == rows.end()) {
			rows.insert({y, 1});
		} else {
			loc->second++;
		}
	}

	points = vector<ll>(n + 1, 0);
	vector<ll> partner(n + 1, 0);

	ll count = 1;
	for (auto it = rows.begin(); it != rows.end(); it++) {
		for (ll i = 0; i < it->second; i++) {
			points[count] = it->first;
			count++;
			//sorted << points[count - 1] << endl;
		}
	}

	vector<bool> picked;
	picked.push_back(true);
	for (ll i = 0; i < n; i++) {
		picked.push_back(false);
	}

	permutation(partner, picked);

	//cout << ::ans << "\n"

	fout << ::ans << "\n";

	return 0;
}

