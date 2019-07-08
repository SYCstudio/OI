#include<bits/stdc++.h>
using namespace std;

const int maxK=510;
const int Mod=998244353;

class Data
{
public:
	int a,b;
	Data()
	{
		a=b=0;
	}
	Data(int c,int d)
	{
		a=c;
		b=d;
		return;
	}
};

int G,C[maxK][maxK];
Data C1,C2,X1,X2;
Data px1[maxK],px2[maxK],pc1[maxK],pc2[maxK];

int QPow(int x,long long cnt);
int Inv(int x);
Data QPow(Data x,long long cnt);
Data Inv(Data A);
Data operator + (Data A,int B);
Data operator * (Data A,int B);
Data operator + (int A,Data B);
Data operator * (int A,Data B);
Data operator + (Data A,Data B);
Data operator - (Data A,Data B);
Data operator * (Data A,Data B);
int Calc(long long up,int K);
int main()
{
	for (int i=0; i<maxK; i++) for (int j=C[i][0]=1; j<=i; j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
	int Case,M;
	scanf("%d%d",&Case,&M);
	if (M==2) {
		G=5;
		C1=(Data) {
			Inv(2),Inv(10)
		};
		C2=(Data) {
			C1.a,Mod-C1.b
		};
		X1=(Data) {
			Inv(2),Inv(2)
		};
		X2=(Data) {
			X1.a,Mod-X1.b
		};
	} else {
		G=3;
		C1=(Data) {
			Inv(2),Inv(6)
		};
		C2=(Data) {
			C1.a,Mod-C1.b
		};
		X1=(Data) {
			2,1
		};
		X2=(Data) {
			X1.a,Mod-X1.b
		};
	}
	px1[0]=px2[0]=pc1[0]=pc2[0]=(Data) {
		1,0
	};
	for (int i=1; i<maxK; i++) px1[i]=px1[i-1]*X1,px2[i]=px2[i-1]*X2,pc1[i]=pc1[i-1]*C1,pc2[i]=pc2[i-1]*C2;

	while (Case--) {
		long long L,R;
		int K;
		scanf("%lld%lld%d",&L,&R,&K);
		int inv=Inv((R-L+1)%Mod);
		if (M==3) L=(L+1)/2,R=R/2;
		int ans=(Calc(R,K)-Calc(L-1,K)+Mod)%Mod;
		ans=1ll*ans*inv%Mod;
		printf("%d\n",ans);
	}
	return 0;
}
int QPow(int x,long long cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
int Inv(int x)
{
	return QPow(x,Mod-2);
}
Data QPow(Data x,long long cnt)
{
	Data ret(1,0);
	while (cnt) {
		if (cnt&1) ret=ret*x;
		x=x*x;
		cnt>>=1;
	}
	return ret;
}
Data Inv(Data A)
{
	int ic=(1ll*A.a*A.a%Mod-1ll*A.b*A.b%Mod*G%Mod+Mod)%Mod;
	ic=Inv(ic);
	assert(ic>=0);
	return (Data) {
		1ll*A.a*ic%Mod,1ll*(Mod-A.b)*ic%Mod
	};
}
Data operator + (Data A,int B)
{
	return (Data) {
		(A.a+B)%Mod,A.b
	};
}
Data operator * (Data A,int B)
{
	return (Data) {
		1ll*A.a*B%Mod,1ll*A.b*B%Mod
	};
}
Data operator + (int A,Data B)
{
	return B+A;
}
Data operator * (int A,Data B)
{
	return B*A;
}
Data operator + (Data A,Data B)
{
	return (Data) {
		(A.a+B.a)%Mod,(A.b+B.b)%Mod
	};
}
Data operator - (Data A,Data B)
{
	return (Data) {
		(A.a-B.a+Mod)%Mod,(A.b-B.b+Mod)%Mod
	};
}
Data operator * (Data A,Data B)
{
	return (Data) {
		(1ll*A.a*B.a%Mod+1ll*G*A.b%Mod*B.b%Mod)%Mod,(1ll*A.a*B.b%Mod+1ll*A.b*B.a%Mod)%Mod
	};
}
int Calc(long long up,int K)
{
	static Data f[maxK];
	static int poly[maxK];
	for (int i=0; i<=K; i++) f[i]=(Data) {
		0,0
	};
	memset(poly,0,sizeof(poly));
	for (int i=0; i<=K; i++)
		for (int j=0; j<=i; j++) {
			Data mul=px1[j]*px2[i-j];

			if (mul.a==1&&mul.b==0) mul=(Data) {
				up%Mod,0
			};
			else mul=(mul-QPow(mul,up+1))*Inv((Data) {
				1,0
			}-mul);

			f[i]=f[i]+C[i][j]*pc1[j]*pc2[i-j]*mul;
		}
	poly[0]=1;
	for (int i=0; i<K; i++) {
		int mul=(Mod-i)%Mod;
		for (int j=K; j>=1; j--) poly[j]=(1ll*poly[j]*mul%Mod+poly[j-1])%Mod;
		poly[0]=1ll*poly[0]*mul%Mod;
	}
	int fc=1;
	for (int i=1; i<=K; i++) fc=1ll*fc*i%Mod;
	int ifc=Inv(fc);

	/*
	for (int i=0;i<=K;i++){
	Data sum(0,0);
	for (int j=1;j<=up;j++) sum=sum+QPow(C1*QPow(X1,j)+C2*QPow(X2,j),i);
	cout<<"("<<sum.a<<" "<<sum.b<<") ";
	f[i]=sum;
	}cout<<endl;
	for (int i=0;i<=K;i++) cout<<"("<<f[i].a<<" "<<f[i].b<<") ";cout<<endl;
	//*/

	int ret=0;
	for (int i=0; i<=K; i++) ret=(ret+1ll*poly[i]*f[i].a%Mod)%Mod;
	ret=1ll*ret*ifc%Mod;
	return ret;
}
