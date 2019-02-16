#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=maxN<<1;
const int maxK=55;
const int inf=2147483647;

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM],Depth[maxN],Size[maxN];
int F[maxN][maxN][maxK],G[maxN][maxN],St[maxN],NW[maxN];

void Add_Edge(int u,int v,int w);
void dfs(int u,int fa,int dep);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&K);K++;
	for (int i=1;i<=n;i++){
		int w,v,d;scanf("%d%d%d",&w,&v,&d);NW[i+1]=w;v++;
		Add_Edge(i+1,v,d);Add_Edge(v,i+1,d);
	}
	n++;

	Depth[1]=0;
	dfs(1,1,1);

	printf("%d\n",F[1][1][K]);

	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs(int u,int fa,int dep){
	St[dep]=u;Size[u]=1;
	for (int d=1;d<dep;d++) F[u][St[d]][1]=NW[u]*(Depth[u]-Depth[St[d]]);
	
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i];Depth[v]=Depth[u]+W[i];//cout<<u<<"->"<<v<<endl;
			dfs(v,u,dep+1);
			for (int d=1;d<=dep;d++) for (int s=1;s<=min(K,Size[u]+Size[v]);s++) G[St[d]][s]=inf;
			for (int d=1;d<=dep;d++)
				for (int s=1;s<=min(K,Size[u]);s++)
					for (int ss=1;ss+s-1<=min(Size[u]+Size[v],K);ss++)
						G[St[d]][s+ss-1]=min(G[St[d]][s+ss-1],F[u][St[d]][s]+F[v][St[d]][ss]);
			for (int d=1;d<=dep;d++)
				for (int s=1;s<=min(K,Size[u]);s++)
					for (int ss=1;s+ss<=min(Size[u]+Size[v],K);ss++)
						G[St[d]][s+ss]=min(G[St[d]][s+ss],F[u][St[d]][s]+F[v][v][ss]);
			for (int d=1;d<=dep;d++) for (int s=1;s<=min(K,Size[u]+Size[v]);s++) F[u][St[d]][s]=G[St[d]][s];
			Size[u]+=Size[v];
			/*
			cout<<"after:"<<u<<" -> "<<v<<endl;
			cout<<"node:"<<u<<endl;
			for (int d=1;d<=dep;d++){
				cout<<"to:"<<St[d]<<endl;
				for (int j=1;j<=min(Size[u],K);j++) cout<<F[u][St[d]][j]<<" ";
				cout<<endl;
			}
			cout<<endl;
			//*/
		}
	/*
	cout<<"finish "<<u<<endl;
	for (int d=1;d<=dep;d++){
		cout<<"to:"<<St[d]<<endl;
		for (int j=1;j<=min(Size[u],K);j++) cout<<F[u][St[d]][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	//*/
	return;
}
