#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxN],V[maxN];
int indegree[maxN];
bool isleaf[maxN];
int Queue[maxN],Leafcnt[maxN];

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=2;i<=n;i++)
	{
		int u;scanf("%d",&u);
		edgecnt++;Next[edgecnt]=Head[i];Head[i]=edgecnt;V[edgecnt]=u;
		indegree[u]++;
	}
	int h=0,t=0;
	for (int i=1;i<=n;i++) if (indegree[i]==0) isleaf[Queue[++h]=i]=1;
	bool flag=1;
	do
	{
		int u=Queue[++t];
		if ((isleaf[u]==0)&&(Leafcnt[u]<3))
		{
			flag=0;
			break;
		}
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			indegree[V[i]]--;
			if (isleaf[u]==1) Leafcnt[V[i]]++;
			if (indegree[V[i]]==0) Queue[++h]=V[i];
		}
	}
	while (t!=h);
	if (flag) printf("Yes\n");
	else printf("No\n");
	return 0;
}
