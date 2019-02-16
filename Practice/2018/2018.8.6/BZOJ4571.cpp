#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=401000;
const int Num=400000;
const int maxBit=18;
const int inf=2147483647;

class SegmentData
{
public:
	int cnt,ls,rs;
};

int n,m;
int nodecnt=0,root[maxN];
SegmentData S[maxN*40];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int pos);
int Query(int r1,int r2,int l,int r,int ql,int qr);

int main(){
	scanf("%d%d",&n,&m);
	Build(root[0],0,Num);

	for (int i=1;i<=n;i++){
		int key;scanf("%d",&key);
		root[i]=root[i-1];Modify(root[i],0,Num,key);
	}

	//cout<<"Input"<<endl;

	while (m--){
		int b,x,l,r;scanf("%d%d%d%d",&b,&x,&l,&r);
		int ans=0,key=0;
		for (int i=maxBit;i>=0;i--){
			int c=(b&(1<<i))!=0;
			int ql,qr;
			if (c) ql=key,qr=key+(1<<i)-1;
			else ql=key+(1<<i),qr=key+(1<<(i+1))-1;
			//cout<<"Q:"<<ql<<" "<<qr<<","<<max(0,ql-x)<<" "<<max(0,qr-x)<<endl;
			if (max(0,qr-x)>Num) continue;
			if (qr-x<0) continue;
			if (Query(root[l-1],root[r],0,Num,max(0,ql-x),max(0,qr-x))) ans|=(1<<i),key|=((c^1)<<i);
			else key|=(c<<i);
		}
		printf("%d\n",ans);
	}
	return 0;
}

void Build(int &now,int l,int r){
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int pos){
	S[++nodecnt]=S[now];now=nodecnt;S[now].cnt++;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos);
	else Modify(S[now].rs,mid+1,r,pos);
	return;
}

int Query(int r1,int r2,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[r2].cnt-S[r1].cnt;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[r1].ls,S[r2].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(S[r1].rs,S[r2].rs,mid+1,r,ql,qr);
	else return Query(S[r1].ls,S[r2].ls,l,mid,ql,mid)+Query(S[r1].rs,S[r2].rs,mid+1,r,mid+1,qr);
}
