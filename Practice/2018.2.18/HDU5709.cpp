#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

class SegmentData
{
public:
	int key,ls,rs;
};

int n,m,nodecnt;
int Fa[maxN],Col[maxN],Depth[maxN];
SegmentData S[maxN*110];
int T1[maxN],T2[maxN];

int Modify(int rt,int l,int r,int pos,int opt);
int Merge1(int r1,int r2,int l,int r);
int Merge2(int r1,int r2,int l,int r,int u);
int Query(int now,int l,int r,int d);

int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		nodecnt=0;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d",&Col[i]);
		for (int i=2;i<=n;i++) scanf("%d",&Fa[i]);
		Depth[1]=1;for (int i=2;i<=n;i++) Depth[i]=Depth[Fa[i]]+1;
		//for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";cout<<endl;
		for (int i=1;i<=n;i++)
		{
			T1[i]=Modify(0,1,n,Depth[i],1);
			T2[i]=Modify(0,1,n,Col[i],Depth[i]);
		}
		for (int i=n;i>=2;i--)
		{
			T1[Fa[i]]=Merge1(T1[Fa[i]],T1[i],1,n);
			T2[Fa[i]]=Merge2(T2[Fa[i]],T2[i],1,n,Fa[i]);
		}
		int lastans=0;
		for (int i=1;i<=m;i++)
		{
			int u,dep;scanf("%d%d",&u,&dep);
			u^=lastans;dep^=lastans;
			//cout<<"Q:"<<u<<" "<<Depth[u]<<" "<<min(Depth[u]+dep,n)<<endl;
			printf("%d\n",lastans=Query(T1[u],1,n,min(Depth[u]+dep,n)));
		}
	}
	return 0;
}

int Modify(int rt,int l,int r,int pos,int opt)
{
	int nrt=++nodecnt;S[nrt].key=S[rt].key+opt;
	if (l==r) return nrt;
	int mid=(l+r)>>1;
	if (pos<=mid) S[nrt].ls=Modify(S[rt].ls,l,mid,pos,opt),S[nrt].rs=S[rt].rs;
	else S[nrt].ls=S[rt].ls,S[nrt].rs=Modify(S[rt].rs,mid+1,r,pos,opt);
	return nrt;
}

int Merge1(int r1,int r2,int l,int r)
{
	if ((r1==0)||(r2==0)) return r1+r2;
	int nrt=++nodecnt;S[nrt].key=S[r1].key+S[r2].key;
	if (l==r) return nrt;
	int mid=(l+r)>>1;
	S[nrt].ls=Merge1(S[r1].ls,S[r2].ls,l,mid);
	S[nrt].rs=Merge1(S[r1].rs,S[r2].rs,mid+1,r);
	return nrt;
}

int Merge2(int r1,int r2,int l,int r,int u)
{
	if ((r1==0)||(r2==0)) return r1+r2;
	int nrt=++nodecnt;
	if (l==r)
	{
		if (S[r1].key>S[r2].key){
			S[nrt].key=S[r2].key;T1[u]=Modify(T1[u],1,n,S[r1].key,-1);
		}
		else{
			S[nrt].key=S[r1].key;T1[u]=Modify(T1[u],1,n,S[r2].key,-1);
		}
		return nrt;
	}
	int mid=(l+r)>>1;
	S[nrt].ls=Merge2(S[r1].ls,S[r2].ls,l,mid,u);
	S[nrt].rs=Merge2(S[r1].rs,S[r2].rs,mid+1,r,u);
	return nrt;
}

int Query(int now,int l,int r,int d)
{
	if (now==0) return 0;
	if (r<=d) return S[now].key;
	int mid=(l+r)>>1;
	int ret=Query(S[now].ls,l,mid,d);
	if (d>=mid+1) ret+=Query(S[now].rs,mid+1,r,d);
	return ret;
}
