#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;
class Num
{
public:
	ull a[5];
	Num()
	{
		memset(a,0,sizeof(a));
		return;
	}
};
const int maxN=100000;
const ull M=1ull<<58;

Num P[maxN],W[10];

Num operator + (Num A,Num B);
Num operator - (Num A,Num B);
Num operator * (Num A,ull B);
Num operator * (Num A,Num B);
ull QPow(ull x,ull cnt);
Num QPow(Num x,ull cnt);
void FWT(Num *P,int opt);
int main()
{
	W[0].a[0]=1;
	W[1].a[1]=1;
	for (int i=2; i<10; i++) W[i]=W[i-1]*W[1];
	int n;
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		int x;
		scanf("%d",&x);
		++P[x].a[0];
	}
	FWT(P,1);
	for (int i=0; i<maxN; i++) P[i]=QPow(P[i],n);
	FWT(P,9);
	for (int i=0; i<n; i++) printf("%llu\n",(P[i].a[0]-P[i].a[4])/32%M);
	return 0;
}
Num operator + (Num A,Num B)
{
	for (int i=0; i<=4; i++) A.a[i]+=B.a[i];
	return A;
}
Num operator - (Num A,Num B)
{
	for (int i=0; i<=4; i++) A.a[i]-=B.a[i];
	return A;
}
Num operator * (Num A,ull B)
{
	for (int i=0; i<=4; i++) A.a[i]*=B;
	return A;
}
Num operator * (Num A,Num B)
{
	ull tmp[10];
	memset(tmp,0,sizeof(tmp));
	for (int i=0; i<=4; i++) for (int j=0; j<=4; j++) tmp[i+j]+=A.a[i]*B.a[j];
	for (int i=0; i<=4; i++) A.a[i]=tmp[i]-tmp[i+5];
	return A;
}
ull QPow(ull x,ull cnt)
{
	ull ret=1;
	while (cnt) {
		if (cnt&1) ret=ret*x;
		x=x*x;
		cnt>>=1;
	}
	return ret;
}
Num QPow(Num x,ull cnt)
{
	Num ret;
	ret.a[0]=1;
	while (cnt) {
		if (cnt&1) ret=ret*x;
		x=x*x;
		cnt>>=1;
	}
	return ret;
}
void FWT(Num *P,int opt)
{
	for (int i=1; i<maxN; i=i*10)
		for (int j=0; j<maxN; j+=i*10)
			for (int k=0; k<i; k++) {
				static Num sum[10];
				for (int x=0; x<10; x++) {
					sum[x]=Num();
					for (int y=0; y<10; y++)
						sum[x]=sum[x]+P[j+k+y*i]*W[x*y*opt%10];
				}
				for (int x=0; x<10; x++) P[j+k+x*i]=sum[x];
			}
	if (opt==9) {
		ull inv=QPow(5,(1ull<<63)-5);
		for (int i=0; i<maxN; i++) P[i]=P[i]*inv;
	}
	return;
}
