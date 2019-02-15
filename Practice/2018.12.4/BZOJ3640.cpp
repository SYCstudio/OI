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

const int maxN=160;
const int maxM=5010<<1;
const int maxHP=10100;
const ld eps=1e-10;
const int inf=2147483647;

int n,m,HP;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dft[maxN],Dg[maxN];
ld M1[maxN][maxN],M2[maxN][maxN],Ans[maxN][maxHP],C[maxN];

void Add_Edge(int u,int v);

int main(){
	mem(Head,-1);scanf("%d%d%d",&n,&m,&HP);
	for (int i=1;i<=n;i++) scanf("%d",&Dft[i]);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);if (u!=v) Add_Edge(v,u);
	}
	for (int i=1;i<=n;i++){
		M1[i][i]=1.0;M2[i][i]=1.0;
		if (Dft[i]==0)
			for (int j=Head[i];j!=-1;j=Next[j])
				if (V[j]!=n) M1[i][V[j]]-=1.0/Dg[V[j]];
	}
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			printf("%2.2LF ",M1[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			printf("%2.2LF ",M2[i][j]);
		printf("\n");
	}
	printf("\n");
	//*/
	for (int i=1;i<=n;i++){
		int now=i;
		for (int j=i+1;j<=n;j++) if (fabs(M1[j][i])>fabs(M1[now][i])) now=j;
		if (now!=i) swap(M1[i],M1[now]),swap(M2[i],M2[now]);
		ld d=1.0/M1[i][i];
		//cout<<"d:"<<d<<endl;
		for (int j=1;j<=n;j++) M1[i][j]=M1[i][j]*d,M2[i][j]=M2[i][j]*d;
		for (int j=1;j<=n;j++)
			if ((j!=i)&&(fabs(M1[j][i])>eps)){
				d=M1[j][i];
				for (int k=1;k<=n;k++) M1[j][k]=M1[j][k]-d*M1[i][k],M2[j][k]=M2[j][k]-d*M2[i][k];
			}
	}
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			printf("%2.2LF ",M1[i][j]);
		printf("\n");
	}
	printf("\n");
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			printf("%2.2LF ",M2[i][j]);
		printf("\n");
	}
	//*/
	ld ans=0;
	for (int h=HP;h>=1;h--){
		mem(C,0);if (h==HP) C[1]=1;
		for (int i=1;i<=n;i++)
			if ((Dft[i]!=0)&&(Dft[i]+h<=HP))
				for (int j=Head[i];j!=-1;j=Next[j])
					if (V[j]!=n) C[i]+=Ans[V[j]][Dft[i]+h]/Dg[V[j]];
		for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Ans[i][h]+=M2[i][j]*C[j];
		ans+=Ans[n][h];
	}
	printf("%.8LF\n",ans);return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;++Dg[u];
	return;
}
/*
3 3 2
0 1 0
1 2
1 3
2 3
//*/
