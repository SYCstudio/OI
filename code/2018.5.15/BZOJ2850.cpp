#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51000;
const int inf=2147483647;

class KDT
{
public:
	ll sum,key;
	int ls,rs;
	ll P[2],Mx[2],Mn[2];
};

int n,m;
KDT T[maxN];
int nowD,root;

bool operator < (KDT A,KDT B);
int Build(int l,int r,int D);
void Update(int now);
ll Query(int now,ll a,ll b,ll c);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld%lld%lld",&T[i].P[0],&T[i].P[1],&T[i].key);
	root=Build(1,n,0);
	for (int i=1;i<=m;i++)
	{
		ll a,b,c;scanf("%lld%lld%lld",&a,&b,&c);
		printf("%lld\n",Query(root,a,b,c));
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
	T[mid].Mx[0]=T[mid].Mn[0]=T[mid].P[0];
	T[mid].Mx[1]=T[mid].Mn[1]=T[mid].P[1];
	T[mid].sum=T[mid].key;
	T[mid].ls=Build(l,mid-1,D^1);
	T[mid].rs=Build(mid+1,r,D^1);
	Update(mid);return mid;
}

void Update(int now)
{
	int ls=T[now].ls,rs=T[now].rs;
	T[now].sum=T[now].key;
	if (ls) T[now].sum+=T[ls].sum,T[now].Mn[0]=min(T[now].Mn[0],T[ls].Mn[0]),T[now].Mn[1]=min(T[now].Mn[1],T[ls].Mn[1]),T[now].Mx[0]=max(T[now].Mx[0],T[ls].Mx[0]),T[now].Mx[1]=max(T[now].Mx[1],T[ls].Mx[1]);
	if (rs) T[now].sum+=T[rs].sum,T[now].Mn[0]=min(T[now].Mn[0],T[rs].Mn[0]),T[now].Mn[1]=min(T[now].Mn[1],T[rs].Mn[1]),T[now].Mx[0]=max(T[now].Mx[0],T[rs].Mx[0]),T[now].Mx[1]=max(T[now].Mx[1],T[rs].Mx[1]);
	return;
}

ll Query(int now,ll a,ll b,ll c)
{
	int cnt=((T[now].Mn[0]*a+T[now].Mn[1]*b)<c)+((T[now].Mn[0]*a+T[now].Mx[1]*b)<c)+((T[now].Mx[0]*a+T[now].Mn[1]*b)<c)+((T[now].Mx[0]*a+T[now].Mx[1]*b)<c);
	if (cnt==0) return 0;
	if (cnt==4) return T[now].sum;
	ll Ret=0;
	if (T[now].P[0]*a+T[now].P[1]*b<c) Ret+=T[now].key;
	if (T[now].ls) Ret+=Query(T[now].ls,a,b,c);
	if (T[now].rs) Ret+=Query(T[now].rs,a,b,c);
	return Ret;
}
