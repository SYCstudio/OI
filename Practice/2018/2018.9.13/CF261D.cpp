#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=505000;
const int inf=2147483647;

int n,T,Mx;
int Seq[maxN];
int F[maxN];

int main(){
	int Case;scanf("%d",&Case);
	scanf("%d%d%d",&n,&Mx,&T);T=min(T,Mx);T=T*n;
	while (Case--){
		for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
		mem(F,0);
		for (int i=1;i<=T;i++){
			int k=Seq[(i-1)%n+1];
			for (int j=k;(j<=Mx)&&(F[j]<F[k-1]+1);j++)
				F[j]=F[k-1]+1;
		}
		int Ans=0;
		for (int i=1;i<=Mx;i++) Ans=max(Ans,F[i]);
		printf("%d\n",Ans);
	}

	return 0;
}
