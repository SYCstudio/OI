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
const int SS=(1<<10)-1;
const int inf=2147483647;

class SegmentData
{
public:
	int lkey,rkey,key;
	int sum;
};

int n;
int Seq[maxN];
SegmentData S[maxN<<2];

SegmentData operator + (const SegmentData A,const SegmentData B);
void Build(int now,int l,int r);
SegmentData Query(int now,int l,int r,int ql,int qr);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),Seq[i]=(Seq[i]-1)%9+1;
	//for (int i=1;i<=n;i++) cout<<Seq[i]<<" ";cout<<endl;
	Build(1,1,n);
	int Q;scanf("%d",&Q);
	while (Q--){
		int l,r;scanf("%d%d",&l,&r);
		//cout<<"Q:"<<l<<" "<<r<<endl;
		SegmentData R=Query(1,1,n,l,r);
		int cnt=0;
		for (int i=9;(i>=0)&&(cnt<5);i--)
			if (R.key&(1<<i)){
				printf("%d ",i);++cnt;
			}
		while (cnt<5) printf("-1 "),++cnt;
		printf("\n");
	}
	return 0;
}

SegmentData operator + (const SegmentData A,const SegmentData B){
	SegmentData r;r.lkey=A.lkey;r.rkey=B.rkey;r.key=A.key|B.key;r.sum=(A.sum+B.sum-1)%9+1;
	//cout<<r.key<<endl;
	for (int i=0;i<=9;i++)
		if (A.rkey&(1<<i)){
			r.key|=((B.lkey<<i)&SS);
			if (i) r.key|=((((B.lkey>>(9-i))&SS)>>1)<<1);
		}
	//cout<<r.lkey<<" "<<A.lkey<<" "<<((A.lkey<<B.sum)&SS)<<" "<<((A.lkey>>(9-B.sum))&SS)<<endl;
	r.lkey|=((B.lkey<<A.sum)&SS);
	r.lkey|=((((B.lkey>>(9-A.sum))&SS)>>1)<<1);
	//cout<<r.lkey<<endl;
	r.rkey|=((A.rkey<<B.sum)&SS);
	r.rkey|=((((A.rkey>>(9-B.sum))&SS)>>1)<<1);
	//cout<<r.key<<endl;
	r.key|=r.lkey|r.rkey;
	//cout<<"Merge:["<<A.lkey<<" "<<A.rkey<<" "<<A.key<<" "<<A.sum<<"] ["<<B.lkey<<" "<<B.rkey<<" "<<B.key<<" "<<B.sum<<"] ["<<r.lkey<<" "<<r.rkey<<" "<<r.key<<" "<<r.sum<<"]"<<endl;
	return r;
}

void Build(int now,int l,int r){
	if (l==r){
		S[now].lkey=S[now].rkey=S[now].key=(1<<Seq[l]);
		S[now].sum=Seq[l];return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	S[now]=S[lson]+S[rson];return;
}

SegmentData Query(int now,int l,int r,int ql,int qr){
	//cout<<"["<<l<<","<<r<<"]"<<endl;
	if ((l==ql)&&(r==qr)) return S[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
/*
10
4 1 9 9 5 5 4 4 7 7 
1
4 7
//*/
