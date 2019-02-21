#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string extra; cin >> extra;
	vector<int> alpha;
	for (int i = 0; i < 26; i++) 
	{
		alpha.push_back(0);
	}
	
	for (int i = 0; i < extra.size(); i++)
	{
		alpha[extra[i] - 'a']++;
	}
	
	int sum = 0;
	for (int i = 0; i < alpha.size(); i++)
	{
		if (alpha[i] > 0)
		{
			sum++;
		}
	}
	
	cout << 26 * (sum + 1) - sum << endl;
	return 0;
}
