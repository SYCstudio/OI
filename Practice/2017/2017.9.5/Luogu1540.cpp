#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxNum=2000;
const int maxN=200;
const int inf=2147483647;

int n,m;
int Hash[maxNum];
queue<int> Q;

int main()
{
	scanf("%d%d",&m,&n);
	memset(Hash,0,sizeof(Hash));
	int Ans=0;
	int siz=0;
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if (Hash[x]==1)
			continue;
		//cout<<x<<" ";
		Ans++;
		if (siz<m)
		{
			siz++;
			Hash[x]=1;
			Q.push(x);
		}
		else
		{
			Hash[Q.front()]=0;
			Q.pop();
			Q.push(x);
			Hash[x]=1;
		}
	}
	//cout<<endl;
	printf("%d\n",Ans);
	return 0;
}
