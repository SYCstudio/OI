#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define find(Arr,x,sz) (lower_bound(&Arr[1],&Arr[sz+1],x)-Arr)

const int maxN=101000;
const int inf=2147483647;

class SegmentData
{
public:
	ll sum,size;
	int ls,rs;
};

class SegmentTree
{
public:
	class Data
	{
	public:
		int key,id;
		bool operator < (Data B){
			return key<B.key;
		}
	};
	
	SegmentData S[maxN*100];
	int nodecnt,root[maxN];
	int numcnt,Id[maxN];
	Data D[maxN];

	void Add(int key,int id){
		D[++numcnt]=((Data){key,id});return;
	}

	bool cmp(Data A,Data B){
		return A.key<B.key;
	}
	
	void Unique(){
		sort(&D[1],&D[numcnt+1]);
		//numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
		for (int i=1;i<=numcnt;i++) Id[D[i].id]=i;
		return;
	}
	
	int Find(int id){
		return Id[id];
	}
	
	void Build(int &now,int l,int r){
		now=++nodecnt;
		if (l==r) return;
		int mid=(l+r)>>1;
		Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
		return;
	}
	
	void Modify(int &now,int l,int r,int pos){
		S[++nodecnt]=S[now];now=nodecnt;
		S[now].size++;S[now].sum+=1ll*D[pos].key;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) Modify(S[now].ls,l,mid,pos);
		else Modify(S[now].rs,mid+1,r,pos);
		return;
	}
	
	int Kth(int r1,int r2,int l,int r,int kth){
		if (l==r) return l;
		int cnt=S[S[r2].ls].size-S[S[r1].ls].size;
		int mid=(l+r)>>1;
		if (cnt>=kth) return Kth(S[r1].ls,S[r2].ls,l,mid,kth);
		else return Kth(S[r1].rs,S[r2].rs,mid+1,r,kth-cnt);
	}

	ll Sum(int r1,int r2,int l,int r,int ql,int qr){
		if (ql>qr) return 0;
		if ((l==ql)&&(r==qr)) return S[r2].sum-S[r1].sum;
		int mid=(l+r)>>1;
		if (qr<=mid) return Sum(S[r1].ls,S[r2].ls,l,mid,ql,qr);
		else if (ql>=mid+1) return Sum(S[r1].rs,S[r2].rs,mid+1,r,ql,qr);
		else return Sum(S[r1].ls,S[r2].ls,l,mid,ql,mid)+Sum(S[r1].rs,S[r2].rs,mid+1,r,mid+1,qr);
	}
};

int n,m;
int X[maxN],Y[maxN];
SegmentTree S1,S2;

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&X[i]);
	for (int i=1;i<=n;i++) scanf("%d",&Y[i]);
	for (int i=1;i<=n;i++)
	{
		int x=X[i],y=Y[i];
		X[i]=x+y;Y[i]=x-y;
		S1.Add(X[i],i);S2.Add(Y[i],i);
	}
	S1.Unique();S2.Unique();
	//cout<<"cnt:"<<S1.numcnt<<" "<<S2.numcnt<<endl;
	S1.Build(S1.root[0],1,S1.numcnt);
	S2.Build(S2.root[0],1,S2.numcnt);
	for (int i=1;i<=n;i++)
	{
		S1.root[i]=S1.root[i-1];S2.root[i]=S2.root[i-1];
		S1.Modify(S1.root[i],1,S1.numcnt,S1.Find(i));
		S2.Modify(S2.root[i],1,S2.numcnt,S2.Find(i));
	}

	for (int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		int mid=(l+r)>>1;
		//cout<<"("<<l<<","<<r<<")"<<mid<<endl;
		int px=S1.Kth(S1.root[l-1],S1.root[r],1,S1.numcnt,mid-l+1);
		int py=S2.Kth(S2.root[l-1],S2.root[r],1,S2.numcnt,mid-l+1);
		ll x=S1.D[px].key,y=S2.D[py].key;
		//cout<<x<<" "<<y<<"("<<px<<" "<<py<<")"<<endl;
		//cout<<x*(mid-l+1)<<" "<<S1.Sum(S1.root[l-1],S1.root[r],1,S1.numcnt,1,px)<<" "<<S1.Sum(S1.root[l-1],S1.root[r],1,S1.numcnt,px+1,S1.numcnt)<<" "<<(r-mid)*x<<endl;
		//cout<<y*(mid-l+1)<<" "<<S2.Sum(S2.root[l-1],S2.root[r],1,S2.numcnt,1,py)<<" "<<S2.Sum(S2.root[l-1],S2.root[r],1,S2.numcnt,py+1,S2.numcnt)<<" "<<(r-mid)*y<<endl;
		ll sum1=(x*(mid-l+1)-S1.Sum(S1.root[l-1],S1.root[r],1,S1.numcnt,1,px))
			+(S1.Sum(S1.root[l-1],S1.root[r],1,S1.numcnt,px+1,S1.numcnt)-(r-mid)*x);
		ll sum2=(y*(mid-l+1)-S2.Sum(S2.root[l-1],S2.root[r],1,S2.numcnt,1,py))
			+(S2.Sum(S2.root[l-1],S2.root[r],1,S2.numcnt,py+1,S2.numcnt)-(r-mid)*y);
		//cout<<"sum:"<<sum1<<" "<<sum2<<endl;
		printf("%.2lf\n",1.0*(sum1+sum2)/2.0);
	}

	return 0;
}
