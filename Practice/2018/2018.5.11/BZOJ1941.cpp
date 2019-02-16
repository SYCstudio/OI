#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int inf=2147483647;

class KDT
{
public:
	int ls,rs;
	int P[2],Mn[2],Mx[2];
};

int n;
KDT T[maxN];
int root,nowD;
int Min,Max;

bool operator < (KDT A,KDT B);
int Build(int l,int r,int D);
void Update(int now);
void Query_max(int now,int x,int y);
void Query_min(int now,int x,int y);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&T[i].P[0],&T[i].P[1]);
	root=Build(1,n,0);
	int Ans=inf;
	for (int i=1;i<=n;i++)
	{
		Min=inf;Max=-inf;
		Query_max(root,T[i].P[0],T[i].P[1]);Query_min(root,T[i].P[0],T[i].P[1]);
		Ans=min(Ans,Max-Min);
	}
	printf("%d\n",Ans);
}

bool operator < (KDT A,KDT B){
	return A.P[nowD]<B.P[nowD];
}

int Build(int l,int r,int D)
{
	if (l>r) return 0;
	nowD=D;
	int mid=(l+r)>>1;
	nth_element(&T[l],&T[mid],&T[r+1]);
	for (int i=0;i<2;i++) T[mid].Mn[i]=T[mid].Mx[i]=T[mid].P[i];
	T[mid].ls=Build(l,mid-1,D^1);
	T[mid].rs=Build(mid+1,r,D^1);
	Update(mid);return mid;
}

void Update(int now)
{
	int ls=T[now].ls,rs=T[now].rs;
	for (int i=0;i<2;i++)
	{
		if (ls) T[now].Mn[i]=min(T[now].Mn[i],T[ls].Mn[i]),T[now].Mx[i]=max(T[now].Mx[i],T[ls].Mx[i]);
		if (rs) T[now].Mn[i]=min(T[now].Mn[i],T[rs].Mn[i]),T[now].Mx[i]=max(T[now].Mx[i],T[rs].Mx[i]);
	}
	return;
}

void Query_max(int now,int x,int y)
{
	Max=max(Max,abs(x-T[now].P[0])+abs(y-T[now].P[1]));
	int dl=-inf,dr=-inf;
	int ls=T[now].ls,rs=T[now].rs;
	if (ls) dl=max(abs(T[ls].Mn[0]-x),abs(T[ls].Mx[0]-x))+max(abs(T[ls].Mn[1]-y),abs(T[ls].Mx[1]-y));
	if (rs) dr=max(abs(T[rs].Mn[0]-x),abs(T[rs].Mx[0]-x))+max(abs(T[rs].Mn[1]-y),abs(T[rs].Mx[1]-y));
	if (dl>dr)
	{
		if (dl>Max) Query_max(ls,x,y);
		if (dr>Max) Query_max(rs,x,y);
	}
	else
	{
		if (dr>Max) Query_max(rs,x,y);
		if (dl>Max) Query_max(ls,x,y);
	}
	return;
}

void Query_min(int now,int x,int y)
{
	if (abs(x-T[now].P[0])+abs(y-T[now].P[1])!=0) Min=min(Min,abs(x-T[now].P[0])+abs(y-T[now].P[1]));
	int dl=inf,dr=inf;
	int ls=T[now].ls,rs=T[now].rs;
	if (ls) dl=max(0,T[ls].Mn[0]-x)+max(0,x-T[ls].Mx[0])+max(0,T[ls].Mn[1]-y)+max(0,y-T[ls].Mx[1]);
	if (rs) dr=max(0,T[rs].Mn[0]-x)+max(0,x-T[rs].Mx[0])+max(0,T[rs].Mn[1]-y)+max(0,y-T[rs].Mx[1]);
	if (dl<dr)
	{
		if (dl<Min) Query_min(ls,x,y);
		if (dr<Min) Query_min(rs,x,y);
	}
	else
	{
		if (dr<Min) Query_min(rs,x,y);
		if (dl<Min) Query_min(ls,x,y);
	}
	return;
}

