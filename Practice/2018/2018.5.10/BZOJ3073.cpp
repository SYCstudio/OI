#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=501000;
const int maxQ=101000;
const int maxNode=((maxN<<2)+(maxQ<<1))<<1;
const int maxM=maxNode*10;
const int inf=2147483647;

class HeapData
{
public:
    int u,dist;
};

int n,m,P;
int Id1[maxN],Id2[maxN],nodesum,nodecnt;
int edgecnt=0,Head[maxNode],Next[maxM],V[maxM],W[maxM];
bool vis[maxNode];
int Dist[maxNode];
priority_queue<HeapData> H;

bool operator < (HeapData A,HeapData B);
void Add_Edge(int u,int v,int w);
void Build1(int now,int l,int r);
void Build2(int now,int l,int r);
void Add1(int now,int l,int r,int ql,int qr,int node,int opt);
void Add2(int now,int l,int r,int ql,int qr,int node,int opt);

int main()
{
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&P);
    Build1(1,1,n);Build2(1,1,n);//建树
    nodecnt=nodesum<<1;
    for (int i=1;i<=m;i++)
    {
        int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
        nodecnt++;
        Add1(1,1,n,a,b,nodecnt,0);
        Add2(1,1,n,c,d,nodecnt,1);
        nodecnt++;
        Add1(1,1,n,c,d,nodecnt,0);
        Add2(1,1,n,a,b,nodecnt,1);
    }
    mem(Dist,-1);P=Id1[P];Dist[P]=0;H.push((HeapData){P,0});
    do
    {
        int u=H.top().u;H.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (int i=Head[u];i!=-1;i=Next[i])
            if ((vis[V[i]]==0)&&((Dist[V[i]]==-1)||(Dist[V[i]]>Dist[u]+W[i])))
            {
                Dist[V[i]]=Dist[u]+W[i];
                H.push((HeapData){V[i],Dist[V[i]]});
            }
    }
    while (!H.empty());
    for (int i=1;i<=n;i++) printf("%d\n",Dist[Id1[i]]);
    return 0;
}

bool operator < (HeapData A,HeapData B)
{
    return A.dist>B.dist;
}

void Add_Edge(int u,int v,int w)
{
    //cout<<"Add:"<<u<<"->"<<v<<" "<<w<<endl;
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
}

void Build1(int now,int l,int r)
{
    if (l==r){
        Id1[l]=now;nodesum=max(nodesum,now);return;
    }
    int mid=(l+r)>>1;
    Add_Edge(lson,now,0);Add_Edge(rson,now,0);
    Build1(lson,l,mid);Build1(rson,mid+1,r);
    return;
}

void Build2(int now,int l,int r)
{
    Add_Edge(now+nodesum,now,0);
    if (l==r){
        Id2[l]=now+nodesum;return;
    }
    int mid=(l+r)>>1;
    Add_Edge(now+nodesum,lson+nodesum,0);Add_Edge(now+nodesum,rson+nodesum,0);
    Build2(lson,l,mid);Build2(rson,mid+1,r);
    return;
}

void Add1(int now,int l,int r,int ql,int qr,int node,int opt)
{
    if ((l==ql)&&(r==qr))
    {
        if (opt==0) Add_Edge(now,node,1);
        else Add_Edge(node,now,0);
        return;
    }
    int mid=(l+r)>>1;
    if (qr<=mid) Add1(lson,l,mid,ql,qr,node,opt);
    else if (ql>=mid+1) Add1(rson,mid+1,r,ql,qr,node,opt);
    else
    {
        Add1(lson,l,mid,ql,mid,node,opt);
        Add1(rson,mid+1,r,mid+1,qr,node,opt);
    }
    return;
}

void Add2(int now,int l,int r,int ql,int qr,int node,int opt)
{
    if ((l==ql)&&(r==qr))
    {
        if (opt==0) Add_Edge(now+nodesum,node,1);
        else Add_Edge(node,now+nodesum,0);
        return;
    }
    int mid=(l+r)>>1;
    if (qr<=mid) Add2(lson,l,mid,ql,qr,node,opt);
    else if (ql>=mid+1) Add2(rson,mid+1,r,ql,qr,node,opt);
    else
    {
        Add2(lson,l,mid,ql,mid,node,opt);
        Add2(rson,mid+1,r,mid+1,qr,node,opt);
    }
    return;
}
