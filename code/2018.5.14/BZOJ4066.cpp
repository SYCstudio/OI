#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (((ll)x)*((ll)x))

const int maxN=101000*2;
const int inf=2147483647;

class KDT
{
public:
	int ls,rs;
	ll P[2],Mn[2],Mx[2];
};

int n,K;
int nowD,root;
KDT T[maxN];
priority_queue<ll,vector<ll>,greater<ll> > H;

bool operator < (KDT A,KDT B);
int Build(int l,int r,int D);
void Update(int now);
void Query(int now,ll x,ll y);

int main()
{
	scanf("%d%d",&n,&K);K=K<<1;
	for (int i=1;i<=K;i++) H.push(0ll);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&T[i].P[0],&T[i].P[1]);
	root=Build(1,n,0);
	//cout<<"Build over!"<<endl;
	for (int i=1;i<=n;i++) Query(root,T[i].P[0],T[i].P[1]);
	//for (int i=1;i<K;i++) H.Pop();
	printf("%lld\n",H.top());
	return 0;
}

int Build(int l,int r,int D)
{
	if (l>r) return 0;
	int mid=(l+r)>>1;
	nowD=D;
	nth_element(&T[l],&T[mid],&T[r+1]);
	T[mid].Mx[0]=T[mid].Mn[0]=T[mid].P[0];
	T[mid].Mx[1]=T[mid].Mn[1]=T[mid].P[1];
	T[mid].ls=Build(l,mid-1,D^1);
	T[mid].rs=Build(mid+1,r,D^1);
	Update(mid);return mid;
}

bool operator < (KDT A,KDT B){
	return A.P[nowD]<B.P[nowD];
}

void Update(int now)
{
	int ls=T[now].ls,rs=T[now].rs;
	if (ls) T[now].Mn[0]=min(T[now].Mn[0],T[ls].Mn[0]),T[now].Mn[1]=min(T[now].Mn[1],T[ls].Mn[1]),T[now].Mx[0]=max(T[now].Mx[0],T[ls].Mx[0]),T[now].Mx[1]=max(T[now].Mx[1],T[ls].Mx[1]);
	if (rs) T[now].Mn[0]=min(T[now].Mn[0],T[rs].Mn[0]),T[now].Mn[1]=min(T[now].Mn[1],T[rs].Mn[1]),T[now].Mx[0]=max(T[now].Mx[0],T[rs].Mx[0]),T[now].Mx[1]=max(T[now].Mx[1],T[rs].Mx[1]);
	return;
}

void Query(int now,ll x,ll y)
{
	///cout<<now<<" "<<x<<" "<<y<<endl;
	ll d=sqr(T[now].P[0]-x)+sqr(T[now].P[1]-y);
	if (d>H.top()){
		H.pop();H.push(d);
	}
	ll dl=-inf,dr=-inf;
	int ls=T[now].ls,rs=T[now].rs;
	if (ls) dl=max(sqr(x-T[ls].Mn[0]),sqr(x-T[ls].Mx[0]))+max(sqr(y-T[ls].Mn[1]),sqr(y-T[ls].Mx[1]));
	if (rs) dr=max(sqr(x-T[rs].Mn[0]),sqr(x-T[rs].Mx[0]))+max(sqr(y-T[rs].Mn[1]),sqr(y-T[rs].Mx[1]));
	if (dl>=dr)
	{
		if (H.top()<dl) Query(ls,x,y);
		if (H.top()<dr) Query(rs,x,y);
	}
	else
	{
		if (H.top()<dr) Query(rs,x,y);
		if (H.top()<dl) Query(ls,x,y);
	}
	return;
}

