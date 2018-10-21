#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int maxM=maxN<<1;
const int inf=2147483647;
const ll INF=1e17;

class Data
{
public:
	ll key,cnt;
};

int n,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
Data Ans,F[maxN][3];

void Add_Edge(int u,int v,int w);
int Calc(ll limit);
void dfs(int u,int fa,ll limit);
bool operator < (Data A,Data B);
Data operator + (Data A,Data B);
void Update(Data &A,Data B);

int main(){
	mem(Head,-1);
	ll Mx=0,Mn=0;
	scanf("%d%d",&n,&K);K++;
	for (int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
		Mx+=abs(w);Mn-=abs(w);
	}

	ll L=Mn,R=Mx,pos=0;
	do{
		ll mid=(L+R)>>1;
		if (Calc(mid)>=K) pos=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);

	Calc(pos);

	printf("%lld\n",Ans.key+1ll*K*pos);

	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

int Calc(ll limit){
	dfs(1,1,limit);
	Ans=((Data){-INF,0});
	for (int i=1;i<=n;i++) Update(Ans,max(F[i][0],max(F[i][1],F[i][2])));
	return Ans.cnt;
}

void dfs(int u,int fa,ll limit){
	F[u][0]=((Data){0,0});F[u][1]=((Data){-limit,1});F[u][2]=((Data){-INF,0});
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i],w=W[i];
			dfs(v,u,limit);
			Data P=max(F[v][0],max(F[v][1],F[v][2]));
			Update(F[u][2],F[u][2]+P);
			Update(F[u][2],F[u][1]+F[v][1]+((Data){w+limit,-1}));
			Update(F[u][1],F[u][1]+P);
			Update(F[u][1],F[u][0]+F[v][1]+((Data){w,0}));
			Update(F[u][1],F[u][0]+F[v][0]+((Data){-limit,1}));
			Update(F[u][0],F[u][0]+P);
		}
	return;
}

bool operator < (Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	else return A.cnt<B.cnt;
}

Data operator + (Data A,Data B){
	return ((Data){A.key+B.key,A.cnt+B.cnt});
}

void Update(Data &A,Data B){
	if (A<B) A=B;
}
