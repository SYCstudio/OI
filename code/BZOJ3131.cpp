#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)

const int maxN=101000;
const int Mod=1000000007;
const int inf=2147483647;

class HData
{
public:
	ll key;
	int id;
};

int len,N[20];
int F[2][20][maxN];
ll numcnt,Num[maxN];
ll Sum[maxN];
int Lst[maxN];
priority_queue<Hdata> H;

void dfs(int lst,int cnt,ll mul);
bool operator < (HData A,HData B);

int main(){
	ll n,K;scanf("%lld%lld",&n,&K);
	while (n){
		N[++len]=n%10;
		n/=10;
	}

	dfs(1,1,1);Num[++numcnt]=0;
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1]);

	F[0][0][Find(1)]=1;
	for (int i=0;i<len;i++)
		for (int j=1;j<=numcnt;j++)
			for (int k=0;k<=1;k++)
				if (F[k][j][i])
					for (int p=(i==0)?1:0;p<=9;p++)
						Plus(F[k+p>N[i+1]][Find(Num[j]*p)][i+1],F[k][j][i]);

	for (int i=1;i<=numcnt;i++){
		for (int j=1;j<len;j++) Plus(Sum[i],(F[0][i][j]+F[1][i][j])%Mod);
		Plus(Sum[i],F[0][i][j]);
	}

	sort(&Sum[1],&Sum[numcnt+1]);

	for (int i=1;i<=numcnt;i++) H.push((HData){Sum[1]*Sum[i],i});

	ll Ans=0;
	while (K--){
	}
}

void dfs(int lst,int cnt,ll mul){
	if (cnt==len+1){
		Num[++numcnt]=mul;return;
	}
	for (int i=lst;i<=9;i++)
		dfs(i,cnt+1,mul*i);
	return;
}

bool operator < (HData A,HData B){
	return A.key<B.key;
}
