#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;

const int maxsize=100001;
const int inf=2147483647;

int n,T;
vector<int> sons[maxsize];

int dp(int u);

int main()
{
	int i,j,k;
	while (cin>>n>>T) {
		if ((n==0)&&(T==0))
			break;
		for (i=0; i<=n; i++)
			sons[i].clear();
		for (i=1; i<=n; i++) {
			cin>>k;
			sons[k].push_back(i);
		}
		cout<<dp(0)<<endl;
	}
}

int dp(int u)
{
	if (sons[u].empty())
		return 1;
	int k=sons[u].size();
	vector<int> D;
	for (int i=0; i<k; i++)
		D.push_back(dp(sons[u][i]));
	sort(D.begin(),D.end());
	int c=(k*T-1)/100+1;
	int ans=0;
	for (int i=0; i<c; i++)
		ans+=D[i];
	return ans;
}
