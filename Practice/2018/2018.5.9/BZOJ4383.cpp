#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int maxQ=201000;
const int maxNode=(maxN<<2)+maxQ;
const int maxM=maxNode*10;
const int inf=2147483648;

int n,m,nodecnt;
int edgecnt=0,Head[maxNode],Next[maxM],V[maxM],W[maxM];
int Id[maxN],Input[maxN];
int Val[maxNode],Min[maxNode];
int Degree[maxNode],Queue[maxNode];

void Build(int now,int l,int r);
void Add_Edge(int u,int v,int w);
void Query(int now,int l,int r,int ql,int qr,int node);

int main()
{
    mem(Head,-1);mem(Val,-1);
    int know;
    scanf("%d%d%d",&n,&know,&m);
    Build(1,1,n);//初始化线段树上的连边，同时记录下每一个序列中的编号对应的线段树节点位置
    for (int i=1;i<=know;i++)
    {
        int pos,key;scanf("%d%d",&pos,&key);
        Val[Id[pos]]=Min[Id[pos]]=key;//对于已知的，直接赋值
    }
    for (int i=1;i<=m;i++)
    {
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
        nodecnt++;
        for (int j=1;j<=k;j++) scanf("%d",&Input[j]);
        for (int j=1;j<=k;j++) Add_Edge(nodecnt,Id[Input[j]],1);//从新建点向这k个点连边
        Input[0]=l-1;Input[k+1]=r+1;
        for (int j=1;j<=k+1;j++) if ((Input[j-1]+1!=Input[j])&&(Input[j-1]!=Input[j])) Query(1,1,n,Input[j-1]+1,Input[j]-1,nodecnt);//从线段树节点连边
    }
    int h=0,t=0;//拓扑排序
    for (int i=1;i<=nodecnt;i++) if (Degree[i]==0) Queue[++h]=i;
    bool flag=1;
    do
    {
        int u=Queue[++t];
        Min[u]=max(Min[u],1);//注意值域下界为1
        if (Val[u]==-1) Val[u]=Min[u];
        else if (Val[u]<Min[u]){//原来有值，但小于下界，则无解
            flag=0;break;
        }
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            Degree[V[i]]--;Min[V[i]]=max(Min[V[i]],Val[u]+W[i]);
            if (Degree[V[i]]==0) Queue[++h]=V[i];
        }
    }
    while (t!=h);
    for (int i=1;i<=n;i++) if (Val[Id[i]]>1e9) flag=0;//判断值域是否超过上限制
    if ((t!=nodecnt)||(flag==0)) printf("NIE\n");
    else
    {
        printf("TAK\n");
        for (int i=1;i<=n;i++) printf("%d ",Val[Id[i]]);
        printf("\n");
    }
    return 0;
}

void Build(int now,int l,int r)
{
    nodecnt=max(nodecnt,now);
    if (l==r){
        Id[l]=now;return;
    }
    int mid=(l+r)>>1;
    Add_Edge(lson,now,0);Add_Edge(rson,now,0);
    Build(lson,l,mid);Build(rson,mid+1,r);
    return;
}

void Add_Edge(int u,int v,int w)
{
    Degree[v]++;
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
    return;
}

void Query(int now,int l,int r,int ql,int qr,int node)//从线段树[ql,qr]区间的点连到node
{
    if ((l==ql)&&(r==qr)){
        Add_Edge(now,node,0);return;
    }
    int mid=(l+r)>>1;
    if (qr<=mid) Query(lson,l,mid,ql,qr,node);
    else if (ql>=mid+1) Query(rson,mid+1,r,ql,qr,node);
    else
    {
        Query(lson,l,mid,ql,mid,node);
        Query(rson,mid+1,r,mid+1,qr,node);
    }
    return;
}
