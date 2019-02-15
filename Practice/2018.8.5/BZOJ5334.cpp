#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int inf=2147483647;

int Q,Mod;
vector<int> S[maxN<<2];
int Val[maxN],app[maxN],dip[maxN];

void Build(int now,int l,int r);
void Modify(int now,int l,int r,int ql,int qr,int key);
void Query(int now,int l,int r,int key);

int main(){
	int TTT;scanf("%d",&TTT);
	while (TTT--){
		scanf("%d%d",&Q,&Mod);
		Build(1,1,Q);
		mem(Val,-1);mem(dip,-1);
		for (int i=1;i<=Q;i++){
			int opt;scanf("%d",&opt);
			if (opt==1){
				scanf("%d",&Val[i]);app[i]=i;
			}
			if (opt==2){
				int pos;scanf("%d",&pos);
				dip[pos]=i-1;
			}
		}
		for (int i=1;i<=Q;i++) if (dip[i]==-1) dip[i]=Q;
		for (int i=1;i<=Q;i++) if (Val[i]!=-1) Modify(1,1,Q,app[i],dip[i],Val[i]);

		Query(1,1,Q,1);
	}

	return 0;
}

void Build(int now,int l,int r){
	S[now].clear();
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key){
	if ((l==ql)&&(r==qr)){
		S[now].push_back(key);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else{
		Modify(lson,l,mid,ql,mid,key);Modify(rson,mid+1,r,mid+1,qr,key);
	}
	return;
}

void Query(int now,int l,int r,int key)
{
	for (int sz=S[now].size(),i=0;i<sz;i++) key=1ll*key*S[now][i]%Mod;
	if (l==r){
		printf("%d\n",key);return;
	}
	int mid=(l+r)>>1;
	Query(lson,l,mid,key);Query(rson,mid+1,r,key);
	return;
}

/*
2
10 1000000000
1 2
2 1
1 2
1 10
2 3
2 4
1 6
1 7
1 12
2 7
10 1000000000
1 2
2 1
1 2
1 10
2 3
2 4
1 6
1 7
1 12
2 7
//*/
