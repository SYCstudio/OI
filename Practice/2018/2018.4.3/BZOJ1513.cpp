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

const int maxN=1010;
const int inf=2147483647;

int n,m;

class InSegTree
{
public:
	int Val[maxN<<2],Lazy[maxN<<2];
	void Modify(int now,int l,int r,int ql,int qr,int key){
		Val[now]=max(Val[now],key);
		if ((l==ql)&&(r==qr))
		{
			Lazy[now]=max(Lazy[now],key);
			return;
		}
		int mid=(l+r)>>1;
		if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
		else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
		else
		{
			Modify(lson,l,mid,ql,mid,key);
			Modify(rson,mid+1,r,mid+1,qr,key);
		}
		return;
	}
	int Query(int now,int l,int r,int ql,int qr){
		if ((l==ql)&&(r==qr)) return max(Val[now],Lazy[now]);
		int Ret=Lazy[now];
		int mid=(l+r)>>1;
		if (qr<=mid) return max(Ret,Query(lson,l,mid,ql,qr));
		else if (ql>=mid+1) return max(Ret,Query(rson,mid+1,r,ql,qr));
		else return max(Ret,max(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr)));
	}
};

class OutSegTree
{
public:
	InSegTree Val[maxN<<2],Lazy[maxN<<2];
	void Modify(int now,int l,int r,int ql,int qr,int p,int q,int key){
		Val[now].Modify(1,1,m,p,q,key);
		if ((l==ql)&&(r==qr))
		{
			Lazy[now].Modify(1,1,m,p,q,key);
			return;
		}
		int mid=(l+r)>>1;
		if (qr<=mid) Modify(lson,l,mid,ql,qr,p,q,key);
		else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,p,q,key);
		else
		{
			Modify(lson,l,mid,ql,mid,p,q,key);
			Modify(rson,mid+1,r,mid+1,qr,p,q,key);
		}
		return;
	}
	int Query(int now,int l,int r,int ql,int qr,int p,int q){
		if ((l==ql)&&(r==qr)) return Val[now].Query(1,1,m,p,q);
		int mid=(l+r)>>1;
		int Ret=Lazy[now].Query(1,1,m,p,q);
		if (qr<=mid) return max(Ret,Query(lson,l,mid,ql,qr,p,q));
		else if (ql>=mid+1) return max(Ret,Query(rson,mid+1,r,ql,qr,p,q));
		else return max(Ret,max(Query(lson,l,mid,ql,mid,p,q),Query(rson,mid+1,r,mid+1,qr,p,q)));
	}
};

OutSegTree S;

int main()
{
	ios::sync_with_stdio(false);
	int Q;
	cin>>n>>m>>Q;n++;m++;
	while (Q--)
	{
		int d,s,w,x,y;cin>>d>>s>>w>>x>>y;x++;y++;
		w=w+S.Query(1,1,n,x,x+d-1,y,y+s-1);
		//cout<<w<<endl;
		S.Modify(1,1,n,x,x+d-1,y,y+s-1,w);
	}
	cout<<S.Query(1,1,n,1,n,1,m)<<endl;
	return 0;
}
