#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int maxM=maxN*10;
const int maxBit=19;
const int inf=2147483647;

int n,m,nodecnt;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],low[maxN],last[maxN],top,St[maxN];
vector<int> T[maxN];
int Depth[maxN],Fa[maxBit][maxN],Dist[maxN];
int Seq[maxN],Mark[maxN];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void dfs_fa(int u,int fa);
int LCA(int u,int v);
bool cmp(int a,int b);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		//cout<<"now:"<<TTT<<endl;
		edgecnt=-1;mem(Head,-1);mem(dfn,0);dfncnt=0;top=0;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n+n;i++) T[i].clear();

		for (int i=1;i<=m;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			Add_Edge(u,v);
		}

		nodecnt=n;
		tarjan(1,0);

		dfncnt=0;Depth[1]=1;Dist[1]=1;
		dfs_fa(1,0);
		for (int i=1;i<maxBit;i++)
			for (int j=1;j<=nodecnt;j++)
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];

		/*
		for (int i=1;i<=nodecnt;i++)
			for (int j=0;j<T[i].size();j++)
				cout<<i<<"->"<<T[i][j]<<endl;
		//*/
        /*
		cout<<"Init finish"<<endl;

		for (int i=1;i<=nodecnt;i++) cout<<Depth[i]<<" ";cout<<endl;
		for (int i=1;i<=nodecnt;i++) cout<<Dist[i]<<" ";cout<<endl;
		for (int i=1;i<=nodecnt;i++) cout<<Depth[i]<<" ";cout<<endl;
		//*/
		
		int Q;scanf("%d",&Q);
		
		while (Q--)
		{
			int ncnt;scanf("%d",&ncnt);
			for (int i=1;i<=ncnt;i++) scanf("%d",&Seq[i]),Mark[Seq[i]]=1;
			sort(&Seq[1],&Seq[ncnt+1],cmp);
			//for (int i=1;i<=ncnt;i++) cout<<Seq[i]<<" ";cout<<endl;
			for (int i=1;i<ncnt;i++) Seq[ncnt+i]=LCA(Seq[i],Seq[i+1]);
			sort(&Seq[1],&Seq[ncnt+ncnt],cmp);
			ncnt=unique(&Seq[1],&Seq[ncnt+ncnt])-Seq-1;
			//cout<<ncnt<<":";for (int i=1;i<=ncnt;i++) cout<<Seq[i]<<" ";cout<<endl;

			top=0;
			int Ans=0;
			for (int i=1;i<=ncnt;i++)
			{
				while ((top)&&(last[St[top]]<dfn[Seq[i]])) top--;
				if (top) Ans=Ans+Dist[Fa[0][Seq[i]]]-Dist[St[top]];
				//if (top) cout<<Seq[i]<<" "<<St[top]<<":"<<Dist[Fa[0][Seq[i]]]-Dist[St[top]]<<endl;
				St[++top]=Seq[i];
			}
			for (int i=1;i<=ncnt;i++) if ((Mark[Seq[i]]==0)&&(Seq[i]<=n)) Ans++;

			printf("%d\n",Ans);
			for (int i=1;i<=ncnt;i++) Mark[Seq[i]]=0;
		}
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;St[++top]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i];
			if (dfn[v]==0){
				tarjan(v,u);low[u]=min(low[u],low[v]);
				if (low[v]>=dfn[u])
				{
					nodecnt++;T[nodecnt].clear();int w;
					do{
						w=St[top--];
						T[w].push_back(nodecnt);T[nodecnt].push_back(w);
					}
					while (w!=v);
					T[u].push_back(nodecnt);T[nodecnt].push_back(u);
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
	return;
}

void dfs_fa(int u,int fa)
{
	int sz=T[u].size();dfn[u]=++dfncnt;
	for (int i=0;i<sz;i++)
		if (T[u][i]!=fa){
			Depth[T[u][i]]=Depth[u]+1;Fa[0][T[u][i]]=u;
			if (T[u][i]<=n) Dist[T[u][i]]=Dist[u]+1;
			else Dist[T[u][i]]=Dist[u];
			dfs_fa(T[u][i],u);
		}
	last[u]=dfncnt;
	return;
}

int LCA(int u,int v)
{
	//cout<<"LCA:"<<u<<" "<<v<<":";
	if (Depth[u]<Depth[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
/*
1
10 11
1 2
1 3
2 3
2 4
2 5
4 7
5 7
4 6
5 8
8 9
9 10
1
2 6 8
//*/
