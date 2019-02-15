#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=310;
const int inf=2147483647;

int n,m,M;
int sum[maxN],num[maxN],C[maxN][maxN];
int F[maxN][maxN];

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		mem(sum,0);mem(num,0);mem(C,0);mem(F,0);
		scanf("%d%d%d",&n,&m,&M);
		for (int i=0;i<=n;i++)
			for (int j=C[i][0]=1;j<=i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%M;
		for (int i=1;i<=m;i++){
			int p,q;scanf("%d%d",&p,&q);num[q]++;
		}
		sum[0]=num[0]=n-m;
		bool flag=1;
		for (int i=1;i<=n;i++){
			sum[i]=sum[i-1]+num[i];
			if (sum[i]<i){
				flag=0;break;
			}
		}
		if (flag==0){
			printf("NO\n");continue;
		}
		F[0][0]=1;
		for (int i=1;i<=n;i++)
			for (int j=i;j<=sum[i];j++)
				for (int k=num[i];k<=j;k++)
					F[i][j]=(F[i][j]+1ll*F[i-1][j-k]*C[sum[i]-j+k-num[i]][k-num[i]]%M)%M;
		printf("YES %d\n",F[n][n]);
	}
	return 0;
}
