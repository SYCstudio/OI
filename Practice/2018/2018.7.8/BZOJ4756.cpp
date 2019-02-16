#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class SegmentData
{
public:
	int ls,rs,sum;
};

int n;
vector<int> To[maxN];
int numcnt,Num[maxN],Val[maxN],Ans[maxN];
int nodecnt,root[maxN];
SegmentData S[maxN*50];

void dfs(int u);
void Modify(int &now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);
int Merge(int r1,int r2);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]),Num[++numcnt]=Val[i];
	Num[++numcnt]=inf;
	
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	for (int i=1;i<=n;i++) Val[i]=lower_bound(&Num[1],&Num[numcnt+1],Val[i])-Num;

	for (int i=2;i<=n;i++)
	{
		int fa;scanf("%d",&fa);
		To[fa].push_back(i);
	}

	dfs(1);

	for (int i=1;i<=n;i++) printf("%d\n",Ans[i]);
	return 0;
}

void dfs(int u)
{
	int sz=To[u].size();
	for (int i=0;i<sz;i++){
		dfs(To[u][i]);root[u]=Merge(root[u],root[To[u][i]]);
	}
	Ans[u]=Query(root[u],1,numcnt,Val[u]+1,numcnt);
	Modify(root[u],1,numcnt,Val[u],1);
	return;
}

void Modify(int &now,int l,int r,int pos,int key)
{
	S[++nodecnt]=S[now];now=nodecnt;
	S[now].sum+=key;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(S[now].ls,l,mid,pos,key);
	else Modify(S[now].rs,mid+1,r,pos,key);
	return;
}

int Query(int now,int l,int r,int ql,int qr)
{
	if (now==0) return 0;
	if ((l==ql)&&(r==qr)) return S[now].sum;
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(S[now].ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(S[now].rs,mid+1,r,ql,qr);
	else return Query(S[now].ls,l,mid,ql,mid)+Query(S[now].rs,mid+1,r,mid+1,qr);
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	int now=++nodecnt;
	S[now].sum=S[r1].sum+S[r2].sum;
	S[now].ls=Merge(S[r1].ls,S[r2].ls);
	S[now].rs=Merge(S[r1].rs,S[r2].rs);
	return now;
}
