#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m,L;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int F[maxN][2],P[maxN][2];
int top,Sorter[maxN],St[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int w);
void dfs1(int u,int fa);
void dfs2(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&L);
	for (int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);++u;++v;
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	int Ans=0,scnt=0;
	for (int i=1;i<=n;i++)
		if (vis[i]==0){
			top=0;dfs1(i,i);dfs2(i,i);
			//for (int i=1;i<=top;i++) cout<<St[i]<<" ";cout<<endl;
			for (int i=1;i<=top;i++) Ans=max(Ans,F[St[i]][0]+F[St[i]][1]);
			Sorter[++scnt]=inf;
			for (int i=1;i<=top;i++) Sorter[scnt]=min(Sorter[scnt],max(F[St[i]][0],F[St[i]][1]));
		}
	sort(&Sorter[1],&Sorter[scnt+1]);reverse(&Sorter[1],&Sorter[scnt+1]);
	if (scnt>=2) Ans=max(Ans,Sorter[1]+Sorter[2]+L);
	if (scnt>=3) Ans=max(Ans,Sorter[2]+Sorter[3]+L+L);
	printf("%d\n",Ans);return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs1(int u,int fa){
	St[++top]=u;vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i];dfs1(v,u);
			if (F[v][0]+W[i]>=F[u][0]){
				F[u][1]=F[u][0];P[u][1]=P[u][0];
				F[u][0]=F[v][0]+W[i];P[u][0]=v;
			}
			else if (F[v][0]+W[i]>F[u][1]) F[u][1]=F[v][0]+W[i],P[u][1]=v;
		}
	return;
}

void dfs2(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]==fa){
			if (P[fa][0]!=u){
				if (F[fa][0]+W[i]>=F[u][0]){
					F[u][1]=F[u][0];P[u][1]=P[u][0];
					F[u][0]=F[fa][0]+W[i];P[u][0]=fa;
				}
				else if (F[fa][0]+W[i]>F[u][1]) F[u][1]=F[fa][0]+W[i],P[u][1]=fa;
			}
			else if (P[fa][1]!=u){
				if (F[fa][1]+W[i]>=F[u][0]){
					F[u][1]=F[u][0];P[u][1]=P[u][0];
					F[u][0]=F[fa][1]+W[i];P[u][0]=fa;
				}
				else if (F[fa][1]+W[i]>F[u][1]) F[u][1]=F[fa][1]+W[i],P[u][1]=fa;
			}
		}
	for (int i=Head[u];i!=-1;i=Next[i]) if (V[i]!=fa) dfs2(V[i],u);
	return;
}
/*
12 8 2
0 8 4
8 2 2
2 7 4
5 11 3
5 1 7
1 3 1
1 9 5
10 6 3
//*/
