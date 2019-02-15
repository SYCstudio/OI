#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1<<20;
const ld eps=1e-8;

int n;
ld F[maxN];
int Cnt[maxN];

int main(){
	while (scanf("%d",&n)!=EOF){
		int N=1<<n;mem(F,0);mem(Cnt,0);
		for (int i=0;i<n;i++) scanf("%lf",&F[1<<i]);
		for (int i=1;i<N;i<<=1)
			for (int j=0;j<N;j+=(i<<1))
				for (int k=0;k<i;k++)
					F[j+k+i]+=F[j+k];
		for (int i=1;i<N;i++) Cnt[i]=Cnt[i>>1]+(i&1);
		ld Ans=0;
		for (int i=1;i<N;i++)
			if (F[i]>eps) Ans=Ans+((Cnt[i]&1)?1.0:-1.0)/F[i];
		printf("%.4lf\n",Ans);
	}
	return 0;
}
