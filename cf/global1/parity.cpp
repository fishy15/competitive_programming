// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:

#include <iostream>

using namespace std;

int nums[100001];

int main() {
	int b, k; cin >> b >> k;
	int sum = 0;
	
	for (int i = 0; i < k; i++) {
		cin >> nums[i];
		sum += nums[i]; 
	}
	
	int val = 0;
	if (b % 2 == 0) {
		val = nums[k - 1] % 2;
	} else {
		val = sum % 2;
	}
	
	if (val == 0) {
		cout << "even\n";
	} else {
		cout << "odd\n";
	}
	
	return 0;
}