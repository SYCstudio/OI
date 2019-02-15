#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxFac=5000;
const int M1=998244353;
const int M2=998244853;
const int inf=2147483647;

class Number
{
public:
	ld key;
	int a,b;
};

int n;
int C[maxN];
int anscnt,f1,f2,F1[maxFac],F2[maxFac];
Number Ans[maxN*10];

void Fact(int key,int *F,int &f);
bool check(int a,int b,int f);
int QPow(int x,int cnt,int Mod);
bool cmp(Number A,Number B);

int main(){
	scanf("%d",&n);
	for (int i=0;i<=n;i++) scanf("%d",&C[i]);
	if (C[0]==0){
		int x=0;
		while (C[x]==0) x++;
		n=n-x;
		for (int i=0;i<=n;i++) C[i]=C[i+x];
		Ans[++anscnt]=((Number){0,0,1});
	}
	Fact(C[0],F1,f1);Fact(C[n],F2,f2);
	for (int i=1;i<=f1;i++)
		for (int j=1;j<=f2;j++)
			if (__gcd(F1[i],F2[j])==1){
				if (check(F1[i],F2[j],1)) Ans[++anscnt]=((Number){(ld)F1[i]/(ld)F2[j],F1[i],F2[j]});
				if (check(F1[i],F2[j],-1)) Ans[++anscnt]=((Number){-(ld)F1[i]/(ld)F2[j],-F1[i],F2[j]});
			}
	sort(&Ans[1],&Ans[anscnt+1],cmp);
	printf("%d\n",anscnt);
	for (int i=1;i<=anscnt;i++)
		if (Ans[i].a%Ans[i].b) printf("%d/%d\n",Ans[i].a,Ans[i].b);
		else printf("%d\n",Ans[i].a/Ans[i].b);
	return 0;
}

void Fact(int key,int *F,int &f){
	if (key<0) key=-key;
	for (int i=1;1ll*i*i<=key;i++)
		if (key%i==0){
			F[++f]=i;
			if (1ll*i*i!=key) F[++f]=key/i;
		}
	return;
}

bool check(int a,int b,int f){
	//cout<<"check:"<<a<<" "<<b<<endl;
	int x1=1ll*a*QPow(b,M1-2,M1)%M1;
	int x2=1ll*a*QPow(b,M2-2,M2)%M2;
	if (f==-1) x1=(M1-x1)%M1,x2=(M2-x2)%M2;
	int s1=0,s2=0,xx1=1,xx2=1;
	for (int i=0;i<=n;i++){
		s1=((s1+1ll*xx1*C[i]%M1)%M1+M1)%M1;
		s2=((s2+1ll*xx2*C[i]%M2)%M2+M2)%M2;
		xx1=1ll*xx1*x1%M1;xx2=1ll*xx2*x2%M2;
	}
	return (s1==0)&&(s2==0);
}

int QPow(int x,int cnt,int Mod){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

bool cmp(Number A,Number B){
	return A.key<B.key;
}
