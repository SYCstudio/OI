#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=300;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

int n,m;
int B1[maxN];
int B2[maxN];
int F1[maxN];
int F2[maxN];
int Cost[maxN];
int Q[1<<41];
int Dist[1<<41];
bool inqueue[1<<41];

void Add_Edge(int u,int v,int cost);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		char str[maxN];
		scanf("%d%s",&Cost[i],str);
		for (int j=0;j<n;j++)
			if (str[j]=='+')
				B1[i]=B1[i]|(1<<(j));
			else
				if (str[j]=='-')
					B2[i]=B2[i]|(1<<j);
		scanf("%s",str);
		for (int j=0;j<n;j++)
			if (str[j]=='+')
				F1[i]=F1[i]|(1<<j);
			else
				if (str[j]=='-')
					F2[i]=F2[i]|(1<<j);
	}
	int h=1,t=0;
	Q[1]=(1<<n)-1;
	
}
