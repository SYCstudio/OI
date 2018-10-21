#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=11000;
const int maxM=maxN*100;
const int HashSize=1000000;
const int maxS=110;
const int Base=29;
const int maxAlpha=26;
const int inf=2147483647;

int n;
int Map[HashSize];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
char Input[maxN][maxS];
int Cnt[maxN][maxAlpha];
int Degree[maxN],Queue[maxN],F[maxN],Path[maxN];

void Add_Edge(int u,int v);
void Outp(int id);

int main()
{
	//freopen("in.in","r",stdin);
	n=0;mem(Head,-1);
	while (scanf("%s",Input[++n]+1)!=EOF);
	n--;
	for (int i=1;i<=n;i++)
	{
		int l=strlen(Input[i]+1);
		for (int j=1;j<=l;j++) Cnt[i][Input[i][j]-'a']++;
		int hash=0;
		for (int j=0;j<maxAlpha;j++) hash=(hash*Base%HashSize+Cnt[i][j])%HashSize;
		Map[hash]=i;
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<maxAlpha;j++)
		{
			Cnt[i][j]++;
			int hash=0;
			for (int k=0;k<maxAlpha;k++) hash=(hash*Base%HashSize+Cnt[i][k])%HashSize;
			if (Map[hash]) Add_Edge(i,Map[hash]);
			Cnt[i][j]--;
		}
	}
	int h=0,t=0;
	for (int i=1;i<=n;i++) if (Degree[i]==0) Queue[++h]=i,F[i]=1;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
			Degree[V[i]]--;
			if (F[V[i]]<F[u]+1) F[V[i]]=F[u]+1,Path[V[i]]=u;
			if (Degree[V[i]]==0) Queue[++h]=V[i];
		}
	}
	while (t!=h);
	int id=1;
	for (int i=2;i<=n;i++) if (F[i]>F[id]) id=i;
	printf("%d\n",F[id]);
	Outp(id);
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Degree[v]++;
	return;
}

void Outp(int id)
{
	if (id==0) return;
	Outp(Path[id]);
	printf("%s\n",Input[id]+1);
	return;
}
