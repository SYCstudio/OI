#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxNum=1000000;
const int maxM=maxN*10;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
int num[maxN],F[2][maxN],Pow[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
bool ink[maxN],fob[maxN];
int timcnt,Tim[maxN];
int top,St[maxN],Dph[maxN];

void Add_Edge(int u,int v);
int Solve(int u);
void dfs1(int u,int fa);
void dfs2(int u,int fa);
bool dfs_check(int u,int fa);

int main(){
	//freopen("in","r",stdin);freopen("1","w",stdout);
	mem(Head,-1);
	Pow[0]=1;for (int i=1;i<maxN;i++) Pow[i]=2ll*Pow[i-1]%Mod;
	for (int i=2;i<=maxNum;i++)
		for (int j=sqrt(max(1ll,1ll*i*i-maxNum));(2ll*i*j<=maxNum)&&(j<=i);j++){
			ll x=1ll*i*i,y=1ll*j*j;
			if ( (__gcd(x-y,2ll*i*j)==1) && ((x-y)*(x-y)+4ll*x*y==(x+y)*(x+y)) ){
				Add_Edge(x-y,2ll*i*j);//++cnt;//cout<<x-y<<" "<<2ll*i*j<<endl;
			}
		}

	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		num[x]++;
	}

	int Ans=1;
	for (int i=1;i<=maxNum;i++)
		if ((Tim[i]==0)&&(num[i])) Ans=1ll*Ans*Solve(i)%Mod;
	printf("%d\n",(Ans-1+Mod)%Mod);return 0;
}

void Add_Edge(int u,int v){
	//if ((u<=100)&&(v<=100)) cout<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

int Solve(int u){
	top=0;Dph[u]=1;timcnt++;
	//cout<<"Solve:"<<u<<endl;
	dfs1(u,0);
	sort(&St[0],&St[top]);top=unique(&St[0],&St[top])-St;
	//if (top){cout<<"St:["<<top<<"] ";for (int i=0;i<top;i++) cout<<St[i]<<" ";cout<<endl;}
	ll ret=0;
	for (int S=0;S<(1<<top);S++){
		for (int i=0;i<top;i++)
			if (S&(1<<i)) fob[St[i]]=1;
			else fob[St[i]]=0;
		//for (int i=0;i<top;i++) cout<<fob[St[i]];cout<<endl;
		timcnt++;
		if (dfs_check(u,0)==0) continue;
		timcnt++;
		dfs2(u,0);
		ret=(ret+F[0][u]+F[1][u])%Mod;
		//cout<<F[0][u]<<" "<<F[1][u]<<endl;
	}
	//cout<<ret<<endl;
	return ret;
}

void dfs1(int u,int fa){
	//cout<<"dfs1:"<<u<<" "<<fa<<endl;
	Tim[u]=timcnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(num[V[i]])){
			if (Tim[V[i]]!=timcnt) dfs1(V[i],u);
			else{
				ink[u]=ink[V[i]]=1;
				St[top++]=u;St[top++]=V[i];
			}
		}
	return;
}

void dfs2(int u,int fa){
	Tim[u]=timcnt;
	//cout<<"dfs2:"<<u<<" "<<fa<<endl;
	F[0][u]=1;F[1][u]=(Pow[num[u]]-1+Mod)%Mod;
	if (ink[u]) F[fob[u]^1][u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(num[V[i]])&&(Tim[V[i]]!=timcnt)){
			dfs2(V[i],u);
			F[0][u]=1ll*F[0][u]*(F[1][V[i]]+F[0][V[i]])%Mod;
			F[1][u]=1ll*F[1][u]*F[0][V[i]]%Mod;
		}
	//cout<<"dp:"<<u<<" "<<F[0][u]<<" "<<F[1][u]<<endl;
	return;
}


bool dfs_check(int u,int fa){
	Tim[u]=timcnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(num[V[i]])){
			if ((ink[u])&&(ink[V[i]])&&(fob[u])&&(fob[V[i]])) return 0;
			if (Tim[V[i]]==timcnt) continue;
			if (dfs_check(V[i],u)==0) return 0;
		}
	return 1;
}
/*
4
5 12 35 5
//*/


