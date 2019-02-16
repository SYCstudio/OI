#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000*2;
const int maxK=2;
const int inf=2147483647;

class KDT
{
public:
	int P[maxK],Mn[maxK],Mx[maxK];
	int ls,rs;
};

int n,m;
int nowD,root,Ans;
KDT T[maxN];

bool operator < (KDT A,KDT B);
int Build(int l,int r,int D);
void Update(int now);
void Insert(int now,int D);
void Query(int now,int x,int y);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d%d",&T[i].P[0],&T[i].P[1]);
	root=Build(1,n,0);
	for (int i=1;i<=m;i++)
	{
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if (opt==1)
		{
			T[++n].P[0]=x;T[n].P[1]=y;
			for (int i=0;i<2;i++) T[n].Mn[i]=T[n].Mx[i]=T[n].P[i];
			Insert(root,0);
		}
		else
		{
			Ans=inf;
			Query(root,x,y);
			printf("%d\n",Ans);
		}
	}
	return 0;
}

bool operator < (KDT A,KDT B){
	return A.P[nowD]<B.P[nowD];
}

int Build(int l,int r,int D)
{
	if (l>r) return 0;
	int mid=(l+r)>>1;
	nowD=D;
	nth_element(&T[l],&T[mid],&T[r+1]);
	for (int i=0;i<2;i++) T[mid].Mn[i]=T[mid].Mx[i]=T[mid].P[i];
	T[mid].ls=Build(l,mid-1,D^1);
	T[mid].rs=Build(mid+1,r,D^1);
	Update(mid);return mid;
}

void Update(int now)
{
	for (int i=0;i<2;i++)
	{
		if (T[now].ls) T[now].Mn[i]=min(T[now].Mn[i],T[T[now].ls].Mn[i]),T[now].Mx[i]=max(T[now].Mx[i],T[T[now].ls].Mx[i]);
		if (T[now].rs) T[now].Mn[i]=min(T[now].Mn[i],T[T[now].rs].Mn[i]),T[now].Mx[i]=max(T[now].Mx[i],T[T[now].rs].Mx[i]);
	}
	return;
}

void Insert(int now,int D)
{
	//cout<<"I:("<<T[now].P[0]<<","<<T[now].P[1]<<") ("<<T[n].P[0]<<","<<T[n].P[1]<<")"<<endl;
	if (T[now].P[D]>T[n].P[D])
	{
		if (T[now].ls) Insert(T[now].ls,D^1);
		else T[now].ls=n;
	}
	else
	{
		if (T[now].rs) Insert(T[now].rs,D^1);
		else T[now].rs=n;
	}
	Update(now);return;
}

void Query(int now,int x,int y)
{
    //cout<<"Q:("<<T[now].P[0]<<","<<T[now].P[1]<<") ("<<x<<","<<y<<")"<<endl;
	Ans=min(Ans,abs(x-T[now].P[0])+abs(y-T[now].P[1]));
	int dl=inf,dr=inf;
	int ls=T[now].ls,rs=T[now].rs;
	if (T[now].ls) dl=max(0,x-T[ls].Mx[0])+max(0,T[ls].Mn[0]-x)+max(0,y-T[ls].Mx[1])+max(0,T[ls].Mn[1]-y);
	if (T[now].rs) dr=max(0,x-T[rs].Mx[0])+max(0,T[rs].Mn[0]-x)+max(0,y-T[rs].Mx[1])+max(0,T[rs].Mn[1]-y);
	//cout<<dl<<" "<<dr<<endl;
	if (dl<dr)
	{
		if (dl<Ans) Query(ls,x,y);
		if (dr<Ans) Query(rs,x,y);
	}
	else
	{
		if (dr<Ans) Query(rs,x,y);
		if (dl<Ans) Query(ls,x,y);
	}
	return;
}

