#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,B;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int top=0,St[maxN];
int blockcnt,Belong[maxN],Center[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&B);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}

	dfs(1,0);
	while (top) Belong[St[top--]]=blockcnt;

	printf("%d\n",blockcnt);
	for (int i=1;i<=n;i++) printf("%d ",Belong[i]);printf("\n");
	for (int i=1;i<=blockcnt;i++) printf("%d ",Center[i]);printf("\n");
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs(int u,int fa)
{
	int nowtop=top;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dfs(V[i],u);
			if (top-nowtop>=B)
			{
				Center[++blockcnt]=u;
				while (top!=nowtop) Belong[St[top--]]=blockcnt;
			}	
		}
	St[++top]=u;
	return;
}

/*
8 2 
1 2 
2 3 
1 8 
8 7 
8 6 
4 6 
6 5
//*/
