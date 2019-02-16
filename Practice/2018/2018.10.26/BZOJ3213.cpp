#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=100;
const int maxL=1010;
const int inf=2147483647;

ll Bp[maxN];

class Bigint
{
public:
	int sz;
	ll num[maxN];
	void MainTain(){
		for (int i=1;i<sz;i++) num[i+1]+=num[i]/maxM,num[i]%=maxM;
		while (num[sz]>=maxM) num[sz+1]=num[sz]/maxM,num[sz]%=maxM,++sz;
		return;
	}
	Bigint(){
		sz=0;return;
	}
	Bigint(int A){
		num[sz=1]=A;MainTain();return;
	}
	bool zero(){
		return (sz==1)&&(num[1]==0);
	}
	Bigint operator = (int A){
		num[sz=1]=A;MainTain();return *this;
	}
	Bigint operator = (Bigint A){
		sz=A.sz;for (int i=1;i<=sz;i++) num[i]=A.num[i];
		return *this;
	}
	void outp(){
		printf("%lld",num[sz]);
		for (int i=sz-1;i>=1;i--) printf("%02lld",num[i]);
		return;
	}
};

Bigint operator + (Bigint A,int B);
Bigint operator - (Bigint A,int B);
Bigint operator * (Bigint A,int B);
Bigint operator / (Bigint A,int B);
int operator % (Bigint A,int B);
Bigint operator + (Bigint A,Bigint B);
Bigint operator - (Bigint A,Bigint B);
Bigint operator * (Bigint A,Bigint B);

class Fraction
{
public:
	Bigint A,B;
	Fraction(){}
	Fraction(int a,int b){
		A=a;B=b;Reduction();return;
	}
	Fraction(Bigint a,Bigint b){
		A=a;B=b;Reduction();return;
	}
	void Reduction(){
		if (A.zero()){
			B=1;return;
		}
		for (int i=2;i<=100;i++)
			while ((A%i==0)&&(B%i==0)) A=A/i,B=B/i;
		return;
	}
	bool zero(){
		return A.zero();
	}
	Fraction Assign(int a,int b){
		A=a;B=b;Reduction();return *this;
	}
	void outp(){
		A.outp();printf("/");B.outp();
		return;
	}
};

char Input[maxL];
int Next[maxL],Fail[maxL];
Fraction P[2],K[maxL],B[maxL];

Fraction operator + (Fraction F,int a);
Fraction operator - (Fraction F,int a);
Fraction operator * (Fraction F,int a);
Fraction operator / (Fraction F,int a);
Fraction operator + (Fraction F,Bigint a);
Fraction operator - (Fraction F,Bigint a);
Fraction operator * (Fraction F,Bigint a);
Fraction operator / (Fraction F,Bigint a);
Fraction operator + (Fraction F,Fraction a);
Fraction operator - (Fraction F,Fraction a);
Fraction operator * (Fraction F,Fraction a);
Fraction operator / (Fraction F,Fraction a);

int main(){
	int a,b;scanf("%d%d",&a,&b);
	P[0].Assign(a,b);P[1].Assign(b-a,b);
	scanf("%s",Input+1);int len=strlen(Input+1);
	
	Next[0]=0;Next[1]=0;
	for (int i=2;i<=len;i++){
		int j=Next[i-1];
		while ((j)&&(Input[j+1]!=Input[i])) j=Next[j];
		if (Input[j+1]==Input[i]) ++j;
		Next[i]=j;
	}
	Fail[0]=0;
	for (int i=1;i<len;i++){
		int j=Next[i];
		while ((j)&&(Input[j+1]==Input[i+1])) j=Next[j];
		if (Input[j+1]!=Input[i+1]) Fail[i]=j+1;
	}
	
	//for (int i=1;i<=len;i++) cout<<Next[i]<<" ";cout<<endl;
	//for (int i=1;i<=len;i++) cout<<Fail[i]<<" ";cout<<endl;
	//F[0].Assign(0,1);
	//cout<<"P:";P[0].outp();printf(" ");P[1].outp();printf("\n");
	K[0].Assign(1,1);B[0].Assign(0,1);
	for (int i=1;i<=len;i++){
		int b=(Input[i]!='H');
		K[i]=(K[i-1]-P[b^1]*K[Fail[i-1]])/P[b];
		B[i]=(B[i-1]+1-P[b^1]*B[Fail[i-1]])/P[b];
	}
	K[len]=B[len]/K[len];
	K[len].A.outp();printf("/");K[len].B.outp();
	return 0;
}

