#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int maxAlpha=26*2;
const int P=100000000;
const int inf=2147483647;

class Auto
{
public:
	int last[maxAlpha],fa[maxN];
	int nodecnt,trans[maxN][maxAlpha];
	Auto(){
		nodecnt=1;for (int i=0;i<maxAlpha;i++) last[i]=1;return;
	}
	void Insert(int c){
		//cout<<"Insert:"<<c<<endl;
		fa[++nodecnt]=last[c];
		for (int i=0;i<maxAlpha;i++)
			for (int j=last[i];(j!=0)&&(trans[j][c]==0);j=fa[j])
				trans[j][c]=nodecnt;
		last[c]=nodecnt;return;
	}
};

class BigNum
{
public:
	int mx;
	int *Num;
	BigNum Init(){
		Num = new int[20];
	}
	BigNum& operator = (const BigNum A){
		mx=A.mx;
		for (int i=0;i<=mx;i++) Num[i]=A.Num[i];
		return *this;
	}
	void Add(BigNum A){
		int last=0;
		mx=max(mx,A.mx);
		for (int i=0;i<=mx;i++){
			Num[i]=Num[i]+A.Num[i]+last;
			last=Num[i]/P;Num[i]%=P;
		}
		if (last) Num[++mx]=last;
		return;
	}
	void Outp(){
		printf("%d",Num[mx]);
		for (int i=mx-1;i>=0;i--) printf("%08d",Num[i]);
		return;
	}
};

int n,m;
Auto A,B;
int I1[maxN],I2[maxAlpha];
char Input[maxN];
ll Ans=0;
BigNum F[maxN][maxN];
bool vis[maxN][maxN];
char St[maxN];

void Work1();
void Work2();
void dfs1(int u,int v,int depth);
void dfs2(int u,int v);

int main()
{
	for (int i=0;i<26;i++) I1['A'+i]=i,I2[i]='A'+i;
	for (int i=0;i<26;i++) I1['a'+i]=i+26,I2[i+26]='a'+i;
	scanf("%d%d",&n,&m);
	scanf("%s",Input+1);
	for (int i=1;i<=n;i++) A.Insert(I1[Input[i]]);
	scanf("%s",Input+1);
	for (int i=1;i<=m;i++) B.Insert(I1[Input[i]]);

	int T;scanf("%d",&T);
	if (T==1) Work1();
	else Work2();

	return 0;
}

void Work1()
{
	Ans=0;
	dfs1(1,1,0);
	printf("%lld\n",Ans);
	return;
}

void Work2(){
	dfs2(1,1);
	F[1][1].Outp();
	return;
}

void dfs1(int u,int v,int depth){
	Ans++;
	for (int i=1;i<=depth;i++) putchar(St[i]);putchar('\n');
	for (int i=0;i<maxAlpha;i++)
		if ((A.trans[u][i])&&(B.trans[v][i])){
			St[depth+1]=I2[i];
			dfs1(A.trans[u][i],B.trans[v][i],depth+1);
		}
	return;
}
	
void dfs2(int u,int v){
	if (vis[u][v]==1) return;
	vis[u][v]=1;
	F[u][v].Init();
	F[u][v].mx=0;F[u][v].Num[0]=1;
	for (int i=0;i<maxAlpha;i++)
		if ((A.trans[u][i])&&(B.trans[v][i])){
			dfs2(A.trans[u][i],B.trans[v][i]);
			F[u][v].Add(F[A.trans[u][i]][B.trans[v][i]]);
		}
	return;
}
