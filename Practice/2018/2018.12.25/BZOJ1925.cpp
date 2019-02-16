#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=4300;

int n,P;
int F[2][maxN];

int main(){
	scanf("%d%d",&n,&P);
	F[0][1]=1;int now=0;
	for (int i=1;i<=n;i++){
		now^=1;mem(F[now],0);
		for (int j=1;j<=i;j++) F[now][j]=(F[now][j-1]+F[now^1][i-j+1])%P;
	}
	int sum=0;
	for (int i=1;i<=n;i++) sum=(sum+F[now][i])%P;
	printf("%d\n",(sum+sum)%P);
	return 0;
}
