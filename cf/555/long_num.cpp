// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
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
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

int n; 
string num;
int m[10];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> n >> num;
    for (int i = 1; i < 10; i++) {
		cin >> m[i];
	}
	
	int l = 0;
	while (l < n && m[num[l] - '0'] <= num[l] - '0') {
	    //cout << m[num[l] - '0'] << ' ' << num[l] - '0' << '\n';
		l++;
	}
	
	int r = l;
	while (r < n && m[num[r] - '0'] >= num[r] - '0') {
		r++;
	}
	
	//cerr << "L: " << l << ' ' << r << '\n';
	
	for (int i = 0; i < n; i++) {
		if (l <= i && i < r) {
			cout << m[num[i] - '0'];
		} else {
			cout << num[i];
		}
	}
	
	cout << '\n';

    return 0;
}
