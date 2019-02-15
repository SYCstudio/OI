#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

#define ld long double

const ld eps=1e-10;
const int maxN=1<<20;

int n;
ld F[maxN];
int Cnt[maxN];

int main(){
	scanf("%d",&n);int N=1<<n;
	for (int i=0;i<N;i++) scanf("%LF",&F[i]);
	for (int i=1;i<N;i<<=1)
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0;k<i;k++)
				F[j+k+i]+=F[j+k];
	//for (int i=0;i<N;i++) cout<<F[i]<<" ";cout<<endl;
	for (int i=1;i<N;i++) Cnt[i]=Cnt[i>>1]+(i&1);
	ld Ans=0;
	for (int i=1;i<N;i++){
		if (fabs(1-F[(N-1)^i])<eps){
			printf("INF\n");return 0;
		}
		Ans=Ans+((Cnt[i]&1)?1.0:-1.0)/(1.0-F[(N-1)^i]);
	}
	printf("%.10LF\n",Ans);return 0;
}
