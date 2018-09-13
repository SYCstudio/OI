#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Bigint
{
public:
	int num[500],high;
	Bigint(){
		high=0;mem(num,0);
	}
	
	Bigint & operator = (Bigint A){
		high=A.high;
		for (int i=0;i<=high;i++) num[i]=A.num[i];
		return *this;
	}

	Bigint & operator = (int A){
		high=0;num[0]=A;
		while (num[high]>=1000) high++,num[high]=num[high-1]/1000,num[high-1]%=1000;
		return *this;
	}
};

const int maxN=220;
const int inf=2147483647;

int n,K;
int X[maxN],Y[maxN];
Bigint F[maxN][maxN];

Bigint operator + (const Bigint A,const Bigint B);
Bigint operator * (const Bigint A,const int B);
ostream & operator << (ostream &os,Bigint A);

int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&X[i]);
	for (int i=1;i<=n;i++) scanf("%d",&Y[i]);
	sort(&X[1],&X[n+1]);sort(&Y[1],&Y[n+1]);

	//for (int i=1;i<=n;i++) cout<<X[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Y[i]<<" ";cout<<endl;
	
	F[0][0]=1;
	for (int i=1;i<=n;i++)
		if (X[i]<Y[i]){
			int p=0;
			for (int j=i;j>=1;j--) if (Y[j]>X[i]) p++;
			//cout<<i<<":"<<p<<endl;
			for (int j=1;j<=i;j++){
				if (j>=1) F[i][j]=F[i][j]+F[i-1][j-1]*p;
				if (j>=1) F[i][j]=F[i][j]+F[i-1][j-1]*(i-j);
				if (j>=p) F[i][j]=F[i][j]+F[i-1][j]*(j-(p-1));
			}
		}
		else{
			int p=0;
			for (int j=i;j>=1;j--) if (X[j]>=Y[i]) p++;
			for (int j=0;j<=i;j++){
				F[i][j]=F[i][j]+F[i-1][j]*p;
				F[i][j]=F[i][j]+F[i-1][j]*j;
				if ((j>=1)&&(i-(j-1)-p>=0)) F[i][j]=F[i][j]+F[i-1][j-1]*(i-(j-1)-p);
			}
		}
	
	Bigint Ans;
	for (int i=0;i<=K;i++) Ans=Ans+F[n][i];

	/*
	for (int i=1;i<=n;i++){
		Bigint Sum;
		for (int j=0;j<=i;j++) cout<<F[i][j]<<" ",Sum=Sum+F[i][j];
		cout<<" Sum:"<<Sum<<endl;
	}
	//*/

	cout<<Ans<<endl;

	return 0;
}

Bigint operator + (const Bigint A,const Bigint B){
	Bigint Ret;
	Ret.high=max(A.high,B.high);
	for (int i=0;i<=Ret.high;i++) Ret.num[i]=A.num[i]+B.num[i];
	for (int i=0;i<Ret.high;i++) Ret.num[i+1]+=Ret.num[i]/1000,Ret.num[i]%=1000;
	while (Ret.num[Ret.high]>=1000) Ret.high++,Ret.num[Ret.high]+=Ret.num[Ret.high-1]/1000,Ret.num[Ret.high-1]%=1000;
	return Ret;
}

Bigint operator * (const Bigint A,const int B){
	Bigint Ret;
	Ret.high=A.high;
	for (int i=0;i<=Ret.high;i++) Ret.num[i]=A.num[i]*B;
	for (int i=0;i<Ret.high;i++) Ret.num[i+1]+=Ret.num[i]/1000,Ret.num[i]%=1000;
	while (Ret.num[Ret.high]>=1000) Ret.high++,Ret.num[Ret.high]=Ret.num[Ret.high-1]/1000,Ret.num[Ret.high-1]%=1000;
	return Ret;
}

ostream & operator << (ostream & os,Bigint A){
	os<<A.num[A.high];
	for (int i=A.high-1;i>=0;i--){
		if (A.num[i]<=9) os<<"00";
		else if (A.num[i]<=99) os<<"0";
		os<<A.num[i];
	}
	return os;
}
