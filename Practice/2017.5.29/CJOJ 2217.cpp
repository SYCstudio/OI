#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
 
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
class EDGE
{
public:
    int u,v,w;
};
 
bool operator < (EDGE a,EDGE b)
{
    return a.w<b.w;
}
 
const int maxN=15001;
const int maxM=30001*2;
const int inf=2147483647;
 
int n,m,K;
int cnt;
//Graph1
EDGE Edge[maxM];
//Graph2
int First[maxN];
int Last[maxN];
int Next[maxM];
int V[maxM];
int W[maxM];
//Kerubiel
int Mayuri[maxN];
//Tree
int Father[maxN];
int Deep[maxN];
int Way[maxN];
 
void init();
void Add_Edge(int u,int v,int w);
void Union(int x,int y);
void Build_Tree(int u,int father);
int Find(int x);
int lca(int a,int b);
 
int main()
{
    //freopen("heatwave.in","r",stdin);
    //freopen("heatwave.out","w",stdout);
 
    cin>>n>>m>>K;
    cnt=0;
    init();
    for (int i=1;i<=n;i++)
        Mayuri[i]=i;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].w);
    }
 
    sort(&Edge[1],&Edge[m+1]);
 
    int tot=0;
    cnt=0;
    for (int i=1;i<=m;i++)
    {
        int u=Edge[i].u;
        int v=Edge[i].v;
        int w=Edge[i].w;
        if (Find(u)!=Find(v))
        {
            tot++;
            Union(u,v);
            Add_Edge(u,v,w);
            Add_Edge(v,u,w);
            if (tot>n-1)
                break;
        }
    }
 
    //cout<<"MST"<<endl;
 
    Deep[1]=0;
    Father[1]=0;
    Father[0]=0;
    Way[0]=0;
 
    Build_Tree(1,0);
    //cout<<"TREE"<<endl;
 
    /*for (int i=1;i<=n;i++)
    {
        cout<<"Node "<<i<<endl;
        for (int j=First[i];j!=-1;j=Next[j])
            cout<<V[j]<<' ';
        cout<<endl;
    }
    for (int i=1;i<=n;i++)
        cout<<Father[i]<<' ';
    cout<<endl;
    for (int i=1;i<=n;i++)
        cout<<Deep[i]<<' ';
    cout<<endl;//*/
 
    int a,b;
    for (int i=1;i<=K;i++)
    {
        cin>>a>>b;
        //cout<<"lca "<<a<<' '<<b<<endl;
        cout<<lca(a,b)<<endl;
    }
 
    fclose(stdin);
    fclose(stdout);
}
 
void init()
{
    cnt=0;
    mem(First,-1);
    mem(Next,-1);
    mem(Father,-1);
    return;
}
 
void Add_Edge(int u,int v,int w)
{
    cnt++;
    V[cnt]=v;
    W[cnt]=w;
    if (First[u]==-1)
    {
        First[u]=cnt;
        Last[u]=cnt;
    }
    else
    {
        Next[Last[u]]=cnt;
        Last[u]=cnt;
    }
    return;
}
 
void Union(int x,int y)
{
    int fx=Find(x);
    int fy=Find(y);
    Mayuri[fx]=fy;
    return;
}
 
int Find(int x)
{
    return Mayuri[x]==x ? (x) : Mayuri[x]=Find(Mayuri[x]);
}
 
void Build_Tree(int u,int father)
{
    //Father[u]=father;
    //Deep[u]=Deep[father]+1;
    for (int i=First[u];i!=-1;i=Next[i])
    {
        int v=V[i];
        if (v!=father)
        {
            Way[v]=W[i];
            Father[v]=u;
            Deep[v]=Deep[u]+1;
            Build_Tree(v,u);
        }
    }
    return;
}
 
int lca(int a,int b)
{
    int Max_Way=0;
    if (Deep[a]<Deep[b])
        swap(a,b);
    //cout<<"while 1"<<endl;
    while (Deep[a]!=Deep[b])
    {
        //cout<<a<<' '<<b<<endl;
        Max_Way=max(Max_Way,Way[a]);
        a=Father[a];
    }
    //cout<<"while 2"<<endl;
    while (a!=b)
    {
        //cout<<a<<' '<<b<<endl;
        Max_Way=max(Max_Way,max(Way[a],Way[b]));
        a=Father[a];
        b=Father[b];
    }
    return Max_Way;
}