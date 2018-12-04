#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30100<<1;
const int maxM=maxN<<1;
const ld Pi=acos(-1);
const int inf=2147483647;

class Complex
{
public:
	ld x,y;
	/*
	Complex(){}
	Complex(ld a,ld b){
		x=a;y=b;return;
	}
	//*/
};

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
Complex F[maxN],Wn[maxN];
ld Sum[maxN];
int root,nowsize,Sz[maxN],Mx[maxN],mxd;
bool vis[maxN];
int Rader[maxN];

Complex operator + (Complex A,Complex B);
Complex operator - (Complex A,Complex B);
Complex operator * (Complex A,Complex B);
void Add_Edge(int u,int v);
void dfs_root(int u,int fa);
void Solve(int u);
void dfs_get(int u,int fa,int d);
void Mul(int mxd,int opt);
void FFT(Complex *P,int N,int opt);

int main(){
	mem(Head,-1);scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);++u;++v;
		Add_Edge(u,v);Add_Edge(v,u);
	}
	root=0;Mx[0]=inf;dfs_root(1,1);
	Solve(1);
	ld Ans=0;
	for (int i=0;i<=n;i++) Ans+=Sum[i]/(i+1);
	printf("%.4LF\n",Ans);return 0;
}

Complex operator + (Complex A,Complex B){
	return ((Complex){A.x+B.x,A.y+B.y});
}

Complex operator - (Complex A,Complex B){
	return ((Complex){A.x-B.x,A.y-B.y});
}

Complex operator * (Complex A,Complex B){
	return ((Complex){A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x});
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs_root(int u,int fa){
	Sz[u]=1;Mx[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa)){
			dfs_root(V[i],u);Sz[u]+=Sz[V[i]];
			Mx[u]=max(Mx[u],Sz[V[i]]);
		}
	Mx[u]=max(Mx[u],nowsize-Sz[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

void Solve(int u){
	vis[u]=1;mxd=0;
	dfs_get(u,u,0);
	Mul(mxd,1);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			mxd=0;dfs_get(V[i],u,1);Mul(mxd,-1);
		}
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			if (Sz[V[i]]>Sz[u]) nowsize=Sz[V[i]]-Sz[u];
			else nowsize=Sz[V[i]];
			root=0;dfs_root(V[i],u);Solve(root);
		}
	return;
}

void dfs_get(int u,int fa,int d){
	F[d].x+=1.0;mxd=max(mxd,d);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa)) dfs_get(V[i],u,d+1);
	return;
}

void Mul(int n,int opt){
	int N=1,L=0;while(N<=n+n) N<<=1,++L;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	FFT(F,N,1);
	for (int i=0;i<N;i++) F[i]=F[i]*F[i];
	FFT(F,N,-1);
	for (int i=0;i<N;i++) Sum[i]+=(ll)(F[i].x)*opt;
	for (int i=0;i<N;i++) F[i]=((Complex){0,0});
	return;
}

void FFT(Complex *P,int N,int opt){
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		Complex dw=((Complex){cos(Pi/i),opt*sin(Pi/i)});
		for (int j=0;j<N;j+=(i<<1)){
			Complex w=((Complex){1,0});
			for (int k=0;k<i;k++){
				Complex X=P[j+k],Y=w*P[j+k+i];
				P[j+k]=X+Y;P[j+k+i]=X-Y;w=w*dw;
			}
		}
	}
	if (opt==-1) for (int i=0;i<N;i++) P[i].x=(ll)(P[i].x/N+0.5);
	return;
}
