#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int maxNum=50000;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs,cnt;
};

int n,m;
int root[maxN],nodecnt=0;
SegmentData S[maxN<<2];

void Modify(int &now,int l,int r,int key);
int Query(int r1,int r2,int l,int r,int sz);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		int key;scanf("%d",&key);
		root[i]=root[i-1];
		Modify(root[i],1,maxNum,key);
	}
	while (m--){
		int l,r;scanf("%d%d",&l,&r);
		printf("%d\n",Query(root[l-1],root[r],1,maxNum,(r-l+1)/2));
	}
	return 0;
}

void Modify(int &now,int l,int r,int key){
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].cnt++;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (key<=mid) Modify(S[now].ls,l,mid,key);
	else Modify(S[now].rs,mid+1,r,key);
}

int Query(int r1,int r2,int l,int r,int sz){
	if (l==r) return l;
	int mid=(l+r)>>1;
	if (S[S[r2].ls].cnt-S[S[r1].ls].cnt>sz) return Query(S[r1].ls,S[r2].ls,l,mid,sz);
	if (S[S[r2].rs].cnt-S[S[r1].rs].cnt>sz) return Query(S[r1].rs,S[r2].rs,mid+1,r,sz);
	return 0;
}
/*
5 3
1
2
2
1
1
1 5
2 5
2 4
//*/
