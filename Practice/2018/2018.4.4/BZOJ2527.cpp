#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-(x)))

const int maxN=300100;
const int inf=2147483647;

int n,m,K;
int P[maxN],O[maxN];
int L[maxN],R[maxN],A[maxN];
int edgecnt=0,Head[maxN],Next[maxN],V[maxN];
int Ans[maxN],Last[maxN];
ll BIT[maxN],Sum[maxN];
int histcnt=0,Hist[maxN];
int Id[maxN],Bp[maxN];

void Add_Edge(int u,int v);
void Solve(int tl,int tr,int il,int ir);
void Add(int pos,int key);
ll Query(int pos);

int main()
{
	//ios::sync_with_stdio(false);
	mem(Head,-1);
	
	//cin>>n>>m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int o;scanf("%d",&o);//cin>>o;
		Add_Edge(o,i);
	}
	for (int i=1;i<=n;i++) scanf("%d",&P[i]);//cin>>P[i];
	cin>>K;
	for (int i=1;i<=K;i++) scanf("%d%d%d",&L[i],&R[i],&A[i]);//cin>>L[i]>>R[i]>>A[i];
	K++;L[K]=1;R[K]=m;A[K]=inf;

	for (int i=1;i<=n;i++) Id[i]=i;
	Solve(1,K,1,n);
	
	for (int i=1;i<=n;i++)
		if (Ans[i]==K) printf("NIE\n");//cout<<"NIE"<<endl;
		else printf("%d\n",Ans[i]);//cout<<Ans[i]<<endl;
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void Solve(int tl,int tr,int il,int ir)
{
	//cout<<tl<<" "<<tr<<" "<<il<<" "<<ir<<endl;
	if (il>ir) return;
	if (tl==tr)
	{
		for (int i=il;i<=ir;i++) Ans[Id[i]]=tl;
		return;
	}
	histcnt++;
	int mid=(tl+tr)>>1;
	for (int t=tl;t<=mid;t++)
		if (L[t]<=R[t]) Add(L[t],A[t]),Add(R[t]+1,-A[t]);
		else Add(L[t],A[t]),Add(1,A[t]),Add(R[t]+1,-A[t]);
	//cout<<"Add:"<<tl<<" "<<mid<<endl;
	//for (int i=1;i<=m;i++) cout<<Query(i)<<" ";cout<<endl;
	int l=il,r=ir;
	for (int i=il;i<=ir;i++)
	{
		Sum[Id[i]]=0;
		//cout<<Id[i]<<":"<<endl;
		for (int e=Head[Id[i]];e!=-1;e=Next[e])
		{
			Sum[Id[i]]+=Query(V[e]);
			//cout<<V[e]<<" ";
			if (Sum[Id[i]]+Last[Id[i]]>P[Id[i]]) break;
		}
		//cout<<endl<<"Sum:"<<Sum[Id[i]]<<endl;
		if (Sum[Id[i]]+Last[Id[i]]>=P[Id[i]]) /*cout<<Id[i]<<" left"<<endl,*/Bp[l++]=Id[i];
		else Bp[r--]=Id[i],Last[Id[i]]+=Sum[Id[i]]/*,cout<<Id[i]<<" right"<<endl*/;
	}
	for (int i=il;i<=ir;i++) Id[i]=Bp[i];
	Solve(tl,mid,il,l-1);Solve(mid+1,tr,r+1,ir);
	return;
}

void Add(int pos,int key)
{
	while (pos<=m)
	{
		if (Hist[pos]!=histcnt) BIT[pos]=key,Hist[pos]=histcnt;
		else BIT[pos]+=key;
		pos+=lowbit(pos);
	}
	return;
}

ll Query(int pos)
{
	ll Ret=0;
	while (pos)
	{
		if (Hist[pos]==histcnt) Ret+=BIT[pos];
		pos-=lowbit(pos);
	}
	return Ret;
}
