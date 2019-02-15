#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=25;
const int mxT=1000;
const int inf=2147483647;

int n,Ans=inf;
int A[maxN],B[maxN],O[maxN];
int Q1[maxN],Q2[maxN];

void dfs(int now);
void Solve();
int Calc(int n1,int n2);
bool cmp1(int a,int b);
bool cmp2(int a,int b);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&O[i],&A[i],&B[i]);
	dfs(1);
	printf("%d\n",Ans);return 0;
}

void dfs(int now){
	if (now==n+1){
		Solve();return;
	}
	if (O[now]!=3) dfs(now+1);
	else{
		O[now]=1;dfs(now+1);
		O[now]=2;dfs(now+1);
		O[now]=3;
	}
	return;
}

void Solve(){
	int n1=0,n2=0;
	for (int i=1;i<=n;i++)
		if (O[i]==1) Q1[++n1]=i;
		else Q2[++n2]=i;
	sort(&Q1[1],&Q1[n1+1],cmp1);sort(&Q2[1],&Q2[n2+1],cmp2);
	int ret=Calc(n1,n2);
	int TTT=mxT;
	while (TTT--){
		int p1=0,p2=0,q1=0,q2=0;
		if (n1){
			p1=rand()%n1+1;p2=rand()%n1+1;
			swap(Q1[p1],Q1[p2]);
		}
		if (n2){
			q1=rand()%n2+1;q2=rand()%n2+1;
			swap(Q2[q1],Q2[q2]);
		}
		int tmp=Calc(n1,n2);
		if (tmp<ret) ret=tmp;
		else swap(Q1[p1],Q1[p2]),swap(Q2[q1],Q2[q2]);
	}
	Ans=min(Ans,ret);return;
}

int Calc(int n1,int n2){
	int suma=0,sumb=0,rt=0;
	for (int i=1;i<=n1;i++) suma+=A[Q1[i]];
	for (int i=1;i<=n2;i++){
		sumb+=B[Q2[i]];
		if (sumb<=suma) suma+=A[Q2[i]];
		else suma=sumb+A[Q2[i]];
	}
	rt=suma;suma=sumb=0;
	for (int i=1;i<=n2;i++) sumb+=B[Q2[i]];
	for (int i=1;i<=n1;i++){
		suma+=A[Q1[i]];
		if (suma<=sumb) sumb+=B[Q1[i]];
		else sumb=suma+B[Q1[i]];
	}
	return max(rt,sumb);
}

bool cmp1(int a,int b){
	if (B[a]!=B[b]) return B[a]>B[b];
	else return A[a]<A[b];
}

bool cmp2(int a,int b){
	if (A[a]!=A[b]) return A[a]>A[b];
	else return B[a]<B[b];
}
