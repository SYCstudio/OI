#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxM=1001000*2;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
bool vis[maxN];
int Depth[maxN],Queue[maxN],Fa[maxN];

void Add_Edge(int u,int v,int w);
int gcd(int a,int b);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int a,b;scanf("%d%d",&a,&b);
		Add_Edge(a,b,1);Add_Edge(b,a,-1);
	}
	int length=0,chain=0;
	for (int i=1;i<=n;i++)
		if (vis[i]==0)
		{
			Depth[i]=0;
			int h=1,t=0;Queue[1]=i;vis[i]=1;
			int mx=-inf,mn=inf;
			do
			{
				int u=Queue[++t];mx=max(mx,Depth[u]),mn=min(mn,Depth[u]);
				for (int i=Head[u];i!=-1;i=Next[i])
				{
					if (V[i]==Fa[u]) continue;
					if (vis[V[i]]==0) vis[Queue[++h]=V[i]]=1,Depth[V[i]]=Depth[u]+W[i],Fa[V[i]]=u;
					else
					{
						//cout<<u<<" "<<V[i]<<" "<<abs(Depth[u]-Depth[V[i]])+1<<endl;
						if (length==0) length=abs(Depth[u]-Depth[V[i]]+W[i]);
						else length=gcd(length,abs(Depth[u]-Depth[V[i]]+W[i]));
					}
				}
			}
			while (h!=t);
			chain=chain+mx-mn+1;
		}
	//for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";cout<<endl;
	if (length==0)
	{
		if (chain<3) printf("-1 -1\n");
		else printf("%d 3\n",chain);
	}
	else
	{
		if (length<3) printf("-1 -1\n");
		else
		{
			printf("%d ",length);
			for (int i=3;i<=length;i++) if (length%i==0) {length=i;break;}
			printf("%d\n",length);
		}
	}
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

int gcd(int a,int b)
{
	int tmp;
	while (b) tmp=b,b=a%b,a=tmp;
	return a;
}
