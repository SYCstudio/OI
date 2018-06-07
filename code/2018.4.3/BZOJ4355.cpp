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
#define RG register
#define IL inline

const int maxN=301000;
const int inf=2147483647;
const ll INF=1e15;

class SegmentData
{
public:
	ll mn,mns;
	ll cnt;
	ll cover,add,delta;
	ll size;
	SegmentData(){
		cover=delta=-INF;add=0;
		return;
	}
};

int n,m;
ll Arr[maxN];
SegmentData S[maxN<<2];

IL void PushDown(RG int now);
IL void Update(RG int now);
IL void Cover(RG int now,RG ll key);
IL void Add(RG int now,RG ll key);
IL void Delta(RG int now,RG ll key);
void Build(RG int now,RG int l,RG int r);
void Modify_cover(RG int now,RG int l,RG int r,RG int ql,RG int qr,RG ll key);
void Modify_add(RG int now,RG int l,RG int r,RG int ql,RG int qr,RG ll key);
void Modify_mx(RG int now,RG int l,RG int r,RG int ql,RG int qr,RG ll key);
ll Query(RG int now,RG int l,RG int r,RG int ql,RG int qr);

int main()
{
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	//ios::sync_with_stdio(false);
	//cin>>n>>m;
	scanf("%d%d",&n,&m);
	for (RG int i=1;i<=n;i++) scanf("%lld",&Arr[i]);//cin>>Arr[i];
	Build(1,1,n);
	while (m--)
	{
		RG int opt;scanf("%d",&opt);//cin>>opt;
		if (opt==1)
		{
			RG int l,r,c;scanf("%d%d%d",&l,&r,&c);//cin>>l>>r>>c;
			Modify_cover(1,1,n,l,r,c);
		}
		if (opt==2)
		{
			RG int l,r,c;scanf("%d%d%d",&l,&r,&c);//cin>>l>>r>>c;
			Modify_add(1,1,n,l,r,c);
			Modify_mx(1,1,n,l,r,0);
		}
		if (opt==3)
		{
			RG int l,r;scanf("%d%d",&l,&r);//cin>>l>>r;
			//cout<<Query(1,1,n,l,r)<<endl;
			printf("%lld\n",Query(1,1,n,l,r));
		}
	}
	return 0;
}

IL void PushDown(RG int now)
{
	if (S[now].add)
	{
		Add(lson,S[now].add);Add(rson,S[now].add);
		S[now].add=0;
	}
	if (S[now].cover!=-INF)
	{
		Cover(lson,S[now].cover);Cover(rson,S[now].cover);
		S[now].cover=-INF;
	}
	if (S[now].delta!=-INF)
	{
		Delta(lson,S[now].delta);Delta(rson,S[now].delta);
		S[now].delta=-INF;
	}
	return;
}

IL void Update(RG int now)
{
	S[now].mn=min(S[lson].mn,S[rson].mn);
	S[now].mns=min(S[lson].mns,S[rson].mns);
	if (S[now].mn!=S[lson].mn) S[now].mns=min(S[now].mns,S[lson].mn);
	if (S[now].mn!=S[rson].mn) S[now].mns=min(S[now].mns,S[rson].mn);
	S[now].cnt=0;
	if (S[now].mn==S[lson].mn) S[now].cnt+=S[lson].cnt;
	if (S[now].mn==S[rson].mn) S[now].cnt+=S[rson].cnt;
	return;
}

IL void Cover(RG int now,RG ll key)
{
	S[now].mn=key;S[now].mns=INF;S[now].add=0;S[now].delta=-INF;
	S[now].cover=key;S[now].cnt=S[now].size;
	return;
}

IL void Add(RG int now,RG ll key)
{
	S[now].mn+=key;
	if (S[now].mns!=inf) S[now].mns+=key;
	if (S[now].cover!=-INF) S[now].cover+=key;
	else S[now].add+=key;
	if (S[now].delta!=-INF) S[now].delta+=key;
	return;
}

IL void Delta(RG int now,RG ll key)
{
	if (S[now].mn<key)
	{
		S[now].mn=key;
		S[now].delta=max(S[now].delta,key);
	}
	return;
}

void Build(RG int now,RG int l,RG int r)
{
	S[now].size=r-l+1;
	if (l==r)
	{
		S[now].mn=Arr[l];S[now].mns=INF;
		S[now].cnt=1;
		return;
	}
	RG int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Update(now);return;
}

void Modify_cover(RG int now,RG int l,RG int r,RG int ql,RG int qr,RG ll key)
{
	if ((l==ql)&&(r==qr)){
		Cover(now,key);return;
	}
	PushDown(now);
	RG int mid=(l+r)>>1;
	if (qr<=mid) Modify_cover(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify_cover(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify_cover(lson,l,mid,ql,mid,key);
		Modify_cover(rson,mid+1,r,mid+1,qr,key);
	}
	Update(now);return;
}

void Modify_add(RG int now,RG int l,RG int r,RG int ql,RG int qr,RG ll key)
{
	if ((l==ql)&&(r==qr)){
		Add(now,key);return;
	}
	PushDown(now);
	RG int mid=(l+r)>>1;
	if (qr<=mid) Modify_add(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify_add(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify_add(lson,l,mid,ql,mid,key);
		Modify_add(rson,mid+1,r,mid+1,qr,key);
	}
	Update(now);return;
}

void Modify_mx(RG int now,RG int l,RG int r,RG int ql,RG int qr,RG ll key)
{
	if ((l==ql)&&(r==qr))
	{
		if (S[now].mn>=key) return;
		if (S[now].mns>key)
		{
			//Delta(now,key);
			S[now].delta=S[now].mn=key;
			return;
		}
		PushDown(now);
		int mid=(l+r)>>1;
		Modify_mx(lson,l,mid,ql,mid,key);
		Modify_mx(rson,mid+1,r,mid+1,qr,key);
		Update(now);return;
	}
	PushDown(now);
	RG int mid=(l+r)>>1;
	if (qr<=mid) Modify_mx(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify_mx(rson,mid+1,r,ql,qr,key);
	else
	{
		Modify_mx(lson,l,mid,ql,mid,key);
		Modify_mx(rson,mid+1,r,mid+1,qr,key);
	}
	Update(now);return;
}

ll Query(RG int now,RG int l,RG int r,RG int ql,RG int qr)
{
	if ((l==ql)&&(r==qr)) return ((S[now].mn==0)?(S[now].cnt):(0));
	PushDown(now);
	RG int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}
