#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Mod=1000000007;
const int inf=2147483647;

class Data
{
public:
	int pos,key;
};

int n,m,K;
Data D[maxN];

bool cmp(Data A,Data B);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=K;i++) scanf("%d%d",&D[i].pos,&D[i].key);
	sort(&D[1],&D[K+1],cmp);
	int cnt=0,Ans=1,s=1ll*n*(n+1)/2%Mod;
	for (int i=1,j;i<=K;i=j+1){
		j=i;int sum=s;cnt++;sum=(sum-D[i].key+Mod)%Mod;
		while ((j<K)&&(D[j+1].pos==D[i].pos)){
			j++;if (D[j].key!=D[j-1].key) sum=(sum-D[j].key+Mod)%Mod;
		}
		//cout<<"("<<i<<","<<j<<") "<<sum<<endl;
		Ans=1ll*Ans*sum%Mod;
	}
	cnt=m-cnt;
	while (cnt){
		if (cnt&1) Ans=1ll*Ans*s%Mod;
		s=1ll*s*s%Mod;cnt>>=1;
	}
	printf("%d\n",Ans);return 0;
}

bool cmp(Data A,Data B){
	if (A.pos!=B.pos) return A.pos<B.pos;
	return A.key<B.key;
}
