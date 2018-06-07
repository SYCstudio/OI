#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxK=3;
const int inf=2147483647;

class KDT
{
public:
	int P[maxK];
	int Mn[maxK],Mx[maxK];
	int key,mx;
	int ls,rs;
};

int n,m;
int nowD,root,Ans;
int Arr[maxN],Last[maxN],Next[maxN],Pos[maxN];
KDT T[maxN];

bool operator < (KDT A,KDT B);
void Update(int now);
int Build(int l,int r,int D);
void Query(int now,int k1,int k2);

int main()
{
	//freopen("7.in","r",stdin);freopen("out.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Arr[i]);
	for (int i=1;i<=n;i++) Last[i]=Pos[Arr[i]],Pos[Arr[i]]=i;
	for (int i=1;i<=n;i++) Pos[i]=n+1;
	for (int i=n;i>=1;i--) Next[i]=Pos[Arr[i]],Pos[Arr[i]]=i;

	//for (int i=1;i<=n;i++) cout<<Last[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Next[i]<<" ";cout<<endl;
	
	for (int i=1;i<=n;i++) T[i].P[0]=i,T[i].P[1]=Last[i],T[i].P[2]=Next[i],T[i].key=Arr[i];
	//for (int i=1;i<=n;i++) cout<<"("<<T[i].P[0]<<","<<T[i].P[1]<<","<<T[i].P[2]<<")"<<endl;
	root=Build(1,n,0);//cout<<endl;
	//for (int i=1;i<=n;i++) cout<<i<<" ("<<T[i].P[0]<<","<<T[i].P[1]<<","<<T[i].P[2]<<")"<<endl;
	//for (int i=1;i<=n;i++) cout<<T[i].ls<<" "<<T[i].rs<<endl;
	int lastans=0;
	for (int i=1;i<=m;i++)
	{
		int x,y,l,r;scanf("%d%d",&x,&y);
		l=min((x+lastans)%n+1,(y+lastans)%n+1);
		r=max((x+lastans)%n+1,(y+lastans)%n+1);
		Ans=0;
		Query(root,l,r);
		printf("%d\n",lastans=Ans);
		//if (i!=m) printf("\n");
	}
	return 0;
}

bool operator < (KDT A,KDT B){
	return A.P[nowD]<B.P[nowD];
}

void Update(int now)
{
	if (T[now].ls) T[now].mx=max(T[now].mx,T[T[now].ls].mx);
	if (T[now].rs) T[now].mx=max(T[now].mx,T[T[now].rs].mx);
	for (int i=0;i<maxK;i++)
	{
		if (T[now].ls) T[now].Mn[i]=min(T[now].Mn[i],T[T[now].ls].Mn[i]),T[now].Mx[i]=max(T[now].Mx[i],T[T[now].ls].Mx[i]);
		if (T[now].rs) T[now].Mn[i]=min(T[now].Mn[i],T[T[now].rs].Mn[i]),T[now].Mx[i]=max(T[now].Mx[i],T[T[now].rs].Mx[i]);
	}
	return;
}

int Build(int l,int r,int D)
{
	if (l>r) return 0;
	nowD=D;
	int mid=(l+r)>>1;
	nth_element(&T[l],&T[mid],&T[r+1]);
	for (int i=0;i<maxK;i++) T[mid].Mn[i]=T[mid].Mx[i]=T[mid].P[i];
	T[mid].mx=T[mid].key;
	T[mid].ls=Build(l,mid-1,(D+1)%maxK);
	T[mid].rs=Build(mid+1,r,(D+1)%maxK);
	Update(mid);
	return mid;
}

void Query(int now,int k1,int k2)
{
	//cout<<"now:"<<now<<" "<<k1<<" "<<k2<<endl;
	if (T[now].mx<Ans) return;
	if ((T[now].Mn[0]>k2)||(T[now].Mx[0]<k1)||(T[now].Mn[1]>=k1)||(T[now].Mx[2]<=k2)) return;
	
	if ((T[now].Mn[0]>=k1)&&(T[now].Mn[0]<=k2)&&(T[now].Mx[0]>=k1)&&(T[now].Mx[0]<=k2)&&(T[now].Mn[1]<k1)&&(T[now].Mx[1]<k1)&&(T[now].Mn[2]>k2)&&(T[now].Mx[2]>k2))
	{
		Ans=max(Ans,T[now].mx);
		return;
	}
	//*/
	if ((T[now].P[0]>=k1)&&(T[now].P[0]<=k2)&&(T[now].P[1]<k1)&&(T[now].P[2]>k2)) /*cout<<"Get:"<<now<<endl,*/Ans=max(Ans,T[now].key);
	if (T[T[now].ls].mx>=T[T[now].rs].mx)
	{
		if (T[now].ls) Query(T[now].ls,k1,k2);
		if (T[now].rs) Query(T[now].rs,k1,k2);
	}
	else
	{
		if (T[now].rs) Query(T[now].rs,k1,k2);
		if (T[now].ls) Query(T[now].ls,k1,k2);
	}
	return;
}

