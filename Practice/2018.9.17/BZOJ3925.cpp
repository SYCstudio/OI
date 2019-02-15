#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=11;
const int maxM=55;
const int inf=2147483647;

int n,m;
ll E[maxN],C[maxM][maxM],D[1<<maxN],F[1<<maxN][maxM],G[1<<maxN][maxM],Bit[1<<maxN];

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);u--;v--;
		E[u]|=(1<<v);E[v]|=(1<<u);
	}

	for (int S=1;S<(1<<maxN);S++) Bit[S]=Bit[S>>1]+(S&1);
	for (int i=0;i<=m;i++)
		for (int j=C[i][0]=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];

	for (int S=0;S<(1<<n);S++){
		for (int i=0;i<n;i++)
			if (S&(1<<i))
				D[S]+=Bit[E[i]&S];
		D[S]>>=1;
		//cout<<S<<" "<<D[S]<<endl;
	}

	for (int S=0;S<(1<<n);S++)
		if (Bit[S]==1) G[S][0]=1;
		else{
			int SS=S&(-S);
			for (int T=(S-1)&S;T;T=(T-1)&S)
				if (T&SS){
					for (int i=0;i<=D[T];i++)
						for (int j=0;j<=D[S^T];j++)
							F[S][i+j]+=G[T][i]*C[D[S^T]][j];
				}
			for (int i=0;i<=D[S];i++) G[S][i]=C[D[S]][i]-F[S][i];
		}
	ld Ans=0;
	for (int i=0;i<=m;i++) Ans=Ans+1.0*(ld)F[(1<<n)-1][i]/(ld)C[m][i];
	Ans/=(ld)(m+1);
	printf("%.6LF\n",Ans);return 0;
}
