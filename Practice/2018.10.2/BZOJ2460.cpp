#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxBit=64;
const int inf=2147483647;

class Data
{
public:
	int key;ll id;
};

int n;
Data D[maxN];
ll Base[maxN];

bool Insert(ll key);
bool cmp(Data A,Data B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%d",&D[i].id,&D[i].key);
	ll Ans=0;sort(&D[1],&D[n+1],cmp);
	for (int i=1;i<=n;i++)
		if (Insert(D[i].id)) Ans+=D[i].key;
	printf("%lld\n",Ans);return 0;
}

bool Insert(ll key){
	for (int i=maxBit-1;i>=0;i--)
		if (key&(1ll<<i)){
			if (Base[i]==0){
				Base[i]=key;return 1;
			}
			key^=Base[i];
		}
	return 0;
}

bool cmp(Data A,Data B){
	return A.key>=B.key;
}
