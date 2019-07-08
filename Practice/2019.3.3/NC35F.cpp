#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=303000;
const int maxM=maxN<<1;
const int maxB=19;

class Edge
{
public:
	int x,y,k;
	ll w;
};

int n,m;
int Fa[maxB][maxN],ufs[maxB][maxN],Sz[maxN];
Edge E[maxN];
ll Cost[maxN];

bool ecmp(Edge A,Edge B);
int find(int b,int x);
void Merge(int b,int u,int v,ll w);
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=2; i<=n; i++) scanf("%d",&Fa[0][i]);
	for (int i=1; i<maxB; i++) for (int j=1; j<=n; j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	for (int i=0; i<maxB; i++) for (int j=1; j<=n; j++) ufs[i][j]=j;
	for (int i=1; i<=n; i++) Sz[i]=1;
	for (int i=1; i<=m; i++) scanf("%d%d%d%lld",&E[i].x,&E[i].y,&E[i].k,&E[i].w);
	sort(&E[1],&E[m+1],ecmp);
	for (int i=1; i<=m; i++) {
		int u=E[i].x,v=E[i].y;
		for (int j=maxB-1; j>=0; j--)
			if ((E[i].k>>j)&1) {
				//cout<<"M:"<<j<<" "<<u<<" "<<v<<" "<<E[i].w<<endl;
				Merge(j,u,v,E[i].w);
				u=Fa[j][u];
				v=Fa[j][v];
			}
	}
	ll anssize=0,anscost=0;
	//for (int i=1;i<=n;i++) cout<<find(0,i)<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Cost[i]<<" "<<Sz[i]<<endl;
	for (int i=1; i<=n; i++) if (find(0,i)==i) if (anssize<Sz[i]||(anssize<=Sz[i]&&Cost[i]<anscost)) anssize=Sz[i],anscost=Cost[i];
	printf("%lld %lld\n",anssize,anscost);
	return 0;
}
bool ecmp(Edge A,Edge B)
{
	return A.w<B.w;
}
int find(int b,int x)
{
	if (ufs[b][x]!=x) ufs[b][x]=find(b,ufs[b][x]);
	return ufs[b][x];
}
void Merge(int b,int u,int v,ll w)
{
	int fu=find(b,u),fv=find(b,v);
	if (fu!=fv) {
		if (b) Merge(b-1,u,v,w),Merge(b-1,Fa[b-1][u],Fa[b-1][v],w);
		else Sz[fu]+=Sz[fv],Cost[fu]+=Cost[fv]+w;
		ufs[b][fv]=fu;
	}
	return;
}