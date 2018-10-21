#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int inf=2147483647;

class SegmentData
{
public:
	ll sum,lz;
	int ls,rs;
};

class Data
{
public:
	int l,r,key;
};

int n,m,p1,p2;
int nodecnt,root[maxN],Val[maxN],St[maxN],L[maxN],R[maxN];
SegmentData S[maxN*100];
vector<Data> V[maxN];

void Build(int &now,int l,int r);
void Modify(int &now,int l,int r,int ql,int qr,int key);
ll Query(int r1,int r2,int l,int r,int ql,int qr);

int main()
{
	scanf("%d%d%d%d",&n,&m,&p1,&p2);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
	int top=0;St[0]=0;
	for (int i=1;i<=n;i++)
	{
		while ((top)&&(Val[St[top]]<=Val[i])) top--;
		L[i]=St[top];St[++top]=i;
	}
	top=0;St[0]=n+1;
	for (int i=n;i>=1;i--)
	{
		while ((top)&&(Val[St[top]]<=Val[i])) top--;
		R[i]=St[top];St[++top]=i;
	}

	//for (int i=1;i<=n;i++) cout<<L[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<R[i]<<" ";cout<<endl;

	for (int i=1;i<=n;i++)
	{
		if (L[i]) V[i].push_back((Data){L[i],L[i],p1});
		if (R[i]!=n+1) V[i].push_back((Data){R[i],R[i],p1});
		if ((L[i])&&(i+1<=R[i]-1)) V[L[i]].push_back((Data){i+1,R[i]-1,p2});
		if ((R[i])&&(L[i]+1<=i-1)) V[R[i]].push_back((Data){L[i]+1,i-1,p2});
	}
	Build(root[0],1,n);
	for (int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		for (int j=0;j<V[i].size();j++)
		{
			//cout<<"["<<V[i][j].l<<","<<V[i][j].r<<"] "<<V[i][j].key<<endl;
			Modify(root[i],1,n,V[i][j].l,V[i][j].r,V[i][j].key);
		}
	}

	for (int i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);
		printf("%lld\n",Query(root[l-1],root[r],1,n,l,r));
	}

	return 0;
}

void Build(int &now,int l,int r)
{
	now=++nodecnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(S[now].ls,l,mid);Build(S[now].rs,mid+1,r);
	return;
}

void Modify(int &now,int l,int r,int ql,int qr,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].sum+=1ll*key*(qr-ql+1);
	if ((l==ql)&&(r==qr)){
		S[now].lz+=key;return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr,key);
	else
	{
		Modify(S[now].ls,l,mid,ql,mid,key);
		Modify(S[now].rs,mid+1,r,mid+1,qr,key);
	}
	return;
}

ll Query(int r1,int r2,int l,int r,int ql,int qr)
{
	if ((l==ql)&&(r==qr)) return S[r2].sum-S[r1].sum;
	ll ret=1ll*(qr-ql+1)*(S[r2].lz-S[r1].lz);
	int mid=(l+r)>>1;
	if (qr<=mid) return ret+Query(S[r1].ls,S[r2].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return ret+Query(S[r1].rs,S[r2].rs,mid+1,r,ql,qr);
	else return ret+Query(S[r1].ls,S[r2].ls,l,mid,ql,mid)+Query(S[r1].rs,S[r2].rs,mid+1,r,mid+1,qr);
}
