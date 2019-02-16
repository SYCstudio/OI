#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxM=maxN<<1;
const int maxBit=20;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Fa[maxBit][maxN],Depth[maxN],Hson[maxN],MxD[maxN],Top[maxN];
vector<int> Up[maxN],Down[maxN];
int HighBit[maxN];

int Input();
void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
int Query(int u,int k);

int main(){
	//freopen("in.in","r",stdin);
	HighBit[1]=0;
	for (int i=2;i<maxN;i++) HighBit[i]=HighBit[i>>1]+1;
	mem(Head,-1);
	
	n=Input();//scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u=Input(),v=Input();//scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Depth[1]=1;dfs1(1,1);dfs2(1,1);

	for (int i=1;i<=n;i++)
		if (Top[i]==i){
			//Up[i].push_back(i);Down[i].push_back(i);
			int len=MxD[i]-Depth[i]+1;
			for (int j=Fa[0][i],k=1;(j!=0)&&(k<=len);j=Fa[0][j],k++) Up[i].push_back(j);
			for (int j=Hson[i],k=1;k<=len;j=Hson[j],k++) Down[i].push_back(j);
		}

	/*
	for (int i=1;i<=n;i++) cout<<MxD[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++){
		cout<<i<<":"<<endl<<"Down:";
		for (int sz=Down[i].size(),j=0;j<sz;j++) cout<<Down[i][j]<<" ";
		cout<<endl<<"Up:";
		for (int sz=Down[i].size(),j=0;j<sz;j++) cout<<Up[i][j]<<" ";cout<<endl;
	}
	//*/

	/*
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if (Fa[i-1][j])
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	//*/

	int Q=Input(),lastans=0;//scanf("%d",&Q);
	while (Q--){
		int u=Input(),k=Input();//scanf("%d%d",&u,&k);
		//cout<<u<<" "<<k<<" "<<Depth[u]<<endl;
		u^=lastans;k^=lastans;//-----------------------------------------------------------------
		printf("%d\n",lastans=Query(u,k));
	}

	return 0;
}

int Input(){
	int x=0;char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	for (int i=1;i<maxBit;i++)
		if (Fa[i-1][u]) Fa[i][u]=Fa[i-1][Fa[i-1][u]];
		else break;
	MxD[u]=Depth[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Depth[V[i]]=Depth[u]+1;Fa[0][V[i]]=u;
			dfs1(V[i],u);
			if (MxD[V[i]]>MxD[u]) Hson[u]=V[i],MxD[u]=MxD[V[i]];
		}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;
	/*
	if (u==top){
		Up[u].push_back(u);Down[u].push_back(u);
		for (int i=Fa[0][u],j=1;(i!=0)&&(j<=MxD[u]);i=Fa[0][i],j++) Up[u].push_back(i);
	}
	else Down[top].push_back(u);
	//*/

	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[0][u])&&(V[i]!=Hson[u]))
			dfs2(V[i],V[i]);
	return;
}

int Query(int u,int k){
	if (Depth[u]<=k) return 0;
	if (k==0) return u;
	u=Fa[HighBit[k]][u];k-=(1<<HighBit[k]);
	if (k==0) return u;
	int len=Depth[u]-Depth[Top[u]];
	if (len==k) return Top[u];
	else if (len>k) return Down[Top[u]][len-k-1];
	else return Up[Top[u]][k-len-1];
}

/*
13
1 2
1 8
2 3
2 4
2 5
2 6
4 7
8 9
8 12
8 13
9 10
10 11
10
10 3
5 1
7 2
11 2
11 3
11 1
5 1
13 2
4 2
7 5
//*/
