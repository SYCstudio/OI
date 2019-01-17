#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int maxD=21;
const int inf=2000000000;

class Data{
public:
    int sum,dist;
};

int n,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int root,nowsize,Sz[maxN],Mx[maxN];
bool vis[maxN];
vector<int> To[maxN];
Data Gc[maxN][maxD],Bl[maxD][maxN];

Data operator + (Data A,Data B);
void Add_Edge(int u,int v,int w);
void dfs_root(int u,int fa);
void solve_init(int u,int d);
void modify(int u,int d,int x,int val);
int get_point(int u,int d);
int get_dist(int u,int d,int x);

int main(){
    scanf("%d%d",&n,&Q);
    for (int i=1;i<n;i++){
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    Mx[root=0]=inf;nowsize=n;dfs_root(1,1);
    int rt=root;solve_init(root,0);
    while (Q--){
	int u,e;scanf("%d%d",&u,&e);
	modify(rt,0,u,e);
	printf("%d\n",get_dist(rt,0,get_point(rt,0)));
    }
    return 0;
}
Data operator + (Data A,Data B){
    return ((Data){A.sum+B.sum,A.dist+B.dist});
}
void Add_Edge(int u,int v,int w){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
    return;
}
void dfs_root(int u,int fa){
    Sz[u]=1;Mx[u]=0;
    for (int i=Head[u];i!=-1;i=Next[i])
	if ((vis[V[i]]==0)&&(V[i]!=fa)){
	    dfs_root(V[i],u);Sz[u]+=Sz[V[i]];
	    Mx[u]=max(Mx[u],Sz[V[i]]);
	}
    Mx[u]=max(Mx[u],nowsize-Sz[u]);
    if (Mx[u]<Mx[root]) root=u;return;
}
void solve_init(int u,int d){
    vis[u]=1;
}
void modify(int u,int d,int x,int val);
int get_point(int u,int d);
int get_dist(int u,int d,int x);
