#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n,m,K;
ull Seq[maxN],BS[65],P[65];

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%llu",&Seq[i]);
	ull mx=0;for (int i=1;i<=n;i++) mx=max(mx,Seq[i]);
	int mxd=0;while (mx) ++mxd,mx>>=1;
	if (K==1){
		ull ans=0;for (int i=1;i<=n;i++) ans|=Seq[i];
		printf("%llu",ans>>1);
		if (ans&1) printf(".5");
		printf("\n");
	}
	else if (K==2){
		ull Ans1=0,Ans2=0;
		for (int i=0;i<=mxd;i++)
			for (int j=0;j<=mxd;j++){
				bool f1=0,f2=0,f3=0;
				for (int k=1;k<=n;k++){
					f1|=((Seq[k]>>i)&1);
					f2|=((Seq[k]>>j)&1);
					f3|=(((Seq[k]>>i)&1)!=((Seq[k]>>j)&1));
				}
				if ((f1==0)||(f2==0)) continue;
				if (i+j-f3-1<0) ++Ans2;
				else Ans1+=(1ll<<(i+j-f3-1));
			}
		Ans1+=(Ans2>>1);
		printf("%llu",Ans1);
		if (Ans2&1) printf(".5");
	}
	else{
		for (int i=1;i<=n;i++){
			ull key=Seq[i];
			for (int j=mxd;j>=0;j--)
				if ((key>>j)&1){
					if (BS[j]==0){
						BS[j]=key;break;
					}
					key^=BS[j];
				}
		}
		for (int i=0;i<=mxd;i++) if (BS[i]) P[m++]=BS[i];
		int N=1<<m;ull ans1=0,ans2=0;
		for (int S=1;S<N;S++){
			ull sum=0;for (int i=0;i<m;i++) if ((S>>i)&1) sum^=P[i];
			ull ret1=0,ret2=1;
			for (int i=1;i<=K;i++){
				ret1*=sum;ret2*=sum;
				ret1+=ret2/N;ret2%=N;
			}
			ans1+=ret1;ans2+=ret2;
			ans1+=ans2/N;ans2%=N;
		}
		printf("%llu",ans1);
		if (ans2) printf(".5\n");
	}
	return 0;
}
