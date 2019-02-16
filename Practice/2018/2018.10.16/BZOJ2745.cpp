#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int inf=2147483647;

int n,m,P;

int QPow(int x,int cnt);

namespace C1
{
	const int maxM=215;

	int Tri[maxM][maxM];
	int M1[maxM],M2[maxM][maxM],Bp[maxM][maxM];
	
	void Do();
	IL void Mul1();
	IL void Mul2();
}

namespace C2
{
	int A,B,BB;
	
	void Do();
	int Calc(int limit);
}

int main(){
	scanf("%d%d%d",&n,&m,&P);
	if (m<=200) C1::Do();
	else C2::Do();
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%P;
		x=1ll*x*x%P;cnt>>=1;
	}
	return ret;
}

namespace C1
{
	void Do(){
		RG int i,j;
		int A=1ll*m*(m-1)%P,B=((1ll*m*m%P-3ll*m%P)%P+3+P)%P;
		for (i=0;i<=m+1;++i)
			for (j=Tri[i][0]=1;j<=i;++j){
				Tri[i][j]=(Tri[i-1][j]+Tri[i-1][j-1]);
				if (Tri[i][j]>=P) Tri[i][j]-=P;
			}
		for (i=1;i<=m+1;++i) M1[i]=1;
		M2[0][0]=M2[1][0]=1;
		for (i=1;i<=m+1;++i)
			for (j=i;j<=m+1;++j) M2[j][i]=1ll*B*Tri[m-i+1][j-i]%P;
		RG int nn=n-1;
		while (nn){
			if (nn&1) Mul1();
			Mul2();nn>>=1;
		}
		int Ans=(M1[0]+M1[1])%P;
		Ans=1ll*Ans*A%P*QPow(2,m)%P;
		printf("%d\n",Ans);return;
	}

	IL void Mul1(){
		RG int i,j,k;
		for (i=0;i<=m+1;++i) Bp[0][i]=M1[i],M1[i]=0;
		for (k=0;k<=m+1;++k)
			if (Bp[0][k])
				for (j=0;j<=m+1;++j)
					M1[j]=(M1[j]+1ll*Bp[0][k]*M2[k][j]%P)%P;
		return;
	}

	IL void Mul2(){
		RG int i,j,k;
		for (i=0;i<=m+1;++i) for (j=0;j<=m+1;++j) Bp[i][j]=M2[i][j],M2[i][j]=0;
		for (k=0;k<=m+1;++k)
			for (i=0;i<=m+1;++i)
				if (Bp[i][k])
					for (j=0;j<=m+1;++j)
						if (Bp[k][j])
							M2[i][j]=(M2[i][j]+1ll*Bp[i][k]*Bp[k][j]%P)%P;
		return;
	}
}

namespace C2
{
	void Do(){
		A=1ll*m*(m-1)%P;B=((1ll*m*m%P-3ll*m%P+3)%P+P)%P;BB=QPow(B,P);
		int cnt=n/P;
		int B1=Calc(cnt-1),B2=Calc(cnt);
		//cout<<"cnt:"<<cnt<<" B:"<<B<<" BB:"<<BB<<" B1:"<<B1<<" B2:"<<B2<<endl;
		//for (int i=0;i<=10;i++) cout<<i<<":"<<Calc(i)<<endl;
		int Ans=0;
		for (int i=1;(i<=P)&&(i<=n);i++){
			//cout<<i<<" "<<(i<=n%P)<<endl;
			if (i<=n%P) Ans=(Ans+1ll*B2*QPow(i,m)%P*QPow(B,i-1)%P)%P;
			else Ans=(Ans+1ll*B1*QPow(i,m)%P*QPow(B,i-1)%P)%P;
			//cout<<Ans<<endl;
		}
		//cout<<"Ans:"<<Ans<<endl;
		Ans=1ll*Ans*QPow(2,m)%P*A%P;
		printf("%d\n",Ans);return;
	}

	int Calc(int limit){
		if (limit<0) return 0;
		if (limit==0) return 1;
		if ((limit&1)==0) return (Calc(limit-1)+QPow(BB,limit))%P;
		else return 1ll*Calc(limit/2)*(1+QPow(BB,limit/2+1)%P)%P;
	}
}

