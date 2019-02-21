#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int findQuasi(int n);

int main()
{
	int n; cin >> n;
	vector<int> ans; 
	while (n > 0)
	{
		int sub = findQuasi(n);
		ans.push_back(sub);
		n -= sub;
	}

	cout << ans.size() << endl;

	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << ' ';
	}

	cout << endl;
	return 0;
}

int findQuasi(int n)
{
	int ans = 0;
	int place = 0;

	while (n > 0)
	{
		if (n % 10 != 0)
		{
			ans += pow(10, place);
		}
		n /= 10;
		place++;
	}
	
	return ans;
}
