#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5010;
const int maxId=210;
const int maxM=maxN*2*maxId;
const int Mod=100003;
const ull hashbase=213;
const int inf=2147483647;

int n,Id,m;
int UFS[maxId][maxN],Size[maxId][maxN];
ull NodeHash[maxN];
int edgecnt=0,EHead[maxId][maxN],ENext[maxM],EV[maxM];
int hashcnt=0,HHead[maxM],HNext[maxM],Cnt[maxM];
ull HVal[maxM],HPow[maxId];
int ReuseStack[maxM],restacktop=0;
ll Ans=0;

void Insert(ull key);
void Delete(ull key);
void EAdd_Edge(int u,int v,int id);
void Union(int u,int v,int id);
void dfs(int u,int fa,int id,int anc);

int main()
{
	//ios::sync_with_stdio(false);
	mem(EHead,-1);mem(HHead,-1);
	for (int i=1;i<maxM;i++) ReuseStack[++restacktop]=i;
	
	scanf("%d%d%d",&Id,&n,&m);//cin>>Id>>n>>m;
	HPow[1]=1;for (int i=2;i<=Id;i++) HPow[i]=HPow[i-1]*hashbase;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=Id;j++) UFS[j][i]=i,Size[j][i]=1,NodeHash[i]=NodeHash[i]+(ull)i*HPow[j];
		Insert(NodeHash[i]);
	}
	while (m--)
	{
		int id,u,v;scanf("%d%d%d",&u,&v,&id);//cin>>u>>v>>id;
		Union(u,v,id);
		printf("%lld\n",Ans);//cout<<Ans<<endl;
	}
	return 0;
}

void Insert(ull key)
{
	ull p=key%Mod;
	for (int i=HHead[p];i!=-1;i=HNext[i])
		if (HVal[i]==key)
		{
			Ans+=Cnt[i]*2+1;Cnt[i]++;
			return;
		}
	Ans++;
	int pos=ReuseStack[restacktop--];
	HNext[pos]=HHead[p];HVal[pos]=key;Cnt[pos]=1;HHead[p]=pos;
	return;
}

void Delete(ull key)
{
	int p=key%Mod;
	if (HVal[HHead[p]]==key)
	{
		Cnt[HHead[p]]--;Ans=Ans-(2ll*Cnt[HHead[p]]+1);
		if (Cnt[HHead[p]]==0)
		{
			ReuseStack[++restacktop]=HHead[p];
			HHead[p]=HNext[HHead[p]];
		}
		return;
	}
	for (int i=HHead[p],last=0;i!=-1;last=i,i=HNext[i])
		if (HVal[i]==key)
		{
			Cnt[i]--;Ans=Ans-(2ll*Cnt[i]+1);
			if (Cnt[i]==0)
			{
				ReuseStack[++restacktop]=i;
				HNext[last]=HNext[i];
			}
			return;
		}
	return;
}

void EAdd_Edge(int u,int v,int id)
{
	edgecnt++;ENext[edgecnt]=EHead[id][u];EHead[id][u]=edgecnt;EV[edgecnt]=v;
	return;
}

void Union(int u,int v,int id)
{
	if (UFS[id][u]==UFS[id][v]) return;
	//u=UFS[id][u];v=UFS[id][v];
	if (Size[id][UFS[id][u]]>Size[id][UFS[id][v]]) swap(u,v);
	Size[id][UFS[id][v]]+=Size[id][UFS[id][u]];
	EAdd_Edge(u,v,id);EAdd_Edge(v,u,id);
	dfs(u,v,id,UFS[id][v]);
	return;
}

void dfs(int u,int fa,int id,int anc)
{
	Delete(NodeHash[u]);
	NodeHash[u]-=HPow[id]*(ull)UFS[id][u];
	UFS[id][u]=anc;
	NodeHash[u]+=HPow[id]*(ull)UFS[id][u];
	Insert(NodeHash[u]);
	for (int i=EHead[id][u];i!=-1;i=ENext[i])
		if (EV[i]!=fa) dfs(EV[i],u,id,anc);
	return;
}
