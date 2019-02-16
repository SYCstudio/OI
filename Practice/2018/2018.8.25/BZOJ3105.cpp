#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=111;
const int maxBit=32;
const int inf=2147483647;

ll Seq[maxN];
int Base[maxBit];

bool Insert(int key);

int main(){
	int n;scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Seq[i]);
	sort(&Seq[1],&Seq[n+1]);
	ll sum=0;
	for (int i=n;i>=1;i--)
		if (Insert(Seq[i])==0) sum+=Seq[i];
	printf("%lld\n",sum);
	return 0;
}

bool Insert(int key){
	for (int i=maxBit-1;i>=0;i--)
		if (key&(1<<i)){
			if (Base[i]==0){
				Base[i]=key;return 1;
			}
			key^=Base[i];
		}
	return 0;
}
