#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,limit;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN],Fa[maxN];
int Seq[maxN],Qe[maxN],MxL[maxN],MxR[maxN],D[maxN];
bool mark[maxN];

void Add_Edge(int u,int v,int w);
void dfs_init(int u,int fa);
void dfs_calc(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&limit);
	int sum=0;
	for (int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);sum+=w;
	}

	Dist[1]=0;Fa[1]=0;
	dfs_init(1,1);
	int id=1;for (int i=2;i<=n;i++) if (Dist[id]<Dist[i]) id=i;
	Dist[id]=0;Fa[id]=0;
	dfs_init(id,id);
	id=1;for (int i=2;i<=n;i++) if (Dist[id]<Dist[i]) id=i;

	int scnt=0;
	for (int now=id;now!=0;now=Fa[now]) mark[Seq[++scnt]=now]=1;
	for (int i=1;i<scnt;i++) for (int j=Head[Seq[i]];j!=-1;j=Next[j]) if (V[j]==Seq[i+1]) D[i]=W[j];

	//for (int i=1;i<=scnt;i++) cout<<Seq[i]<<" ";cout<<endl;
	//for (int i=1;i<scnt;i++) cout<<D[i]<<" ";cout<<endl;

	for (int i=1;i<=scnt;i++){
		Dist[Seq[i]]=0;dfs_calc(Seq[i],Seq[i]);
	}

	for (int i=1;i<=scnt;i++) MxL[i]=max(Dist[Seq[i]],MxL[i-1]+D[i-1]);
	for (int i=scnt;i>=1;i--) MxR[i]=max(Dist[Seq[i]],MxR[i+1]+D[i]);

	int R=1,l=1,r=0,Ans=inf;
	for (int L=1,dist=0;L<=scnt;L++){
		while ((l<=r)&&(Seq[Qe[l]]<L)) l++;
		while ((R!=scnt)&&(D[R]+dist<=limit)){
			dist+=D[R];R++;
			while ((l<=r)&&(Dist[Seq[Qe[r]]]<=Dist[Seq[R]])) r--;
			Qe[++r]=R;
		}
		Ans=min(Ans,max(Dist[Seq[Qe[l]]],max(MxL[L],MxR[R])));
		dist-=D[L];
	}

	printf("%d\n",Ans);

	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs_init(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Dist[V[i]]=Dist[u]+W[i];dfs_init(V[i],Fa[V[i]]=u);
		}
	return;
}

void dfs_calc(int u,int fa){
	int mx=Dist[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(mark[V[i]]==0)){
			Dist[V[i]]=Dist[u]+W[i];dfs_calc(V[i],u);mx=max(mx,Dist[V[i]]);
		}
	Dist[u]=mx;return;
}
