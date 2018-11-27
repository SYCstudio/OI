#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
int A[maxN][maxN],B[maxN][maxN],C[maxN][maxN],Inv[maxN][maxN];
bool Mp[maxN][maxN];
int Match[maxN],tim,Tim[maxN];

int QPow(int x,int cnt);
bool Hungary(int u);
bool ReHungary(int u,int p);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&A[i][j]);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&B[i][j]);
	for (int i=1;i<=n;i++) Inv[i][i]=1;
	for (int i=1;i<=n;i++){
		int now=i;
		for (int j=i+1;j<=n;j++) if (A[j][i]>A[now][i]) now=j;
		if (now!=i) swap(A[i],A[now]),swap(Inv[i],Inv[now]);
		if (A[i][i]==0){
			printf("NIE\n");return 0;
		}
		int p=QPow(A[i][i],Mod-2);
		for (int j=1;j<=n;j++) A[i][j]=1ll*A[i][j]*p%Mod,Inv[i][j]=1ll*Inv[i][j]*p%Mod;
		for (int j=1;j<=n;j++)
			if ((i!=j)&&(A[j][i])){
				p=A[j][i];
				for (int k=1;k<=n;k++) A[j][k]=(A[j][k]-1ll*A[i][k]*p%Mod+Mod)%Mod,Inv[j][k]=(Inv[j][k]-1ll*Inv[i][k]*p%Mod+Mod)%Mod;
			}
	}

	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) printf("%d ",Inv[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				C[i][j]=(C[i][j]+1ll*B[i][k]*Inv[k][j]%Mod)%Mod;

	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) printf("%d ",C[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (C[i][j]) Mp[j][i]=1;

	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) printf("%d ",Mp[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	
	mem(Match,-1);++tim;
	for (int i=1;i<=n;i++,tim++)
		if (Hungary(i)==0){
			printf("NIE\n");return 0;
		}

	printf("TAK\n");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			Tim[j]=++tim;
			if ((Mp[i][j])&&(Match[j]>=i)&&(ReHungary(Match[j],i))){
				Match[j]=i;printf("%d\n",j);
				for (int k=1;k<=n;k++) Mp[k][j]=0;
				break;
			}
		}
		for (int j=1;j<=n;j++) Mp[i][j]=0;
	}
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

bool Hungary(int u){
	for (int i=1;i<=n;i++)
		if ((Mp[u][i])&&(Tim[i]!=tim)){
			Tim[i]=tim;//cout<<u<<"->"<<i<<endl;
			if ((Match[i]==-1)||(Hungary(Match[i]))){
				Match[i]=u;return 1;
			}
		}
	return 0;
}

bool ReHungary(int u,int p){
	if (u==p) return 1;
	for (int i=1;i<=n;i++)
		if ((Mp[u][i])&&(Tim[i]!=tim)){
			Tim[i]=tim;
			if (ReHungary(Match[i],p)){
				Match[i]=u;return 1;
			}
		}
	return 0;
}
