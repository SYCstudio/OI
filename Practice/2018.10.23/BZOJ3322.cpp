#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000<<1;
const int maxM=201000<<1;
const int maxBit=20;
const int inf=2147483647;
const ll INF=1e17;

class Edge
{
public:
	int u,v;ll w;
};

int n,m,Q;
int Seq[maxN],Limit[maxN],UFS[maxN],Dph[maxN];
int Fa[maxBit][maxN];
Edge E[maxM];
ll NW[maxN],W[maxN],Ans[maxN];

bool cmp(Edge A,Edge B);
int Find(int u);

int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	for (int i=1;i<=n;i++) scanf("%d",&Limit[i]);
	for (int i=1;i<=m;i++) scanf("%d%d%lld",&E[i].u,&E[i].v,&E[i].w);
	for (int i=1;i<=Q;i++){
		int u;scanf("%d",&u);
		E[++m]=((Edge){u,n+1,INF});
	}
	sort(&E[1],&E[m+1],cmp);int nn=n;n++;
	for (int i=1;i<=n;i++) UFS[i]=i,NW[i]=INF;
	for (int i=1;i<=m;i++)
		if (Find(E[i].u)!=Find(E[i].v)){
			NW[++n]=E[i].w;UFS[n]=n;Fa[0][Find(E[i].u)]=Fa[0][Find(E[i].v)]=n;
			UFS[Find(E[i].u)]=n;
			UFS[Find(E[i].v)]=n;
		}

	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if (Fa[i-1][j]) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	for (int i=n;i>=1;i--) Dph[i]=Dph[Fa[0][i]]+1;

	for (int i=1;i<nn;i++){
		int u=Seq[i],v=Seq[i+1];
		if (Dph[u]<Dph[v]) swap(u,v);
		for (int j=maxBit-1;j>=0;j--) if ((Fa[j][u])&&(Dph[Fa[j][u]]>=Dph[v])) u=Fa[j][u];
		if (u!=v) for (int j=maxBit-1;j>=0;j--) if ((Fa[j][u])&&(Fa[j][v])&&(Fa[j][u]!=Fa[j][v])) u=Fa[j][u],v=Fa[j][v];
		if (u!=v) u=Fa[0][u];
		W[i]=NW[u];
	}
	//cout<<"W:";for (int i=1;i<n;i++) cout<<W[i]<<" ";cout<<endl;
	ll res=(Limit[Seq[1]]>0)?(Limit[Seq[1]]):(0);
	for (int i=2;i<=nn;i++){
		res=min(res,W[i-1]);
		//cout<<i<<":"<<res<<endl;
		if (Limit[Seq[i]]<0) Ans[i]=min((ll)-Limit[Seq[i]],res),res-=Ans[i];
		else res=res+Limit[Seq[i]];
	}
	for (int i=1;i<=nn;i++) if (Limit[Seq[i]]<0) printf("%lld\n",Ans[i]);
	return 0;
}

bool cmp(Edge A,Edge B){
	return A.w>B.w;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