Bigint operator + (Bigint A,int B){
	A.num[1]+=B;A.MainTain();return A;
}
Bigint operator - (Bigint A,int B){
	if (A.num[1]<B){
		int b=2;while (A.num[b]==0) ++b;
		while (b!=1) A.num[b--]=maxM-1;
		A.num[1]+=maxM;
	}
	A.num[1]-=B;return A;
}
Bigint operator * (Bigint A,int B){
	for (int i=1;i<=A.sz;i++) A.num[i]*=B;
	A.MainTain();return A;
}
Bigint operator / (Bigint A,int B){
	for (int i=A.sz,sum=0;i>=1;i--){
		sum=sum*maxM+A.num[i];A.num[i]=0;
		A.num[i]=sum/B;sum%=B;
	}
	while ((A.sz>1)&&(A.num[A.sz]==0)) --A.sz;
	return A;
}
int operator % (Bigint A,int B){
	int ret=0;
	for (int i=A.sz;i>=1;i--){
		ret=ret*maxM+A.num[i];
		ret%=B;
	}
	return ret;
};
Bigint operator + (Bigint A,Bigint B){
	A.sz=max(A.sz,B.sz);
	for (int i=1;i<=A.sz;i++) A.num[i]+=B.num[i];
	A.MainTain();return A;
}
Bigint operator - (Bigint A,Bigint B){
	//cout<<"Minis:";A.outp();cout<<"-";B.outp();cout<<endl;
	for (int i=1;i<=A.sz;i++){
		if (A.num[i]<B.num[i]){
			--A.num[i+1];A.num[i]+=maxM;
		}
		A.num[i]-=B.num[i];
	}
	while ((A.sz>1)&&(A.num[A.sz]==0)) --A.sz;
	//A.outp();cout<<endl;
	return A;
}
Bigint operator * (Bigint A,Bigint B){
	for (int i=1;i<=A.sz;i++) Bp[i]=A.num[i];
	for (int i=1;i<=A.sz+B.sz;i++) A.num[i]=0;
	for (int i=1;i<=A.sz;i++)
		for (int j=1;j<=B.sz;j++)
			A.num[i+j-1]+=Bp[i]*B.num[j];
	A.sz=A.sz+B.sz-1;A.MainTain();return A;
}

Fraction operator + (Fraction F,int a){
	F.A=F.A+F.B*a;F.Reduction();return F;
}
Fraction operator - (Fraction F,int a){
	F.A=F.A-F.B*a;F.Reduction();return F;
}
Fraction operator * (Fraction F,int a){
	F.A=F.A*a;F.Reduction();return F;
}
Fraction operator / (Fraction F,int a){
	F.B=F.B*a;F.Reduction();return F;
}
Fraction operator + (Fraction F,Bigint a){
	F.A=F.A+F.B*a;F.Reduction();return F;
}
Fraction operator - (Fraction F,Bigint a){
	F.A=F.A-F.B*a;F.Reduction();return F;
}
Fraction operator * (Fraction F,Bigint a){
	F.A=F.A*a;F.Reduction();return F;
}
Fraction operator / (Fraction F,Bigint a){
	F.B=F.B*a;F.Reduction();return F;
}
Fraction operator + (Fraction F,Fraction a){
	a.Reduction();if (a.zero()) return F;
	F.A=F.A*a.B+F.B*a.A;F.B=F.B*a.B;F.Reduction();return F;
}
Fraction operator - (Fraction F,Fraction a){
	a.Reduction();if (a.zero()) return F;
	F.A=F.A*a.B-F.B*a.A;F.B=F.B*a.B;F.Reduction();return F;
}
Fraction operator * (Fraction F,Fraction a){
	//cout<<"Mul:"<<endl;
	//outp();printf(" * ");a.outp();printf(" ");
	F.A=F.A*a.A;F.B=F.B*a.B;//outp();printf("\n");
	F.Reduction();return F;
}
Fraction operator / (Fraction F,Fraction a){
	F.A=F.A*a.B;F.B=F.B*a.A;F.Reduction();return F;
}
