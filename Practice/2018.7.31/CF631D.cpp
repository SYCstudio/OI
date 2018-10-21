#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int inf=2147483647;

class Data{
public:
	ll t;
	char c;
};

int n,m;
Data S[maxN],T[maxN];
int Next[maxN];

int main(){
	scanf("%d%d",&n,&m);
	int t1=0;
	for (int i=1;i<=n;i++){
		ll k;char c;scanf("%lld-%c",&k,&c);
		if (c==S[t1].c) S[t1].t+=k;
		else S[++t1]=((Data){k,c});
	}
	n=t1;t1=0;
	for (int i=1;i<=m;i++){
		ll k;char c;scanf("%lld-%c",&k,&c);
		if (c==T[t1].c) T[t1].t+=k;
		else T[++t1]=((Data){k,c});
	}
	m=t1;

	Next[1]=Next[2]=1;
	for (int i=3;i<m;i++){
		int j=Next[i-1];
		while ((j!=1)&&((T[j+1].c!=T[i].c)||(T[j+1].t!=T[i].t))) j=Next[j];
		if ((T[j+1].c==T[i].c)&&(T[j+1].t==T[i].t)) j++;Next[i]=j;
	}

	ll Ans=0;
	if (m==1){
		for (int i=1;i<=n;i++) if ((S[i].c==T[1].c)&&(S[i].t>=T[1].t)) Ans=Ans+(S[i].t-T[1].t+1);
		printf("%lld\n",Ans);
	}
	else if (m==2){
		for (int i=1;i<n;i++) if ((S[i].c==T[1].c)&&(S[i].t>=T[1].t)&&(S[i+1].c==T[2].c)&&(S[i+1].t>=T[2].t)) Ans++;
		printf("%lld\n",Ans);
	}
	else{
		for (int i=1,j=1;i<=n;i++){
			while ((j!=1)&&((T[j+1].c!=S[i].c)||(T[j+1].t!=S[i].t))) j=Next[j];
			if ((T[j+1].c==S[i].c)&&(T[j+1].t==S[i].t)) j++;
			if (j==m-1){
				if ((S[i-m+2].c==T[1].c)&&(S[i-m+2].t>=T[1].t)&&(S[i+1].c==T[m].c)&&(S[i+1].t>=T[m].t)) Ans++;
				j=Next[j];
			}
		}
		printf("%lld\n",Ans);
	}

	return 0;
}
