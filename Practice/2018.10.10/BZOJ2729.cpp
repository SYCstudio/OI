#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int Num=10000000;
const int inf=2147483647;

class Bigint
{
public:
	ll num[maxN],high;
	Bigint(){
		high=1;mem(num,0);
	}
	void MainTain(){
		for (int i=1;i<high;i++) num[i+1]+=num[i]/Num,num[i]%=Num;
		while (num[high]>=Num) num[high+1]=num[high]/Num,num[high]%=Num,++high;
		while ((high>1)&&(num[high]==0))--high;
		return;
	}
	Bigint operator = (int x){
		mem(num,0);num[high=1]=x;return *this;
	}
};

int n,m;
Bigint A,B;

void Print(Bigint N);
Bigint operator * (Bigint A,int x);
Bigint operator + (Bigint A,Bigint B);

int main(){
	scanf("%d%d",&n,&m);
	A=1;
	for (int i=1;i<=n;i++) A=A*i;
	for (int i=n+1;i>=(n+1)-(2)+1;i--) A=A*i;
	for (int i=n+3;i>=(n+3)-(m)+1;i--) A=A*i;
	B=2*m;
	for (int i=1;i<=n+1;i++) B=B*i;
	for (int i=n+2;i>=(n+2)-(m-1)+1;i--) B=B*i;
	A=A+B;
	Print(A);
}

void Print(Bigint N){
	printf("%lld",N.num[N.high]);
	for (int i=N.high-1;i>=1;i--) printf("%07lld",N.num[i]);
	printf("\n");return;
}

Bigint operator * (Bigint A,int x){
	for (int i=1;i<=A.high;i++) A.num[i]*=x;
	A.MainTain();return A;
}
Bigint operator + (Bigint A,Bigint B){
	A.high=max(A.high,B.high);
	for (int i=1;i<=A.high;i++) A.num[i]+=B.num[i];
	A.MainTain();return A;
}
