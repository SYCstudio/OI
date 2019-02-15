#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=201000*2;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int n1,n2,top,To[maxN],Fa[maxN],St[maxN];
bool vis[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	for (int i=1;i<=n;i++)
		if (vis[i]==0){
			//cout<<i<<endl;
			n1=n2=-1;top=0;
			dfs(i,i);
			//cout<<n1<<" "<<n2<<endl;
			//for (int j=1;j<=top;j++) cout<<St[j]<<" ";cout<<endl;
			if (n1==-1){
				printf("NIE\n");return 0;
			}
			int now=n2;
			while (now!=n1){
				//cout<<now<<" ";
				To[now]=Fa[now];now=Fa[now];
			}
			//cout<<endl;
			To[now]=n2;
			while (Fa[now]){
				//cout<<now<<" ";
				To[Fa[now]]=now;now=Fa[now];
			}
			//cout<<endl;
			for (int j=1;j<=top;j++) if (To[St[j]]==0) To[St[j]]=Fa[St[j]];
		}

	printf("TAK\n");
	for (int i=1;i<=n;i++) printf("%d\n",To[i]);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u,int fa){
	vis[u]=1;St[++top]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			if (vis[V[i]]==0){
				Fa[V[i]]=u;dfs(V[i],u);
			}
			else if (n1==-1) n1=V[i],n2=u;
		}
	return;
}
