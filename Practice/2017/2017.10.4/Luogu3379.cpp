#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=500100;
const int inf=2147483647;

class Tree_Node
{
public:
    int f,top,sz,son,depth;//父亲，跳到顶部，大小，重儿子，深度
    Tree_Node()
        {
            f=-1;
            sz=1;
        }
};

int n,root,Q;
int cnt=0;
int Head[maxN];
int Next[maxN*2];
int V[maxN*2];
Tree_Node T[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int father);
void dfs2(int u,int nowTop);
int LCA(int a,int b);

int main()
{
    memset(Head,-1,sizeof(Head));
    scanf("%d%d%d",&n,&Q,&root);
    for (int i=1;i<n;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        Add_Edge(u,v);
        Add_Edge(v,u);
    }
    T[root].depth=1;
    dfs1(root,root);
    dfs2(root,root);
    /*
    for (int i=1;i<=n;i++)
        cout<<T[i].f<<" "<<T[i].top<<" "<<T[i].sz<<" "<<T[i].son<<" "<<T[i].depth<<endl;
    //*/
    while (Q--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%d\n",LCA(u,v));
    }
    return 0;
}

void Add_Edge(int u,int v)
{
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    V[cnt]=v;
    return;
}

void dfs1(int u,int father)
{
    int mxsz=0;
    T[u].sz=1;
    for (int i=Head[u];i!=-1;i=Next[i])
    {
        int v=V[i];        
        if (v==father)
            continue;
        T[v].f=u;
        T[v].depth=T[u].depth+1;
        dfs1(v,u);
        T[u].sz+=T[u].sz;
        if (T[v].sz>mxsz)
        {
            T[u].son=v;
            mxsz=T[v].sz;
        }
    }
    if (mxsz==0)
        T[u].son=0;
    return;
}

void dfs2(int u,int nowTop)
{
    T[u].top=nowTop;
    if (T[u].son==0)
        return;
    dfs2(T[u].son,nowTop);
    for (int i=Head[u];i!=-1;i=Next[i])
    {
        int v=V[i];
        if ((v==T[u].son)||(v==T[u].f))
            continue;
        dfs2(v,v);
    }
    return;
}

int LCA(int a,int b)
{
    int f1=T[a].top;
    int f2=T[b].top;
    while (f1!=f2)
    {
        if (T[f1].depth<T[f2].depth)
        {
            swap(f1,f2);
            swap(a,b);
        }
        a=T[f1].f;
        f1=T[a].top;
    }
    if (T[a].depth<T[b].depth)
        return a;
    else
        return b;
}
