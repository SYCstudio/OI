#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Block=330;
const int maxM=maxN<<1;

int n,m,root,B,Bc;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],lst[maxN],L[maxN],R[maxN];
ull NW[maxN],BAns[maxN],BLal[maxN],Sum[maxN];
int Bl[maxN],To[maxN][Block];

void Add_Edge(int u,int v);
void dfs(int u,int fa);
ull Query(int l,int r);

int main()
{
	//freopen("in","r",stdin);
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	B=sqrt(n);
	Bc=n/B+1;
	for (int i=1; i<=n; i++) scanf("%llu",&NW[i]);
	for (int i=1; i<=n; i++) {
		Bl[i]=i/B+1;
		R[Bl[i]]=i;
		if (L[Bl[i]]==0) L[Bl[i]]=i;
	}
	//cout<<B<<endl;
	//for (int i=1;i<=n;i++) cout<<Bl[i]<<" ";cout<<endl;
	//for (int i=1;i<=Bc;i++) cout<<"("<<L[i]<<" "<<R[i]<<") ";cout<<endl;
	for (int i=1; i<=n; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		if (a==0) {
			root=b;
			continue;
		}
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	dfs(root,0);
	for (int i=1; i<=n; i++)
		for (int j=1; j<=Bc; j++)
			BAns[j]+=NW[i]*To[i][j];
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=Bc;j++)
			cout<<To[i][j]<<" ";
		cout<<endl;
	}
	//*/
	for (int i=1; i<=n; i++) Sum[i]+=Sum[i-1];
	//cout<<"BAns:";for (int i=1;i<=Bc;i++) cout<<BAns[i]<<" ";cout<<endl;

	while (m--) {
		int opt,a;
		ull b;
		scanf("%d%d%llu",&opt,&a,&b);
		if (opt==1) {
			b-=NW[a];
			for (int i=1; i<=Bc; i++) BAns[i]+=1ll*b*To[a][i];
			for (int i=dfn[a]; i<=R[Bl[dfn[a]]]; i++) Sum[i]+=b;
			for (int i=Bl[dfn[a]]+1; i<=Bl[n]; i++) BLal[i]+=b;
			NW[a]+=b;
		} else {
			ull Ans=0;
			if (Bl[a]==Bl[b]) for (int i=a; i<=b; i++) Ans=Ans+Query(dfn[i],lst[i]);
			else {
				for (int i=Bl[a]+1; i<=Bl[b]-1; i++) Ans=Ans+BAns[i]; //cout<<Ans<<endl;
				for (int i=a; i<=R[Bl[a]]; i++) Ans=Ans+Query(dfn[i],lst[i]); //cout<<Ans<<endl;
				for (int i=L[Bl[b]]; i<=b; i++) Ans=Ans+Query(dfn[i],lst[i]); //cout<<Ans<<endl;
				//cout<<"("<<Bl[a]+1<<","<<Bl[b]-1<<") "<<a<<" "<<R[Bl[a]]<<" | "<<L[Bl[b]]<<" "<<b<<endl;
			}
			printf("%llu\n",Ans);
		}

		//for (int i=1;i<=n;i++) cout<<Query(dfn[i],lst[i])<<" ";cout<<endl;
		//for (int i=1;i<=Bc;i++) cout<<BAns[i]<<" ";cout<<endl;
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs(int u,int fa)
{
	++To[u][Bl[u]];
	dfn[u]=++dfncnt;
	Sum[dfn[u]]=NW[u];
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			for (int j=1; j<=Bc; j++) To[V[i]][j]=To[u][j];
			dfs(V[i],u);//Sum[dfn[u]]+=Sum[dfn[V[i]]];
		}
	lst[u]=dfncnt;
	return;
}
ull Query(int l,int r)
{
	//cout<<"("<<l<<","<<r<<") "<<(Sum[r]+BLal[Bl[r]])<<" "<<(Sum[l-1]+BLal[Bl[l-1]])<<endl;
	return (Sum[r]+BLal[Bl[r]])-(Sum[l-1]+BLal[Bl[l-1]]);
}
/*
6 4
0 0 3 4 0 1
0 1
1 2
2 3
2 4
3 5
5 6
2 1 2
1 1 1
2 3 6
2 3 5
//*/
