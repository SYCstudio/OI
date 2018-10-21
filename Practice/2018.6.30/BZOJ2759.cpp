#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40100;
const int Mod=10007;
const int inf=2147483647;

class SplayData
{
public:
	int ch[2],fa,pfa;
	int k,b;
	int kk,bb;
};

int n;
int P[maxN];
SplayData S[maxN];
bool vis[maxN],ink[maxN];

void dfs(int u);
bool Isroot(int x);
void Update(int x);
void Rotate(int x);
void Access(int x);
int Findroot(int x);
void Cut(int x,int y);
void Link(int x,int y);
int Calc(int a,int b);
void Exgcd(int a,int b,int &x,int &y);
int Query(int x);
void Modify(int x,int np,int k,int b);
void Outp();

int main()
{
	//ios::sync_with_stdio(false);
	S[0].k=S[0].kk=1;
	//cin>>n;
    scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		//cin>>S[i].k>>S[i].fa>>S[i].b;
		scanf("%d%d%d",&S[i].k,&S[i].fa,&S[i].b);
		P[i]=S[i].fa;
	}

	for (int i=1;i<=n;i++) if (vis[i]==0) dfs(i);

	//Outp();
	
	int QQQ;//cin>>QQQ;
	scanf("%d",&QQQ);
	while (QQQ--)
	{
		char opt;//cin>>opt;
		scanf(" %c",&opt);
		if (opt=='A')
		{
			int u;//cin>>u;
			scanf("%d",&u);
			//cout<<Query(u)<<endl;
			printf("%d\n",Query(u));
		}
		if (opt=='C')
		{
			int u,k,p,b;//cin>>u>>k>>p>>b;
			scanf("%d%d%d%d",&u,&k,&p,&b);
			Modify(u,p,k,b);
		}
		//Outp();
	}
	return 0;
}

void dfs(int u)
{
	vis[u]=ink[u]=1;
	if (ink[S[u].fa]){
		S[u].pfa=S[u].fa;S[u].fa=0;
	}
	else if (vis[S[u].fa]==0) dfs(S[u].fa);
	ink[u]=0;return;
}

bool Isroot(int x){
	if ( (S[S[x].fa].ch[0]==x) || ((S[S[x].fa].ch[1]==x)) ) return 0;
	return 1;
}

void Update(int x){
	int ls=S[x].ch[0],rs=S[x].ch[1];
	S[x].kk=1ll*S[ls].kk*S[x].k%Mod*S[rs].kk%Mod;
	S[x].bb=S[rs].bb+1ll*S[x].b*S[rs].kk%Mod+1ll*S[ls].bb*S[x].k%Mod*S[rs].kk%Mod;S[x].bb%=Mod;
	return;
}

void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;S[y].fa=x;
	Update(y);//Update(x);
	return;
}

void Splay(int x)
{
	while (Isroot(x)==0)
	{
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
		Rotate(x);
	}
	Update(x);return;
}

void Access(int x)
{
	int lastx=0;
	while (x)
	{
		Splay(x);S[x].ch[1]=lastx;Update(x);
		lastx=x;x=S[x].fa;
	}
	return;
}

int Findroot(int x)
{
	Access(x);Splay(x);
	while (S[x].ch[0]) x=S[x].ch[0];
	return x;
}

void Cut(int x,int y)
{
	//cout<<"Cut:"<<x<<" "<<y<<endl;
	if (S[x].pfa==y) S[x].pfa=0;
	else
	{
		Access(x);
		if (S[x].ch[0]) S[S[x].ch[0]].fa=0;
		S[x].ch[0]=0;Update(x);
	}
	return;
}

void Link(int x,int y)
{
	//cout<<"Link:"<<x<<" "<<y<<endl;
	if (y==0) return;
	if (Findroot(x)==Findroot(y)) S[x].pfa=y;
	else{
		S[x].pfa=0;Access(x);Splay(x);S[x].fa=y;
	}
	return;
}

int Calc(int a,int b)
{
	//cout<<"Calc:"<<a<<" "<<b<<endl;
	if (a==0)
	{
		if (b==0) return -2;
		return -1;
	}
	if (a<0) a=-a,b=-b;
	if (b<0) b=(b%Mod+Mod)%Mod;
	int x=0,y=0;
	//cout<<"Exgcd:"<<a<<" "<<Mod<<" "<<x<<" "<<y<<endl;
	Exgcd(a,Mod,x,y);
	x=(x%Mod+Mod)%Mod;
	//cout<<"x:"<<x<<" y:"<<y<<endl;
	return (1ll*x*b%Mod+Mod)%Mod;
}

void Exgcd(int a,int b,int &x,int &y)
{
	if (b==0){
		x=1;y=0;return;
	}
	Exgcd(b,a%b,x,y);
	int t=x;
	x=y;y=t-1ll*a/b*y;return;
}

int Query(int x)
{
	//cout<<"Query:"<<x<<endl;
	int rt=Findroot(x),pfa=S[rt].pfa;
	//cout<<"rt:"<<rt<<" "<<pfa<<endl;
	Access(pfa);Splay(pfa);//Outp();
	//cout<<"pfa:"<<pfa<<" kk:"<<S[pfa].kk-1<<" bb:"<<S[pfa].bb<<endl;
	int ret=Calc(S[pfa].kk-1,-S[pfa].bb);
	//cout<<"ret:"<<ret<<endl;
	if (ret<0) return ret;
	if (x==pfa) return ret;
	ret=(1ll*ret*S[rt].k%Mod+S[rt].b%Mod)%Mod;
	//cout<<"ret:"<<ret<<endl;

	Access(x);Splay(rt);
	int c=S[rt].ch[1];
	return (int)(1ll*S[c].kk*ret%Mod+S[c].bb)%Mod;
}

void Modify(int x,int np,int k,int b)
{
	//cout<<"Modify:"<<x<<" "<<P[x]<<" "<<np<<endl;
	Access(x);Splay(x);
	S[x].k=k;S[x].b=b;Update(x);
	int rt=Findroot(x);
	Cut(x,P[x]);Link(rt,S[rt].pfa);Link(x,np);
	P[x]=np;
	return;
}

void Outp()
{
	printf("id fa ls rs k b   kk   bb pfa\n");
	for (int i=1;i<=n;i++) printf("%2d%3d%3d%3d%2d%2d%5d%5d%4d\n",i,S[i].fa,S[i].ch[0],S[i].ch[1],S[i].k,S[i].b,S[i].kk,S[i].bb,S[i].pfa);
	return;
}
/*
5
2 2 1
2 3 2
2 4 3
2 5 4
2 3 5
1
A 1
*/
