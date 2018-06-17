#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=2050*6;
const int maxM=maxN*50;
const int F1[]={-1,0,1,0};
const int F2[]={0,1,0,-1};
const int inf=2147483647;

class Edge
{
public:
	int u,v,flow,w;
};

int n,m;
int S,T;
int Id[maxN][maxN][5];
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];

int main()
{
	scanf("%d%d",&n,&m);
	S=n*m*5+1;T=S+1;
	for (int idcnt=0,i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			for (int f=0;f<5;f++) Id[i][j][f]=++idcnt;
			int val;scanf("%d",&val);
			for (int f=0;f<4;f++)
				if ((val&(1<<f))!=0){
					if ((i+j)&1) Add_Edge(Id[][][]);
		}
}
