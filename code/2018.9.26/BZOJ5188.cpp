#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100*2;
const int maxBit=20;
const int inf=2147483647;

class Edge
{
public:
	int u,v,w;
};

int n,Q;
int nodecnt=0,Fa[maxBit][maxN],NodeW[maxN],UFS[maxN],Size[maxN];
Edge E[maxN];

bool cmp(Edge A,Edge B);
int Find(int x);

int main(){
	//freopen("in.in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&Q);nodecnt=n;
	for (int i=1;i<n;i++) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	for (int i=1;i<=n;i++) UFS[i]=i,NodeW[i]=inf,Size[i]=1;
	sort(&E[1],&E[n],cmp);
	for (int i=1;i<n;i++){
		++nodecnt;
		int u=Find(E[i].u),v=Find(E[i].v);
		//cout<<E[i].u<<" "<<E[i].v<<" "<<rt[E[i].u]<<" "<<rt[E[i].v]<<" "<<E[i].w<<endl;
		Fa[0][u]=Fa[0][v]=nodecnt;
		Size[nodecnt]=Size[u]+Size[v];
		NodeW[nodecnt]=E[i].w;UFS[u]=UFS[v]=nodecnt;UFS[nodecnt]=nodecnt;
	}
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=nodecnt;j++)
			if (Fa[i-1][j]) Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	/*
	for (int i=0;i<=3;i++)
		for (int j=1;j<=nodecnt;j++)
			cout<<"("<<i<<" "<<j<<") "<<Fa[i][j]<<endl;
	//*/

	while (Q--){
		int k,v;scanf("%d%d",&k,&v);
		for (int i=maxBit-1;i>=0;i--) if ((Fa[i][v])&&(NodeW[Fa[i][v]]>=k)) v=Fa[i][v];
		//cout<<k<<" "<<v<<" "<<NodeW[v]<<" "<<Fa[0][v]<<endl;
		printf("%d\n",Size[v]-1);
	}

	return 0;
}

bool cmp(Edge A,Edge B){
	return A.w>B.w;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
