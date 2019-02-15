#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int R=100000;
const int Mod=19961993;
const int P[60]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
const int inf=2147483647;

int Mul[maxN<<2];
ll S[maxN<<2];
int Inv[60];

int QPow(int x,int cnt);
void Build(int now,int l,int r);
void Modify(int now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr,ll &s);

int main(){
	for (int i=0;i<60;i++) Inv[i]=QPow(P[i],Mod-2);
	Build(1,1,R);
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int opt,a,b;scanf("%d%d%d",&opt,&a,&b);
		if (opt==0){
			ll s=0;
			ll num=Query(1,1,R,a,b,s);
			for (int i=0;i<60;i++) if (s&(1ll<<i)) num=1ll*num*Inv[i]%Mod*(P[i]-1)%Mod;

			printf("%lld\n",num);
		}
		if (opt==1) Modify(1,1,R,a,b);
	}
	
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void Build(int now,int l,int r){
	if (l==r){
		Mul[now]=3;S[now]=1<<1;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Mul[now]=1ll*Mul[lson]*Mul[rson]%Mod;
	S[now]=S[lson]|S[rson];return;
}

void Modify(int now,int l,int r,int pos,int key){
	if (l==r){
		Mul[now]=key;S[now]=0;
		for (int i=0;i<60;i++) if (key%P[i]==0) S[now]|=(1ll<<i);
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Mul[now]=1ll*Mul[lson]*Mul[rson]%Mod;
	S[now]=S[lson]|S[rson];return;
}

int Query(int now,int l,int r,int ql,int qr,ll &s){
	if ((l==ql)&&(r==qr)){
		s=s|S[now];return Mul[now];
	}
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr,s);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr,s);
	else return 1ll*Query(lson,l,mid,ql,mid,s)*Query(rson,mid+1,r,mid+1,qr,s)%Mod;
}
