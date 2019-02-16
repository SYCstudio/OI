#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxBlock=350;
const int inf=2147483647;

int n;
int Num[maxN];
int Xor[maxN],Gcd[maxN];
map<int,int> Mp[maxBlock];
int blocksize,blockcnt,Belong[maxN],L[maxN],R[maxN];
char Input[10];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Num[i]);

	blocksize=sqrt(n);
	for (int i=1;i<=n;i++){
		Belong[i]=i/blocksize+1;
		if (L[Belong[i]]==0) L[Belong[i]]=i;
		R[Belong[i]]=i;
	}
	blockcnt=Belong[n];

	for (int i=1;i<=n;i++){
		if (L[Belong[i]]==i) Gcd[i]=Xor[i]=Num[i];
		else Gcd[i]=__gcd(Gcd[i-1],Num[i]),Xor[i]=Xor[i-1]^Num[i];
		if (Mp[Belong[i]].count(Xor[i])==0) Mp[Belong[i]][Xor[i]]=i;
	}

	int Q;scanf("%d",&Q);
	while (Q--){
		scanf("%s",Input);
		if (Input[0]=='M'){
			int p,x;scanf("%d%d",&p,&x);p++;Num[p]=x;
			int b=Belong[p];
			for (int i=p;i<=R[b];i++) if (Mp[b][Xor[i]]==i) Mp[b].erase(Xor[i]);
			for (int i=p;i<=R[b];i++){
				if (L[b]==i) Gcd[i]=Xor[i]=Num[i];
				else Gcd[i]=__gcd(Gcd[i-1],Num[i]),Xor[i]=Xor[i-1]^Num[i];
				if (Mp[b].count(Xor[i])==0) Mp[b][Xor[i]]=i;
			}
		}
		if (Input[0]=='Q'){
			ll x;scanf("%lld",&x);
			bool flag=0;
			for (int i=1;i<=R[1];i++)
				if (1ll*Gcd[i]*Xor[i]==x){
					flag=1;printf("%d\n",i-1);break;
				}
			if (flag) continue;
			int lstgcd=Gcd[R[1]],lstxor=Xor[R[1]];
			for (int i=2;i<=blockcnt;i++){
				if (__gcd(lstgcd,Gcd[R[i]])==lstgcd){
					if (x%lstgcd==0){
						ll fd=(x/lstgcd)^lstxor;
						if ( ((int)fd==fd) && (Mp[i].count(fd)) ){
							flag=1;printf("%d\n",Mp[i][fd]-1);break;
						}
					}
					lstxor^=Xor[R[i]];
				}
				else{
					for (int j=L[i];j<=R[i];j++){
						lstgcd=__gcd(lstgcd,Num[j]);
						lstxor=lstxor^Num[j];
						if (1ll*lstgcd*lstxor==x){
							flag=1;printf("%d\n",j-1);break;
						}
					}
				}
				if (flag) break;
			}
			if (flag==0) printf("no\n");
		}
	}

	return 0;
}
