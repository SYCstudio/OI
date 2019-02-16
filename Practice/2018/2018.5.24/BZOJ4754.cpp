#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxM=maxN*2;
const ull base1=50;
const ull base2=20020729;
const int inf=2147483647;

int n;
int edgecnt,Head[maxN],Next[maxM],V[maxM];
ull Hash[maxN];
int Size[maxN],Degree[maxN];
int Ans=inf;
map<ull,bool> Get;

void Add_Edge(int u,int v);
void Build(int u,int fa);
void Calc(int u,int fa);
void GetAns(int u,int fa);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Build(1,0);
	//for (int i=1;i<=n;i++) cout<<Hash[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Size[i]<<" ";cout<<endl;
	Calc(1,0);
	//for (int i=1;i<=n;i++) cout<<Hash[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Size[i]<<" ";cout<<endl;
	edgecnt=0;mem(Head,-1);mem(Hash,0);mem(Size,0);n++;
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
		Degree[u]++;Degree[v]++;
	}
	for (int i=1;i<=n;i++)
		if (Degree[i]>1)
		{
			Build(i,0);
			//for (int j=1;j<=n;j++) cout<<Size[j]<<" ";cout<<endl;
			GetAns(i,0);
			//for (int j=1;j<=n;j++) cout<<Hash[j]<<" ";cout<<endl;
			//for (int j=1;j<=n;j++) cout<<Size[j]<<" ";cout<<endl;
			break;
		}
	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void Build(int u,int fa)
{
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			Build(V[i],u);
			Hash[u]=Hash[u]^(Hash[V[i]]+base1);
			Size[u]+=Size[V[i]];
		}
	Hash[u]=Hash[u]+base2*Size[u]+1;
	return;
}

void Calc(int u,int fa)
{
	Get[Hash[u]]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			ull tmp=((Hash[u]-(ull)n*base2-1)^(Hash[V[i]]+base1))+(ull)(n-Size[V[i]])*base2+1;
			Hash[V[i]]=((Hash[V[i]]-(ull)Size[V[i]]*base2-1)^(tmp+base1))+(ull)n*base2+1;
			Size[V[i]]=n;
			Calc(V[i],u);
		}
	return;
}

void GetAns(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			if (Degree[V[i]]>1)
			{
				ull tmp=((Hash[u]-base2*n-1)^(Hash[V[i]]+base1))+(n-Size[V[i]])*base2+1;
				Hash[V[i]]=((Hash[V[i]]-base2*Size[V[i]]-1)^(tmp+base1))+base2*n+1;
				Size[V[i]]=n;
				GetAns(V[i],u);
			}
			else
			{
				ull tmp=((Hash[u]-base2*n-1)^(Hash[V[i]]+base1))+(n-1)*base2+1;
				//cout<<V[i]<<" "<<tmp<<endl;
				if (Get.count(tmp)) Ans=min(Ans,V[i]);
			}
		}
	return;
}
/*
3
1 2
2 3

1 2
2 3
3 4
*/
