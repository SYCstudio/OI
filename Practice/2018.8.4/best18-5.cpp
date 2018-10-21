#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxN=10100;
const int maxBit=210;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m;
int Seq[maxN];
int Cnt[maxBit][maxN],Ans[maxBit];
int BIT[maxBit][maxN];

void Add(int id,int pos,int key);
int Sum(int id,int pos);

int main(){
	int TTT;scanf("%d",&TTT);
	for (int ti=1;ti<=TTT;ti++){
		mem(Ans,0);mem(BIT,0);mem(Cnt,0);
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
		for (int i=1;i<=n;i++){
			Cnt[1][i]=1;Add(1,Seq[i],1);
			for (int j=2;j<maxBit;j++){
				Cnt[j][i]=Sum(j-1,Seq[i]-1);
				Add(j,Seq[i],Cnt[j][i]);
			}
		}

		for (int i=1;i<=n;i++) for (int j=1;j<maxBit;j++) Ans[j]=(Ans[j]+Cnt[j][i])%Mod;

		printf("Case #%d:",ti);
		for (int i=1;i<=min(n,maxBit-1);i++) printf(" %d",Ans[i]);
		for (int i=maxBit;i<=n;i++) printf(" 0");
		printf("\n");
	}
	return 0;
}

void Add(int id,int pos,int key){
	while (pos<=n){
		BIT[id][pos]=(BIT[id][pos]+key)%Mod;
		pos+=lowbit(pos);
	}
	return;
}

int Sum(int id,int pos){
	int ret=0;
	while (pos){
		ret=(ret+BIT[id][pos])%Mod;
		pos-=lowbit(pos);
	}
	return ret;
}
