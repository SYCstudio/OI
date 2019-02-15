#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "easy"

const int maxN=16;
const int maxM=850;
const int Mod=1000000007;
const int inf=2147483647;

int n,g,l,Q;
int fcnt,Ft[maxN],Mn[maxN],Mx[maxN];
pair<int,int> P[maxM];
int pcnt,F[maxM][1<<maxN],G[maxM][1<<maxN];
int Ans[maxM];

void Push(int key);
void Plus(int &x,int y);

int main(){
	//freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	scanf("%d%d%d%d",&n,&g,&l,&Q);
	if (l%g){
		//Q++;
		while (Q--) printf("0\n");return 0;
	}
	int X=l;
	for (int i=2;i*i<=X;i++)
		if (X%i==0){
			Ft[fcnt++]=i;
			while (X%i==0) X/=i;
		}
	if (X!=1) Ft[fcnt++]=X;
	//cerr<<fcnt<<endl;
	int N=(1<<(fcnt<<1))-1;

	for(int i=0;i<fcnt;i++){
		X=l;while (X%Ft[i]==0) X/=Ft[i],Mx[i]++;
		X=g;while (X%Ft[i]==0) X/=Ft[i],Mn[i]++;
	}

	//for (int i=0;i<fcnt;i++) cout<<Ft[i]<<":"<<Mn[i]<<" "<<Mx[i]<<endl;

	for (int i=1;i*i<=l;i++)
		if (l%i==0){
			Push(i);if (i*i<l) Push(l/i);
		}
	sort(&P[1],&P[pcnt+1]);
	//cerr<<pcnt<<endl;
	//for (int i=1;i<=pcnt;i++) cout<<P[i].first<<" "<<P[i].second<<endl;

	F[0][0]=1;
	for (int i=0;i<pcnt;i++){
		//Plus(F[i+1][P[i+1].second],1);
		for (int j=0;j<=N;j++)
			if (F[i][j]){
				Plus(F[i+1][j|P[i+1].second],F[i][j]);
				Plus(F[i+1][j],F[i][j]);
			}
	}

	/*
	for (int i=1;i<=pcnt;i++){
		for (int j=0;j<=N;j++)
			cout<<F[i][j]<<" ";cout<<endl;
	}
	//*/
	
	//printf("%d\n",F[pcnt][N]);

	G[pcnt+1][0]=1;
	for (int i=pcnt+1;i>1;i--)
		for (int j=0;j<=N;j++)
			if (G[i][j]){
				Plus(G[i-1][j|P[i-1].second],G[i][j]);
				Plus(G[i-1][j],G[i][j]);
			}
	for (int i=1;i<=pcnt+1;i++)
		for (int j=0;j<(fcnt<<1);j++)
			for (int k=0;k<=N;k++)
				if ((k&(1<<j))==0) Plus(G[i][k],G[i][k|(1<<j)]);
	for (int i=1;i<=pcnt;i++)
		for (int j=0;j<=N;j++)
			Plus(Ans[i],1ll*F[i-1][j]*G[i+1][N^(j|P[i].second)]%Mod);
	while (Q--){
		int K;scanf("%d",&K);
		int p=lower_bound(&P[1],&P[pcnt+1],make_pair(K,0))-P;
		if (P[p].first==K) printf("%d\n",Ans[p]);
		else printf("0\n");
	}

	return 0;
}

void Push(int key){
	if ((key>n)||(key%g)) return;
	int s=0;
	for (int i=0;i<fcnt;i++){
		int X=key,d=0;while (X%Ft[i]==0) X/=Ft[i],d++;
		if (d==Mn[i]) s|=(1<<(i<<1));
		if (d==Mx[i]) s|=(1<<((i<<1)+1));
	}
	P[++pcnt]=make_pair(key,s);return;
}

void Plus(int &x,int y){
	x=x+y;if (x>=Mod) x-=Mod;
}
