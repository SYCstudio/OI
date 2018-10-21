#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "for"

const int maxN=103000;
const int maxNum=1000100;
const int inf=2147483647;

class BIT
{
public:
	int B[maxNum],up;
	void Add(int pos,int key){
		++pos;
		while (pos<=up) B[pos]+=key,pos+=(pos)&(-pos);
		return;
	}
	int Sum(int pos){
		int ret=0;++pos;
		while (pos) ret+=B[pos],pos-=(pos)&(-pos);
		return ret;
	}
	int Query(int l,int r){
		if (l>r) return 0;
		return Sum(r)-Sum(l-1);
	}
	void Init(int n){
		mem(B,0);up=n+10;return;
	}
};

ll n;
ll Seq[maxN];
BIT B0,B1;

void Calc();

int main(){
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Seq[i]);

	Calc();

	return 0;
}

void Calc(){
	for (int i=2;i<=n;i++) Seq[i]+=Seq[i-1];
	ll Ans=0;
	for (int k=0;(1<<k)<Seq[n];k++){
		ll up=1<<k;ll cnt=0;
		B0.Init(up);B1.Init(up);
		B0.Add(0,1);
		for (int i=1;i<=n;i++){
			ll key=Seq[i]&(up-1);
			//cout<<k<<" "<<i<<" "<<Seq[i]<<" "<<key<<endl;
			if (Seq[i]&(1<<k)) cnt+=B0.Query(0,key)+B1.Query(key+1,up),B1.Add(key,1);
			else cnt+=B0.Query(key+1,up)+B1.Query(0,key),B0.Add(key,1);
		}
		Ans|=(1ll<<k)*(cnt%2);
	}
	printf("%lld\n",Ans);return;
}
